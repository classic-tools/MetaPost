/****************************************************************
Copyright 1990 - 1995 by AT&T Bell Laboratories.

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the names of AT&T Bell Laboratories or
any of its entities not be used in advertising or publicity
pertaining to distribution of the software without specific,
written prior permission.

AT&T disclaims all warranties with regard to this software,
including all implied warranties of merchantability and fitness.
In no event shall AT&T be liable for any special, indirect or
consequential damages or any damages whatsoever resulting from
loss of use, data or profits, whether in an action of contract,
negligence or other tortious action, arising out of or in
connection with the use or performance of this software.
****************************************************************/

/* time.c -- produce a 1-page summary of cpu times of various C constructs
 * prints ? after CPU times if separate trials differ my more than
 * WARNRANGE times the mean.  Increase MINCLICKS (below) if this happens.
 * Possible portability problems
 *	might need to change jobclicks()
 *	microseconds column will have systematic errors if CLICKS_SEC is wrong
 */

#include <stdio.h>
#include <math.h>

#define WARNRANGE 0.4


#define EXTERN		/* instantiate data here */
#include "test_mpd.h"



#ifdef _POSIX_SOURCE
#include <time.h>

int jobclicks()
{
	return (int) clock();
}
#else
#include <sys/types.h>
#include <sys/times.h>

int jobclicks()
{
	struct	tms buffer;

	times(&buffer);
	return (int) (buffer.tms_utime + buffer.tms_stime);
}
#endif



#ifdef CLOCKS_PER_SEC
#define CLICKS_SEC	CLOCKS_PER_SEC
#else
#ifdef CLK_TCK
#define CLICKS_SEC	CLK_TCK
#else
#ifdef HZ
#define CLICKS_SEC	HZ
#else
#define CLICKS_SEC	60.0
#endif
#endif
#endif

#define MINCLICKS	(20+CLICKS_SEC/4)



/* This is unused when DEBUG is not set, but here it is anyway:
*/
void zconfusion(s)
	strnumber s;
{
	printf("Confusion! (case %ld)\n", s);
	exit(1);
}


/*************** Main macros for experiments ***************/

float	lastmics, basemics;	/* microsecs/iteration, same for null loop */
int	loop1start, loop1ctr;
int	minclicks, maxclicks, sumclicks, thisclicks;
int	loop2ctr, setn_clicks;
char	*queststr;

#define loop1(CODE,n)						\
	loop1ctr++;						\
	loop1start = jobclicks();				\
	for (loop2ctr=0; loop2ctr<n; loop2ctr++) { CODE; }	\
	thisclicks = jobclicks() - loop1start;			\
	sumclicks += thisclicks;				\
	if (thisclicks < minclicks) minclicks = thisclicks;	\
	if (thisclicks > maxclicks) maxclicks = thisclicks;	\
	printf(" %7d", thisclicks);				\
	fflush(stdout)

#define loop(LAB,CODE,n)					\
	printf("  %-28s", LAB);					\
	minclicks = 999999999; maxclicks = -1; sumclicks = 0;	\
	loop1ctr = 0;						\
	loop1(CODE,n);						\
	loop1(CODE,n);						\
	loop1(CODE,n);						\
	queststr = "";						\
	if (loop1ctr*(maxclicks-minclicks) > WARNRANGE*sumclicks)	\
		queststr = "?";						\
	lastmics = sumclicks*1000000.0/((float)CLICKS_SEC*n*loop1ctr);	\
	printf("%10.2f%s\n", lastmics - basemics, queststr)

#define setn(CODE,n)						\
	n=1;							\
	do {	n *= 10;					\
		setn_clicks = jobclicks();			\
		for (loop2ctr=0; loop2ctr<n; loop2ctr++){CODE;}	\
		setn_clicks = jobclicks() - setn_clicks;	\
	} while (setn_clicks < MINCLICKS);
	

#define title(TEXT,n) printf("%s (n=%d)\n", TEXT, n)

/* The experiment */

int test_arith();


long noop(p,q) long p,q; {return 17;}

main()
{
	int n;
	integer j1, j2 = 314159265, j3 = 358979323, j4=846264;

	if (test_arith() > 0) {
		printf("***** TEST FAILED! define FIXPT in site.h ******\n");
		exit(0);
	}

	printf("  Operation                     Clicks for each trial ");
	printf(" Microsecs/n\n");

	setn({}, n)
	title("Null Loop", n);
	basemics = 0.0;
	loop("{}", {}, n);
	basemics = lastmics;

	setn(j1=qtakefraction(j2,j3),n)
	title("Standard arithmetic (#define FIXPT)", n);
	loop("takefraction", j1=qtakefraction(j2,j3), n);
	loop("takescaled", j1=qtakescaled(j4,j4), n);
	loop("makefraction", j1=qmakefraction(j2,j3), n);
	loop("makescaled", j1=qmakescaled(j4,j4), n);

	setn(j1=ztakefraction(j2,j3),n);
	title("External arithmetic (#undef FIXPT)", n);
	loop("takefraction", j1=ztakefraction(j2,j3), n);
	loop("takescaled", j1=ztakescaled(j4,j4), n);
	loop("makefraction", j1=zmakefraction(j2,j3), n);
	loop("makescaled", j1=zmakescaled(j4,j4), n);
	exit(0);
}
