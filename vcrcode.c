# include	<stdio.h>

# include	"scramble.h"


/* function that performs initial scrambling */
long
mixup( long x, long y )
{
	long	i, j, k, sum;
	long	a[12], b[12], out[20] ;

	/* get the digits of x into a[] */
	j = x ;
	for(i=0; i<9; i++)
	{
		k = j % 10;
		a[i] = k;
		j = (j - k) / 10 ;
	}

	/* get the digits of y into b[] */
	j = y ;
	for(i=0; i<9; i++)
	{
		k = j % 10;
		b[i] = k;
		j = (j - k) / 10 ;
		out[i] = 0;
	}


	for(i=0; i<=8; i++)
	{
		for(j=0; j<=8; j++)
		{
			out[i+j] += (b[j] * a[i]) ;
		}
	}

	j = 1;
	sum = 0;
	for(i=0; i<=8; i++)
	{
		sum += j * (out[i] % 10);
		j = j * 10 ;
	}
	return( sum ) ;
}


/* first function */
long
f1( long inval, long key )
{
	long	hashval, pwr;
	int	ndigits;

	if ((ndigits = nd(inval, &pwr)) > 8)
		printf("\nPANIC: %ld has %ld digits\n", inval, ndigits);

	pwr = pwr / 10 ;

	hashval = inval;
again:	hashval = mixup(hashval, key) % (pwr * 10) ;
	if(hashval < pwr) goto again ;

	return(hashval);
}



/* how many digits in a number? */
int
nd( long inval, long *p )
{
	int	ndigits;
	long	pwr;

	ndigits = 0;
	pwr = 1;
	while (inval >= pwr) {
		ndigits++;
		pwr *= 10;
	}

	*p = pwr;
	return ndigits;
}

void main (void)
{
  long t;

  scanf ("%lu", &t);

  printf ("encode: %lu\n", f1 (t, KEY002));
  printf ("decode: %lu\n", f1 (t, KEY001));
}
