# include	<stdio.h>


long
map_top( int day, int year, long top, int digits )
{
	long	d2, d1, d0, y, poot ;
	long	n2, n1, n0, f3, f2, f1, f0;

	y = year % 16 ;
	d2 = top / 100 ;
	d1 = (top % 100) / 10 ;
	d0 = top % 10 ;

	f0 = 1;
	f1 = (y + 1) % 10;
	f2 = ( ((y+1)*(y+2)) / 2 ) % 10 ;
	f3 = ( ((y+1)*(y+2)*(y+3)) / 6 ) % 10 ;


	if(digits == 1)
	{
		n0 = ( (d0*f0) + (day*f1) ) % 10 ;
		n1 = 0;
		n2 = 0;
	}

	if(digits == 2)
	{
		n0 = ( (d0*f0) + (d1*f1) + (day*f2) ) % 10 ;
		n1 = ( (d1*f0) + (day*f1) ) % 10 ;
		n2 = 0;
	}

	if(digits == 3)
	{
		n0 = ( (d0*f0) + (d1*f1) + (d2*f2) + (day*f3) ) % 10 ;
		n1 = ( (d1*f0) + (d2*f1) + (day*f2) ) % 10 ;
		n2 = ( (d2*f0) + (day*f1) ) % 10 ;
	}


	poot =  (100*n2) + (10*n1) + n0 ;

	return( poot );
}



long
unmap_top( int day, int year, long top, int digits )
{
	long	d2, d1, d0, y, poot ;
	long	n2, n1, n0, f3, f2, f1, f0, p3, p2, p1;

	d2 = top / 100 ;
	d1 = (top % 100) / 10 ;
	d0 = top % 10 ;

	/* generate key (P3P2P1F0) and reverse key (F3F2F1F0) */
	f0 = 1;
	y = year % 16 ;
	p1 = (y + 1) % 10;
	f1 = 10 - p1;

	p2 = ( ((y+1)*(y+2)) / 2 ) % 10 ;
	f2 = 10 - (p2 + f1*p1)%10;

	p3 = ( ((y+1)*(y+2)*(y+3)) / 6 ) % 10 ;
	f3 = 10 - (p3 + f1*p2 + f2*p1)%10;
# ifdef DEBUG
	printf("Forward key = %ld%ld%ld1\n", p3, p2, p1);
	printf("Reversing key = %ld%ld%ld1\n", f3, f2, f1);
	printf("Ndigits = %ld\n", digits);
# endif
	if(digits == 1)
	{
		n0 = ( (d0*f0) + (day*f1) ) % 10 ;
		n1 = 0;
		n2 = 0;
	}

	if(digits == 2)
	{
		n0 = ( (d0*f0) + (d1*f1) + (day*f2) ) % 10 ;
		n1 = ( (d1*f0) + (day*f1) ) % 10 ;
		n2 = 0;
	}

	if(digits == 3)
	{
		n0 = ( (d0*f0) + (d1*f1) + (d2*f2) + (day*f3) ) % 10 ;
		n1 = ( (d1*f0) + (d2*f1) + (day*f2) ) % 10 ;
		n2 = ( (d2*f0) + (day*f1) ) % 10 ;
	}


	poot =  (100*n2) + (10*n1) + n0 ;

	return( poot );
}


void
offset( int day, int year, long top, int *ofout, long *topout)
{
	int	i, digits, off;
	long	t, tx;
	long	pwr;


	pwr = 1 ; digits = 0;
	while(top >= pwr) { digits++; pwr *= 10; }
	pwr = pwr / 10 ;

	t = tx = top ;
	off = 0;
	while(tx > 0) { off += ( int )(tx % 10);   tx /= 10; }

again:
	for(i=0; i<=(year%16); i++)
		off += ( int )(map_top(day, i, t, digits) % 10);

	t = map_top(day, year, t, digits) ;
	if(t < pwr) goto again ;


	*ofout = off % 32;
	*topout = t;
	return;
}
