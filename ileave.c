# include	"vcrplus.h"
# include	"ileave.h"


/*
 * Ileave: Interleave and de-interleave routines.
 * The American routine shuffles the bits differently from the British.
 *
 *                     |
 * US:      T8|C5|T7|C4|T6|T5|T4|C3|C2|T3      T2|C1|T1|C0|T0
 * UK:     T10|T9|T8|T7|T6|T5|T4|C3|C2|T3      T2|C1|T1|C0|T0
 *                     |
 *
 * Break points between 4,5 and 6 and 7 digit codes are where the left inter-
 * leave gets to 9,99,999 or 9999. Assume the interleave of T2,T1,T0 and C1,C0
 * is all-ones.
 *
 * In the UK:
 *         T10|T9|T8|T7|T6|T5|T4|C3|C2|T3
 * 9(0x9)    0| 0| 0| 0| 0| 0| 1| 0| 0| 1  -> tblidx=00000011111, cval=000011.
 * 99(0x63)  0| 0| 0| 1| 1| 0| 0| 0| 1| 1  -> tblidx=00011001111, cval=000111.
 * 999(0x3E7)1| 1| 1| 1| 1| 0| 0| 1| 1| 1  -> tblidx=11111001111, cval=001111.
 *
 * The 4-digit break is at tblidx=31 on channel 4, or if we trade T4 to allow
 * C3 and C2 to be set, then it is at tblidx=15 on channel 16.
 * The 5-digit break is at tblidx=207 on channel 8, or if we trade T4 to allow
 * C3 to be set, then it is at tblidx=191 on channel 16.
 * The 6-digit break is at tblidx=1999 on channel 16, so no trade can be done.
 *
 * In the US:
 *          T8|C5|T7|C4|T6|T5|T4|C3|C2|T3
 * 9(0x9)    0| 0| 0| 0| 0| 0| 1| 0| 0| 1  -> tblidx=00000011111, cval=000011.
 * 99(0x63)  0| 0| 0| 1| 1| 0| 0| 0| 1| 1  -> tblidx=00001001111, cval=010111.
 * 999(0x3E7)1| 1| 1| 1| 1| 0| 0| 1| 1| 1  -> tblidx=00111001111, cval=111111.
 *
 * The 4-digit break is at tblidx=31 on channel 4, or if we trade T4 to allow
 * C3 and C2 to be set, then it is at tblidx=15 on channel 16.
 * The 5-digit break is at tblidx=79 on channel 24, or if we trade T6 to allow
 * C3 (and T5 and T4) to be set, then it is at tblidx=63 on channel 32. Or if
 * we trade C4 to allow T5 and T4 and C3 to be set, then it is at tblidx=127 on
 * channel 16.
 * The 6-digit break is at tblidx=463 on channel 64, or if we trade C4 to allow
 * T5 and T4 to be set, then it is at tblidx=511 on channel 48.
 *
 *
 * Notice that if the programme's code doesn't use bits C4 and up (i.e
 * channels 1-16), and if the timeslot index number doesn't use bits T7 and
 * up (tblidx <= 127) then US VCR+ and UK videoplus will produce the same
 * codes.
 */

void
interleave( long tblidx, int cval, long *t8c5, int *t2c1 )
{
	long	small;
	long	big, b;

	small = 0;
	big = 0;

	/* build t2c1 */
	b = 0x00000001 & (tblidx >> 2) ;
	small += (b << 4);

	b = 0x00000001 & (tblidx >> 1) ;
	small += (b << 2);

	b = 0x00000001 & tblidx ;
	small += b;

	b = 0x00000001 & (cval >> 1) ;
	small += (b << 3);

	b = 0x00000001 & cval ;
	small += (b << 1);


	/* build t8c5 */
# ifdef US
	b = 0x00000001 & (tblidx >> 8) ;
	big += (b << 9);

	b = 0x00000001 & (tblidx >> 7) ;
	big += (b << 7);

	b = 0x00000007 & (tblidx >> 4) ;
	big += (b << 3);

	b = 0x00000001 & (tblidx >> 3) ;
	big += b;

	b = 0x00000001 & (cval >> 5) ;
	big += (b << 8);

	b = 0x00000001 & (cval >> 4) ;
	big += (b << 6);

	b = 0x00000001 & (cval >> 3) ;
	big += (b << 2);

	b = 0x00000001 & (cval >> 2) ;
	big += (b << 1);
# endif

# ifdef UK
	b = 0x0000007F & (tblidx >> 4) ;
	big += (b << 3);

	b = 0x00000001 & (tblidx >> 3) ;
	big += b;

	b = 0x00000001 & (cval >> 3) ;
	big += (b << 2);

	b = 0x00000001 & (cval >> 2) ;
	big += (b << 1);

	/* for now, store the C4 and C5 bits way up high */
	big |= (cval & 0x10)? C4_BIT: 0;
	big |= (cval & 0x20)? C5_BIT: 0;
# endif
# ifdef UKC4KNOWN
	/* experiment to find position for C4 */
	b = 0x00000001 & (cval >> 4) ;
	big += (b << 13);
# endif

#if defined(DE) || defined(AU)
	b = 0x00000003 & (tblidx >> 9) ;
	big += (b << 9);

	b = 0x0000003F & (tblidx >> 3) ;
	big += (b << 1);

	b = 0x00000001 & (cval >> 4) ;
	big += (b << 8);

	b = 0x00000001 & (cval >> 3) ;
	big += (b << 7);

	b = 0x00000001 & (cval >> 2) ;
	big += b;
#endif

	*t8c5 = big;
	*t2c1 = ( int ) small;
	return;
}



void
de_interleave( long t8c5, int t2c1, long *tval, int *cval)
{
	long	cc = 0;
	long	tt = 0, b;

# ifdef DEBUG
	/* print extra bits */
	if (b = (t8c5 >> 10))
		printf("Incoming spare bits in 't8c5': 0x%0lX\n", b);
# endif

	/* get t8 thru t3 */
# ifdef US
	b = 0x00000001 & (t8c5 >> 9) ;
	tt += (b << 8);

	b = 0x00000001 & (t8c5 >> 7) ;
	tt += (b << 7);

	b = 0x00000007 & (t8c5 >> 3) ;
	tt += (b << 4);

	b = 0x00000001 & t8c5 ;
	tt += (b << 3);

	/* get c5 thru c2 */
	b = 0x00000001 & (t8c5 >> 8) ;
	cc += (b << 5);

	b = 0x00000001 & (t8c5 >> 6) ;
	cc += (b << 4);

	b = 0x00000003 & (t8c5 >> 1) ;
	cc += (b << 2) ;
# endif

# ifdef UK
/* US t8 -> UK t10 (Steve) */
/* US t7 -> UK t8 (Doug & Steve) */
/* US c5 -> UK t9 (Doug & Steve) */
/* US c4 -> UK t7 (Doug) */
	b = 0x0000007F & (t8c5 >> 3) ;
	tt += (b << 4);

	b = 0x00000001 & t8c5 ;
	tt += (b << 3);

	/* get c5 thru c2 */
	b = 0x00000003 & (t8c5 >> 1) ;
	cc += (b << 2) ;
# endif

#if defined(DE) || defined(AU)
	/* get t8 thru t3 */
	b = 0x00000001 & (t8c5 >> 10) ;
	tt += (b << 10);

	b = 0x00000001 & (t8c5 >> 9) ;
	tt += (b << 9);

	b = 0x0000003F & (t8c5 >> 1) ;
	tt += (b << 3);

	/* get c5 thru c2 */
	b = 0x00000001 & (t8c5 >> 8) ;
	cc += (b << 4);

	b = 0x00000001 & (t8c5 >> 7) ;
	cc += (b << 3) ;

	b = 0x00000001 & t8c5 ;
	cc += (b << 2);
#endif

	/* get t2 thru t0 */
	b = 0x00000001 & (t2c1 >> 4) ;
	tt += (b << 2);

	b = 0x00000001 & (t2c1 >> 2) ;
	tt += (b << 1);

	b = 0x00000001 & t2c1 ;
	tt += b;


	/* get c1 thru c0 */
	b = 0x00000001 & (t2c1 >> 3) ;
	cc += (b << 1);

	b = 0x00000001 & (t2c1 >> 1) ;
	cc += b ;

	*tval = tt;
	*cval = ( int ) cc;
	return;
}
