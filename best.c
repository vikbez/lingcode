# include	<stdio.h>
# include	<stdlib.h>

# include	"vcrplus.h"
# include	"best.h"

# define	SOFTLIMIT	2000

# ifdef HARNESS
static void	usage( void );
# endif

static int	add_time( int start, int dur );
static int	diffminutes( int start, int end );


# ifdef HARNESS
int
main( int argc, char *argv[] )
{
	int		reqstart, reqdur;
	unsigned long	best;

	if (argc != 3) {
		usage();
		exit(-1);
	}

	reqstart = atoi(argv[1]);
	reqdur = atoi(argv[2]);

	besttimes(&reqstart, &reqdur, &best);

	if (best) {
		printf("Exact match not found\n");
		printf("Best times: %04d/%d (heuristic %lu)\n",
				reqstart, reqdur, best);
	}
	else
		printf("Matched: %04d/%d\n", reqstart, reqdur);

	return 0;
}


static void
usage( void )
{

	printf("Usage: best <start> <dur>\n");
	return;
}
# endif


long
besttimes( int *rstart, int *rduration, unsigned long *heuristic )
{
	int		reqstart = *rstart, reqend;
#if defined(DE) || defined(AU)
	long		bestindex = INVALID;
#else
	long		bestindex;
#endif
	unsigned long	best, h, ds, de;
	int		start, end;
	long		index;

	reqend = add_time(reqstart, *rduration);
	best = ~0;

	for (index = 0; index < SOFTLIMIT; index++) {
		lookup(index, &start, &end);

		if (start > reqstart)
			continue;

		end = add_time(start, end);

		if (end < reqend)
			continue;

		/* heuristic */
		ds = diffminutes(reqstart, start);
		de = diffminutes(end, reqend);
		h = ds + de;

		if (h < best) {
			bestindex = index;
			best = h;
		}
	}

#if defined(DE) || defined(AU)
        if (bestindex != INVALID)
#endif
        {
	/* pass back values of rstart and rduration */
	lookup(bestindex, rstart, rduration);

	if (heuristic)
		*heuristic = best;
        }

	return bestindex;
}



static int
add_time( int start, int dur )
{
	int	min, hr;

	min = (start % 100) + (dur % 60);
	hr = (start / 100) + (dur / 60);

	while (min >= 60) {
		min -= 60;
		hr++;
	}

	start = hr*100 + min;
	return start;
}


static int
diffminutes( int start, int end )
{

	start = (start / 100)*60 + (start % 100);
	end = (end / 100)*60 + (end % 100);
	return start - end;
}
