# include	<stdio.h>
# include	<stdlib.h>
# include	<time.h>

# include	"vcrplus.h"
# include	"ileave.h"
# include	"misc.h"
# include	"scramble.h"
# include	"b3.h"
# include	"top456.h"

long		debug = 0;


#ifdef DE
static char *mon[] = {  "Jan", "Feb", "MÑr", "Apr", "Mai", "Jun",
			"Jul", "Aug", "Sep", "Okt", "Nov", "Dez" };
#else
static char *mon[] = {  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
#endif


long
decode( int month_today, int date_today, int year_today, long newspaper )
{
	long	s1_out, top5;
	int	bot3, quo, rem, s5_out, ofout;
	long	mtout, tval;
	int	day_out, channel_out;
	int	starttime_out, duration_out ;

	year_today = year_today % 100 ;
	debug = 0;

	if ((month_today > 12) || (month_today < 1) ||
	      (date_today < 1) || (date_today > 31)) {
#ifdef DE
		fputs("\tUngÅltiges Datum!\n", stdout);
#else
		fputs("Invalid date\n", stdout);
#endif
                return -1;
	}

	if ((newspaper < 1) || (newspaper > 999999l)) {
#ifdef DE
		fputs("\tEs werden nur Codes mit maximal 6 Ziffern unterstÅtzt!\n", stdout);
#else
		fputs("Sorry, I can't process that code value\n", stdout);
		fputs(" I can only do codes with 6 digits or fewer\n", stdout);
#endif
                return -1;
	}

	ofout = INVALID ;
	mtout = INVALID ;

	s1_out = f1(newspaper, KEY001); 
	bot3 = ( int )(s1_out % 1000);
	top5 = s1_out / 1000;
	quo = (bot3 - 1) / 32 ;
	rem = (bot3 - 1) % 32 ;
	day_out = quo + 1;

	/* spot instances of next month's/year's codes - S.Hosgood, 8.Feb.93 */
	if (day_out < date_today) {
		month_today++;

		if (month_today > 12) {
			month_today = 1;
			year_today = (year_today+1) % 100;
		}
	}

	if (newspaper >= 1000)
		offset(day_out, year_today, top5, (&ofout), (&mtout)) ;
	else {
		mtout = 0;
		ofout = 0;
	}

	s5_out = (rem + (day_out*(month_today+1)) + ofout) % 32;

	de_interleave(mtout, s5_out, &tval, &channel_out);
	channel_out += 1;
        if (channel_out >= 20 && channel_out <= 32)
          channel_out += 80;
	lookup(tval, (&starttime_out), (&duration_out));

#if defined(US) || defined(UK)
	printf("\t%s  %2d  %2d\n\tChannel= %2d\n",
		mon[month_today-1], day_out, year_today, channel_out);
	printf("\tStart_time= %04d  Length= %3d\n",
		starttime_out, duration_out);
	printf("\tEnd_time= %04d\n",
		end_time(starttime_out, duration_out));
#endif

# ifdef DE
/*        printf("%lu:",newspaper); */
        if (mtout>1023)
          printf ("\tFehler !!! mtout > 1023 !!!\n");
        else
        {
	printf("\t%d. %s %2d\n\tKanal= %2d\n",
		day_out, mon[month_today-1], year_today, channel_out);
	printf("\tStartzeit= %04d  LÑnge= %3d\n",
		starttime_out, duration_out);
	printf("\tEndzeit= %04d\n",
		end_time(starttime_out, duration_out));
        }
#endif

# ifdef AU
	printf("\t%2d  %s  %2d\n\tChannel= %2d\n",
		day_out, mon[month_today-1], year_today, channel_out);
	printf("\tStart_time= %04d  Length= %3d\n",
		starttime_out, duration_out);
	printf("\tEnd_time= %04d\n",
		end_time(starttime_out, duration_out));
#endif

	return tval;
}


static void
usage( char *progname )
{
#ifdef DE
	printf(
"Syntax: %s [<Tag (1-31)> <Monat (1-12)> <Jahr (0-99)>] <ShowView Code>\n",
#endif
# ifdef US
	printf("Usage: %s [<Month (1-12)> <Day (1-31)> <Year (0-99)>] <VCR+ Number>\n",
# endif
# ifdef UK
	printf("Usage: %s [<Day (1-31)> <Month (1-12)> <Year (0-99)>] <VideoPlus Number>\n",
# endif
# ifdef AU
	printf("Usage: %s [<Day (1-31)> <Month (1-12)> <Year (0-99)>] <G-Code Number>\n",
# endif
								progname);
	return;
}


int
main(int argc, char *argv[])
{
	int		month_today, date_today, year_today;
	long		newspaper;
	time_t		time_today;
	struct tm	*ts;

	tzset();

	switch (argc) {
	case 2:
		/* use current time/date */
		time(&time_today);
		ts = localtime(&time_today);

		date_today = ts->tm_mday;
		month_today = ts->tm_mon + 1;
		year_today = ts->tm_year;

		newspaper = atol(argv[1]);
		break;

	case 5:
# ifdef US
		month_today = atoi(argv[1]);
		date_today = atoi(argv[2]);
#else
		date_today = atoi(argv[1]);
		month_today = atoi(argv[2]);
# endif
		year_today = atoi(argv[3]);
		newspaper = atol(argv[4]);
		break;

	default:
		usage("decode");
		return -1;
	}


	decode(month_today, date_today, year_today, newspaper);
	return 0;
}
