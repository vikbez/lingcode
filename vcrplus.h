/*
 * Shared stuff and function prototypes for Vcrplus decode/encode.
 */

# define	INVALID		(-987)

# define	LIMIT		2202
# define	SOFTLIMIT	2000 

extern long	scanfor( int start, int duration );
extern long	scanforstart( int start, long prev );
extern void	lookup( long i, int *outtime, int *outdur );
extern int	confirm( long index );
extern int	getduration( long index );
extern void	dump( void );
extern long	getguesses( void );
