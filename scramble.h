/*
 * All the scrambling algorithms.
 */


# define	KEY001		(68150631L)
# define	KEY002		(9371L)

extern long	mixup( long x, long y );
extern long	f1( long val, long key );
extern int	nd( long val, long *limit );
