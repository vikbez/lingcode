# include	<stdio.h>
# include	<stdlib.h>

# include	"vcrplus.h"

# ifndef HARNESS
# define	qlookup		lookup
# define	qscanfor	scanfor
# define	qscanforstart	scanforstart
# define	qgetduration	getduration
# endif


#if defined(DE) || defined(AU)
struct s_tab {
	int	start;
	int	leng;
} slottable[LIMIT];

static int	initializer = 0;

static void store (int index, int start, int dur)
{
  slottable [index].start = start;
  slottable [index].leng  = dur;
}

int s_list [] = { 1900, 1930, 2000, 2030, 2100, 2130, 2200, 2230, 2300,
                  2330,    0, 1830, 1800, 1730, 1700, 1630, 1600, 1530,
                  1500, 1430, 1400, 1330, 1300, 1230, 1200, 1130, 1100,
                  1030, 1000,  930,  900,  830,  800,  730,  700,  630, 600};

static void fillS (int index, int dur, int cnt)
{
	int		i;
	struct s_tab	*sptr = &slottable[index];

        for (i = 0; i < cnt; i++, sptr++) {
                sptr->start = s_list [i];
                sptr->leng  = dur;
        }
}

static void fillTI (int index, int start, int dur)
{
        int             i;
	struct s_tab	*sptr = &slottable[index];

        for (i = 0; i < 5; i++, sptr++) {
                sptr->start = start + 5*i;
                sptr->leng  = dur;
        }
}

static void fillDD (int index, int start, int dur)
{
        int             i;
	struct s_tab	*sptr = &slottable[index];

        for (i = 0; i < 5; i++, sptr++) {
                sptr->start = start;
                sptr->leng  = dur - 5*i;
        }
}

static void
settables( void )
{
	int		j;
	struct s_tab	*sptr = &slottable[0];

	for (j = 0; j < LIMIT; j++) {
		sptr->start = sptr->leng = INVALID;
		sptr++;
	}

        fillS (0, 30, 37);  /* 30 min progs starting 600 -> 0 */
        fillS (37, 60, 37); /* 60 min progs starting 600 -> 0 */
        fillS (74, 90, 12); /* 90 min progs starting 1830 -> 0 */
        fillS (86, 120, 9); /* 120 min progs starting 1900 -> 2300 */
        store (95, 1500, 120);
	store (96, 1430, 120);
        store (97, 600, 150);
        fillTI (98, 5, 30); /* 30 min progs starting 5 -> 25 */
        fillTI (103, 1835, 30);
        fillTI (108, 1805, 30);
        fillTI (113, 1735, 30);
        fillTI (118, 1705, 30);
        fillDD (123, 1200, 25); /* 25 -> 5 min progs starting 1200 */
        fillDD (128, 1100, 25);
        fillDD (133, 1000, 25);
        fillDD (138, 900, 25);
        fillDD (143, 800, 25);
        fillDD (148, 700, 25);
        fillDD (153, 600, 25);
        fillDD (158, 1700, 55); /* 55 -> 35 min progs starting 1700 */
        fillDD (163, 1530, 55);
        fillDD (168, 1500, 55);
        fillDD (173, 1300, 55);
        fillDD (178, 1200, 55);
        fillTI (183, 5, 25); /* 25 min progs starting 5 -> 25 */
        fillTI (188, 1735, 25);
        fillTI (193, 1235, 25);
        fillTI (198, 1405, 45); /* 45 min progs starting 1405 -> 1425 */
        fillDD (203, 2015, 115); /* 115 -> 95 min progs starting 2015 */
        for (j = 0; j < 25; j++)
          fillDD (208 + j*5, s_list [j], 25);
        for (j = 0; j < 13; j++)
          fillDD (328 + j*5, s_list [j], 55);
        for (j = 0; j < 19; j++)
          store (393 + j, s_list [j+12], 90);
        for (j = 0; j < 16; j++)
          store (412 + j, s_list [j+9], 120);
        fillTI (428, 2005, 60);
        fillTI (433, 1605, 60);
        fillTI (438, 2035, 90);
        fillTI (443, 2235, 90);
        fillTI (448, 1505, 90);
        fillTI (453, 2035, 120);
        for (j = 0; j < 7; j++)
          fillTI (458+5*j, (1905+100*(j/2))+30*(j%2), 30);
        for (j = 0; j < 6; j++)
          fillTI (493+5*j, (1435-100*(j/2))-30*(j%2), 30);
        fillDD (523, 2200, 25);
        fillDD (528, 2230, 25);
        fillDD (533, 2300, 25);
        fillDD (538, 2330, 25);
        fillDD (543, 1330, 55);
        fillDD (548, 1900, 85);
        fillDD (553, 2300, 85);
        fillDD (558, 2030, 115);
        fillDD (563, 2200, 115);
        fillDD (568, 1800, 115);
        fillDD (573, 1100, 115);
        fillDD (578, 1530, 145);
        for (j = 0; j < 8; j++)
          fillTI (583+5*j, s_list[j]+5, 25);
        fillTI (623, 1405, 55);
        fillTI (628, 1335, 55);
        fillTI (633, 1305, 55);
        fillTI (638, 1605, 25);
        fillTI (643, 1435, 25);
        fillTI (648, 1335, 25);
        fillTI (653, 1905, 55);
        fillTI (658, 2005, 55);
        fillTI (663, 2335, 55);
        fillTI (668, 1835, 25);
        fillTI (673, 1705, 55);
        fillDD (678, 2035, 85);
        fillDD (683, 2105, 85);
        fillDD (688, 2035, 85);
        fillTI (693, 1905, 20);
        fillTI (698, 1935, 20);
        fillTI (703, 2135, 20);
        fillTI (708, 5, 20);
        fillTI (713, 1835, 20);
        fillTI (718, 1705, 20);
        fillTI (723, 1505, 20);
        fillTI (728, 2335, 50);
        fillTI (733, 1705, 50);
        fillDD (738, 2040, 115);
        fillTI (743, 1935, 15);
        fillTI (748, 1235, 15);
        fillTI (753, 2305, 45);
        fillDD (758, 2045, 85);
        fillDD (763, 2215, 85);
        fillDD (768, 2245, 85);
        fillDD (773, 2045, 115);
        fillDD (778, 2215, 115);
        fillDD (783, 2045, 145);
        fillDD (788, 2245, 145);
        for (j = 0; j < 6; j++)
          fillTI (793+j*5, s_list [j+11]+5, 15);
        for (j = 0; j < 6; j++)
          fillTI (823+j*5, s_list [j]+5, 45);
        fillTI (853, 1905, 10);
        fillTI (858, 1235, 10);
        fillTI (863, 2305, 40);
        fillDD (868, 2050, 85);
        fillDD (873, 2250, 85);
        fillDD (878, 2050, 115);
        fillDD (883, 1850, 115);
        fillDD (888, 1620, 115);
        for (j = 0; j < 13; j++)
          fillTI (893+5*j, s_list [j+12]+5, 40);
        fillTI (958, 1905, 35);
        fillTI (963, 2005, 35);
        fillTI (968, 2205, 35);
        fillDD (973, 2255, 115);
        fillDD (978, 1625, 115);
        for (j = 0; j < 9; j++)
          fillTI (983+j*5, s_list[j+12]+5, 35);

        /* Geht bis 1027 ! Ansatzpunkt ?
           1023 -> 1405 35 (letzter 6 stelliger Code)
           1024 -> 1410 35 (ab hier 7 stellige Codes
           1025 -> 1415 35  ABER nur, wenn Gemstar die Loopup-Table nicht
           1026 -> 1420 35  ge„ndert hat!)
           1027 -> 1425 35 */

	return;
}
#else
struct s_tab {
	int	start;
	int	leng;
} slottable[LIMIT] = {
/* first 192 entries are erratic, so pre-load them */
	{ 1830,	30 },
	{ 1600,	30 },
	{ 1930,	30 },
	{ 1630,	30 },
	{ 1530,	30 },
	{ 1730,	30 },
	{ 1800,	30 },
	{ 1430,	30 },
	{ 1900,	30 },
	{ 1700,	60 },
	{ 1400,	30 },
	{ 2030,	30 },
	{ 1700,	30 },
	{ 1600,	120 },
	{ 2000,	30 },
	{ 1500,	30 },
	{ 2000,	120 },
	{ 2100,	120 },
	{ 2000,	60 },
	{ 1800,	120 },
	{ 1900,	60 },
	{ 2200,	60 },
	{ 2100,	60 },
	{ 1400,	120 },
	{ 1500,	60 },
	{ 2200,	120 },
	{ 1130,	30 },
	{ 1100,	30 },
	{ 2300,	30 },
	{ 1600,	60 },
	{ 2100,	90 },
	{ 2100,	30 },
	{ 1230,	30 },
	{ 1330,	30 },
	{ 930,	30 },
	{ 1300,	60 },
	{ 2130,	30 },
	{ 1200,	60 },
	{ 1000,	120 },
	{ 1800,	60 },
	{ 2200,	30 },
	{ 1200,	30 },
	{ 800,	30 },
	{ 830,	30 },
	{ 1700,	120 },
	{ 900,	30 },
	{ 2230,	30 },
	{ 1030,	30 },
	{ 1900,	120 },
	{ 730,	30 },
	{ 2300,	60 },
	{ 1000,	60 },
	{ 700,	30 },
	{ 1300,	30 },
	{ 700,	120 },
	{ 1100,	60 },
	{ 1400,	60 },
	{ 1000,	30 },
	{ 800,	120 },
	{ 2330,	30 },
	{ 1300,	120 },
	{ 1200,	120 },
	{ 900,	120 },
	{ 630,	30 },
	{ 1800,	90 },
	{ 600,	30 },
	{ 530,	30 },
	{ 0,	30 },
	{ 2330,	120 },
	{ 2200,	90 },
	{ 1300,	90 },
	{ 900,	60 },
	{ 1630,	90 },
	{ 1600,	90 },
	{ 1430,	90 },
	{ 2000,	90 },
	{ 1830,	90 },
	{ 600,	60 },
	{ 1200,	90 },
	{ 30,	30 },
	{ 130,	120 },
	{ 0,	60 },
	{ 1700,	90 },
	{ 0,	120 },
	{ 800,	60 },
	{ 700,	60 },
	{ 2130,	120 },
	{ 500,	30 },
	{ 1530,	90 },
	{ 1130,	120 },
	{ 1100,	120 },
	{ 830,	90 },
	{ 2230,	90 },
	{ 900,	90 },
	{ 2130,	90 },
	{ 1630,	120 },
	{ 2330,	60 },
	{ 100,	120 },
	{ 1400,	90 },
	{ 130,	30 },
	{ 330,	120 },
	{ 1500,	90 },
	{ 1500,	120 },
	{ 2300,	120 },
	{ 1900,	90 },
	{ 800,	90 },
	{ 430,	30 },
	{ 300,	30 },
	{ 1330,	120 },
	{ 1000,	90 },
	{ 700,	90 },
	{ 100,	30 },
	{ 2330,	90 },
	{ 330,	30 },
	{ 200,	30 },
	{ 2230,	120 },
	{ 400,	30 },
	{ 600,	120 },
	{ 400,	120 },
	{ 230,	30 },
	{ 630,	90 },
	{ 30,	60 },
	{ 2230,	60 },
	{ 100,	60 },
	{ 30,	120 },
	{ 2300,	90 },
	{ 1630,	60 },
	{ 830,	60 },
	{ 0,	90 },
	{ 1930,	120 },
	{ 930,	120 },
	{ 2030,	90 },
	{ 500,	60 },
	{ 1730,	60 },
	{ 200,	120 },
	{ 1930,	90 },
	{ 930,	90 },
	{ 1730,	120 },
	{ 630,	120 },
	{ 1830,	60 },
	{ 1430,	60 },
	{ 1130,	90 },
	{ 30,	90 },
	{ 830,	120 },
	{ 1030,	90 },
	{ 1430,	120 },
	{ 100,	90 },
	{ 730,	120 },
	{ 2030,	120 },
	{ 300,	90 },
	{ 300,	120 },
	{ 1330,	90 },
	{ 1230,	90 },
	{ 230,	90 },
	{ 2130,	60 },
	{ 1130,	60 },
	{ 1830,	120 },
	{ 630,	60 },
	{ 530,	60 },
	{ 200,	60 },
	{ 1530,	120 },
	{ 730,	60 },
	{ 600,	90 },
	{ 1730,	90 },
	{ 400,	60 },
	{ 730,	90 },
	{ 430,	90 },
	{ 430,	60 },
	{ 130,	90 },
	{ 1230,	120 },
	{ 130,	60 },
	{ 230,	120 },
	{ 1930,	60 },
	{ 300,	60 },
	{ 1030,	120 },
	{ 200,	90 },
	{ 330,	60 },
	{ 500,	120 },
	{ 930,	60 },
	{ 230,	60 },
	{ 2030,	60 },
	{ 400,	90 },
	{ 1530,	60 },
	{ 430,	120 },
	{ 1330,	60 },
	{ 1230,	60 },
	{ 330,	90 },
	{ 1030,	60 },
	{ 500,	90 },
	{ 530,	120 },
	{ 530,	90 },
	{ 1100,	90 }
};

static int	initializer = 0;
static int	change = 0;

static void	fillQHB( int index, int dur );
static void	fillHHB( int index, int dur );
static void	fill( int index, int time, int dur);


static void
settables( void )
{
	int		j;
	struct s_tab	*sptr = &slottable[192];

	for (j = 192; j < LIMIT; j++) {
		sptr->start = sptr->leng = INVALID;
		sptr++;
	}

	fillQHB(192, 30);	/* 30min progs starting 0015 -> 2345 */
	fillQHB(240, 60);
	fillQHB(288, 90);
	fillQHB(336, 120);
	fill(384, 2230, 30);	/* 30 ->5 min progs starting 2230 -> 2255 */
	fill(418, 2300, 30);
	fill(452, 2330, 30);
	fill(486, 1930, 90);	/* 90 -> 65min progs starting 1930 -> 1955 */
	fill(520, 2300, 90);	/* 90 -> 65min progs starting 2300 -> 2325 */
	fill(554, 2330, 90);
	fill(588, 2130, 120);	/* 120 -> 95min progs starting 2130 -> 2155 */
	fill(622, 2200, 120);
	fill(656, 2300, 120);	/* 120 -> 95min progs starting 2300 -> 2325 */
	fill(690, 2330, 120);
	fill(724, 0, 120);
	fill(758, 30, 120);
	fill(792, 100, 120);
	fill(826, 130, 120);
	fill(860, 1730, 60);	/* 60 -> 35min progs starting 1730 -> 1755 */
	fill(894, 1800, 60);
	fill(928, 1830, 60);
	fill(962, 1900, 60);
	fill(996, 1930, 60);
	fill(1030, 2000, 60);
	fill(1064, 2030, 60);
	fill(1098, 200, 120);	/* 120 -> 95min progs starting 0200 -> 0225 */
	fill(1132, 230, 120);
	fill(1166, 300, 120);
	fill(1200, 330, 120);
	fill(1234, 400, 120);
	fill(1268, 1200, 120);
	fill(1302, 1400, 120);
	fill(1336, 1530, 120);
	fill(1370, 2100, 60);	/* 60 -> 35min progs starting 2100 -> 2125 */
	fill(1404, 2130, 60);
	fill(1438, 2200, 60);
	fill(1472, 2230, 60);
	fill(1506, 2300, 60);
	fill(1540, 2330, 60);
	fill(1574, 1730, 30);	/* 30 -> 5min progs starting 1730 -> 1755 */
	fill(1608, 1800, 30);
	fill(1642, 1830, 30);
	fill(1676, 1900, 30);
	fill(1710, 1930, 30);
	fill(1744, 2000, 30);
	fill(1778, 2030, 30);
	fill(1812, 2100, 30);
	fill(1846, 2130, 30);
	fill(1880, 2200, 30);
	fillHHB(1914, 150);	/* 150min progs starting 2330 -> 0000 */
	fillHHB(1962, 180);	/* 180min progs starting 2330 -> 0000 */
	return;
}


/* insert movie (and other) structured tables */
int tlist[] = { 5, 10, 20, 25,
		0, 5, 10, 15, 20, 25,	/* -5 */
		0, 5, 10, 15, 20, 25,	/* -10 */
		0, 5, 10, 15, 20, 25,	/* -15 */
		0, 5, 10, 15, 20, 25,	/* -20 */
		0, 5, 10, 15, 20, 25	/* -25 */
};

int dlist[] = { 0, 0, 0, 0,
		-5, -5, -5, -5, -5, -5,
		-10, -10, -10, -10, -10, -10,
		-15, -15, -15, -15, -15, -15,
		-20, -20, -20, -20, -20, -20,
		-25, -25, -25, -25, -25, -25
};


static void
fill( int index, int time, int dur)
{
	int		i;
	struct s_tab	*sptr = &slottable[index];

	for (i = 0; i < 34; i++, index++) {
		sptr->start = time + tlist[i];
		sptr->leng = dur + dlist[i];
		sptr++;
	}

	change = 1;
	return;
}

static void
fillQHB( int index, int dur )
{
	int		i;
	struct s_tab	*sptr = &slottable[index];

	for (i = 0; i < 24; i++) {
		sptr->start = i*100 + 15;
		sptr->leng = dur;
		sptr++;
		sptr->start = i*100 + 45;
		sptr->leng = dur;
		sptr++;
	}

	change = 1;
	return;
}


static void
fillHHB( int index, int dur )
{
	int		i;
	struct s_tab	*sptr = &slottable[index];

	for (i = 23; i >= 0; i--) {
		sptr->start = i*100 + 30;
		sptr->leng = dur;
		sptr++;
		sptr->start = i*100;
		sptr->leng = dur;
		sptr++;
	}

	change = 1;
	return;
}
#endif


void
qlookup( long i, int *outtime, int *outdur )
{

	if(initializer == 0) {
		initializer = 1;
		settables();
	}

	
	if((i >= LIMIT) || (i < 0))
#ifdef DE
		printf("\nFehler !!! Ungltiger Tabellenindex %ld !!!\n", i);
#else
		printf("\nPANIC, Illegal table index %ld\n", i);
#endif

	if (i >= SOFTLIMIT) {
		/* anything above here is hypothetical anyway */
		*outtime = *outdur = INVALID;
		return;
	}

	fflush(stdout);
	*outtime = slottable[i].start;
	*outdur = slottable[i].leng;
	return;
}


long
qscanfor( int s, int d )
{
	long	j;

	if (initializer == 0) {
		initializer = 1;
		settables();
	}

	for (j = 0; j < SOFTLIMIT; j++) {
		if (slottable[j].start == s && slottable[j].leng == d) {
			/* printf("Match at %d", j); */
			return j;
		}
	}

	return -1L;
}


long
qscanforstart( int s, long prev )
{
	long	j;

	if (initializer == 0) {
		initializer = 1;
		settables();
	}

	for (j = prev+1; j < SOFTLIMIT; j++) {
		if (slottable[j].start == s) {
			/* printf("Match at %d", j); */
			return j;
		}
	}

	return -1L;
}

int
qgetduration( long index )
{

	return slottable[index].leng;
}
