# include	<stdio.h>
# include	<stdlib.h>

# include	"b3.h"
# include	"vcrplus.h"
# include	"ileave.h"
# include	"scramble.h"
# include	"misc.h"
# include	"top456.h"

# define	BEST
# ifdef BEST
# include	"best.h"
# endif

long	debug = 0;


static char *mon[] = {  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

static void
usage( char *progname )
{

# ifdef US
	printf("Usage: %s <Month (1-12)> <Day (1-31)> <Year (0-99)> <Channel (1-64)> <Start Time (0-2330)> <Length (0-300)>\n",
				progname);
# endif
# ifdef UK
	printf("Usage: %s <Day (1-31)> <Month (1-12)> <Year (0-99)> <Channel (1-16)> <Start-time (0-2355)> <Length (0-180)>\n",
				progname);
# endif
# ifdef DE
	printf("Usage: %s <Tag (1-31)> <Monat (1-12)> <Jahr (0-99)> <Kanal (1-19, 100-132)> <Startzeit (0-2355)> <L„nge (0-180)>\n",
				progname);
# endif
# ifdef AU
	printf("Usage: %s <Day (1-31)> <Month (1-12)> <Year (0-99)> <Channel (1-19, 100-132)> <Start-time (0-2355)> <Length (0-180)>\n",
				progname);
# endif

	return;
}


int
main( int argc, char *argv[] )
{
	int	j;
	long	tblidx, limit;
# ifdef FULLSEARCH
	long	doneflag;
# endif
# ifdef US
	long	trailers;
# endif
	int	channel, s5_out, bot3, rem, ofout;
	int	month, day, year, starttime, duration ;
	long	s1_out, top5, newspaper, s4_out;
#if defined(DE) || defined(AU)
	int	channel_old;
#endif
# ifdef BEST
	unsigned long heuristic;
# endif


	if (argc != 7) {
		usage("encode");
		return -1;
	}

# ifdef US
	month = atoi(argv[1]);
	day = atoi(argv[2]);
#else
	day = atoi(argv[1]);
	month = atoi(argv[2]);
# endif
	year = atoi(argv[3]);
	channel = atoi(argv[4]);
	starttime = atoi(argv[5]);
	duration = atoi(argv[6]);

	year = year % 100 ;

	if ((month > 12) || (month < 1) ||
	     (day < 1) || (day > 31)) {
		printf("Invalid date\n");
		usage("encode");
		return -1;
	}

# ifdef US
	if ((channel < 1) || (channel > 64)) {
# endif
# ifdef UK
	if ((channel < 1) || (channel > 16)) {
# endif
# if defined(DE) || defined(AU)
	if (!(((channel >= 1) && (channel <= 19)) ||
           ((channel >= 100) && (channel <= 120)))) {
# endif
		printf("Invalid channel number\n");
		usage("encode");
		return -1;
	}

# if defined(DE) || defined(AU)
        channel_old = channel;
        if (channel >= 100)
          channel -= 80;
# endif

# ifdef US
	trailers = starttime % 100;
	if ((trailers != 0) && (trailers != 30)) {
		printf("Invalid start time\n");
		usage("encode");
		return -1;
	}

	if ((starttime < 0) || (starttime > 2330)) {
#else
	if ((starttime < 0) || (starttime > 2355)) {
# endif
		printf("Sorry, I cannot process that starting time\n");
		usage("encode");
		return -1;
	}

# ifdef US
	trailers = duration % 30;
	if ((trailers!=0) || (duration<30) || (duration>300)) {
#else
	if (duration < 0 || duration > 180) {
# endif
		printf("Sorry, I can't process that program length\n");
		usage("encode");
		return -1;
	}

	/* get the  t  bits and the  c  bits */
# ifdef BEST
	/* do a best fit match on the timeslot */
	tblidx = besttimes(&starttime, &duration, &heuristic);

#if defined(DE) || defined(AU)
        if (tblidx == INVALID)
        {
          printf ("\aNo exact match and no best match available!\nSorry...\n");
          return -1;
        }
#endif

	if (heuristic) {
		printf("\aExact match not available\n");
		printf("Best fit: %04d/%d\n\n", starttime, duration);
	}
# else
	if ((tblidx = scanfor(starttime, duration)) < 0) {
		printf("Sorry, no index known.\n");
		usage("encode");
		return -1;
	}
# endif

# ifdef DEBUG
	printf("Index = %ld\n", tblidx);
# endif
	/* from them infer what must have been step 4 & step 5 results */
	interleave(tblidx, channel-1, (&s4_out), (&s5_out)) ;

	/* if the mapped_top is zero then top and offset are zero */
	if (s4_out == 0) {
		top5 = 0;
		ofout = 0;
	}
	else {
# ifdef FULLSEARCH
		/* find the smallest unmapped_top giving correct mapped_top */
		nd(s4_out, &limit);
		top5 = limit / 10;
		printf("S4=%ld, top5 = %ld, limit = %d\n", s4_out, top5, limit);
		doneflag = 0;

		while (doneflag == 0) {
			offset(day, year, top5, (&ofout), (&j)) ;
			putchar((top5 & 0x01)? '+': 'X');
			putchar('\r');

			if (j == s4_out) {
				printf("\nFound it: %ld\n", top5);
				break;
			}

			if (++top5 >= limit) {
				printf("Can't seem to find an encoding - sorry\n");
				break;
			}
		}
# else
		int	i;
		long	tmp;

		if ((j = nd(s4_out, &limit)) > 3) {
		/*	printf("S4_out = 0x%lX\n", s4_out);	*/
			printf("That needs a 7 or 8 digit code - sorry\n");
			return -1;
		}

		limit /= 10;
		ofout = 0;
		top5 = s4_out;

		/* get a top5 with same no digits as s4_out */
		/* may have to loop several times */
		do {
			/* reverse the map_top encryption */
			top5 = unmap_top(day, year, top5, j);

			/* use that 'top5' to find offset */
			for(i=0; i<=(year%16); i++)
				ofout += ( int )(map_top(day, i, top5, j) % 10);
# ifdef DEBUG
			printf("%ld\n", top5);
# endif
		} while (top5 < limit);

		/* add sum of final top5's digits to offset */
		tmp = top5;

		while (tmp > 0) {
			ofout += ( int )(tmp % 10);
			tmp /= 10;
		}

		ofout %= 32;
# endif
	}
		
	/* have two of the three inputs to step 5; determine the rem */
	for(rem=0; rem<32; rem++)
	{
		j = (rem + (day*(month+1)) + ofout) % 32;
		if(j == s5_out) break ;
	}

	/* assemble the output of step 1 */
	bot3 = encode_bot3(day, rem);
	s1_out = bot3 + (1000 * top5) ;
# ifdef DEBUG
	printf("s1=%ld\n", s1_out);
# endif

	/* invert the mixing */
	newspaper = f1(s1_out, KEY002);

# ifdef US
	printf("\t%s  %2d  %2d\n", mon[month-1], day, year);
	printf("\tChannel= %2d\n", channel);
	printf("\tStart time= %04d  Length= %3d\n", starttime, duration);
	printf("\tEnd time= %04d\n", end_time(starttime, duration));
	printf("\tVCR+ code= %8ld\n", newspaper);
# endif
# ifdef UK
	printf("\t%s  %2d  %2d\n", mon[month-1], day, year);
	printf("\tChannel= %2d\n", channel);
	printf("\tStart time= %04d  Length= %3d\n", starttime, duration);
	printf("\tEnd time= %04d\n", end_time(starttime, duration));
	printf("\tVideoPlus code= %8ld\n", newspaper);
# endif
# if defined(DE)
	printf("\t%d. %s %2d\n\tKanal= %2d\n", day, mon[month-1], year);
	printf("\tKanal= %2d\n", channel_old);
	printf("\tStartzeit= %04d  L„nge= %3d\n", starttime, duration);
	printf("\tEndzeit= %04d\n", end_time(starttime, duration));
	printf("\tShowView code= %8ld\n", newspaper);
# endif
# if defined(AU)
	printf("\t%2d  %s  %2d\n", day, mon[month-1], year);
	printf("\tChannel= %2d\n", channel_old);
	printf("\tStart time= %04d  Length= %3d\n", starttime, duration);
	printf("\tEnd time= %04d\n", end_time(starttime, duration));
	printf("\tG-code= %8ld\n", newspaper);
# endif
	return 0;
}
