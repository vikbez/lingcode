# include	"misc.h"

int
end_time( int start, int dur )
{
	int	min, hr;

	min = (start % 100) + (dur % 60);
	hr = (start / 100) + (dur / 60);

	while (min >= 60) {
		min -= 60;
		hr++;
	}

	start = hr*100 + min;

	if (start >= 2400)
		start -= 2400;

	return start;
}
