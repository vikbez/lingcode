# define	C4_BIT		0x1000000L
# define	C5_BIT		0x2000000L
# define	S4_BITS		0x0FFFFFFL

extern void	interleave( long tblidx, int cval, long *t8c5, int *t2c1 );
extern void	de_interleave( long t8c5, int t2c1, long *tval, int *cval );
