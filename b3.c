# include	"b3.h"

void
decode_bot3( int bot3, int *day, int *rem )
{

	*day = ((bot3 - 1) / 32) + 1;
	*rem = (bot3 - 1) % 32;
	return;
}

int
encode_bot3( int day, int rem )
{

	return rem + (32 * (day - 1)) + 1;
}
