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

#define EXTERN extern
#include "test_mpd.h"

int trouble;

void test1pp(p, q, f1, f2, lab)
	integer p, q;
	integer (*f1)();
	integer (*f2)();
	char *lab;
{
	integer r1, r2;
	char e1=' ', e2=' ';
	aritherror = 0;
	r1 = (*f1)(p,q);
	if (aritherror) e1='*';
	aritherror = 0;
	r2 = (*f2)(p,q);
	if (aritherror) e2='*';
	aritherror = 0;
	if (r1!=r2) {
		printf("%12s(%11d,%11d): %11d%c != %11d%c !\n",
			lab,p,q,r1,e1,r2,e2);
		trouble++;
	} else if (e1!=e2) {
		printf("%12s(%11d,%11d): %11d%c vs %11d%c !\n",
			lab,p,q,r1,e1,r2,e2);
		trouble++;
	}
}

void test1p(p, q, f1, f2, lab)
	integer p, q;
	integer (*f1)();
	integer (*f2)();
	char *lab;
{
	test1pp(p,q,f1,f2,lab);
	test1pp(p,-q,f1,f2,lab);
	test1pp(-p,q,f1,f2,lab);
	test1pp(-p,-q,f1,f2,lab);
}

#define TFargs	qtakefraction, ztakefraction, "takefraction"
#define TSargs	qtakescaled, ztakescaled, "takescaled"
#define MFargs	qmakefraction, zmakefraction, "makefraction"
#define MSargs	qmakescaled, zmakescaled, "makescaled"

/* Special values
	2^59-2^27+2^14 = 576460752169222144
	2^59-2^27      = 576460752169205760
	2^59-2^27-2^14 = 576460752169189376
	(10^9+1)*2^27+2^14 = 134217728134234112
	(10^9+1)*2^27      = 134217728134217728
	(10^9+1)*2^27-2^14 = 134217728134201344
	2^47-2^14    = 140737488338944
	2^47-2^15    = 140737488322560
	2^47-3*2^14  = 140737488306176
	(10^9+1)*2^15 = 32768000032768
	10^9*2^29+2^14 = 536870912000016384
	10^9*2^29      = 536870912000000000
	10^9*2^29-2^14 = 536870912999983616
	10^9*2^17+2^14 = 131072000016384
	10^9*2^17      = 131072000000000
	10^9*2^17-2^14 = 131072999983616
*/
int test_arith()
{
	trouble = 0;
	test1p(1265753777,106037786,TFargs);	/* p*q = (10^9+1)*2^27-6 */
	test1p(314159265,358979323,TFargs);
	test1p(846264,846264,TSargs);
	test1p(314159265,358979323,MFargs);
	test1p(846264,846264,MSargs);
	test1p(858993459,671088640,TFargs);	/* p*q = 2^59-2^27 */
	test1p(506217689,1138760586,TFargs);	/* p*q = 2^59-2^27-6 */
	test1p(478384883,1205014566,TFargs);	/* p*q = 2^59-2^27+18 */
	test1p(1102728503,522758549,TFargs);	/* p*q = 2^59-2^27+2^14+3 */
	test1p(361576106,1594299907,TFargs);	/* p*q = 2^59-2^27+2^14-2 */
	test1p(784709152,734617088,TFargs);	/* p*q = 2^59-2^27-2^14 */
	test1p(303680996,1898244407,TFargs);	/* p*q = 2^59-2^27-2^14-2 */
	test1p(702005182,821163101,TFargs);	/* p*q = 2^59-2^27-2^14+6 */
	test1p(1000000001,134217728,TFargs);	/* p*q = (10^9+1)*2^27 */
	test1p(173288715,774532422,TFargs);	/* p*q = (10^9+1)*2^27+2 */

	test1p(76342514,1758099401,TFargs);	/* p*q = (10^9+1)*2^27+2^14+2 */
	test1p(618554763,216986007,TFargs);	/* p*q = (10^9+1)*2^27-2^14-3 */
	test1p(858993459,163840,TSargs);	/* p*q = 2^47-2^15 */
	test1p(8177307,17210738,TSargs);	/* p*q = 2^47-2^15+6 */
	test1p(68066497,2067647,TSargs);	/* p*q = 2^47-2^15-1 */
	test1p(4196353,33538048,TSargs);	/* p*q = 2^47-2^14 */
	test1p(2586167,54419335,TSargs);	/* p*q = 2^47-2^14+1 */
	test1p(79105513,1779111,TSargs);	/* p*q = 2^47-2^14-1 */
	test1p(475136,296204641,TSargs);	/* p*q = 2^47-3*2^14 */
	test1p(14110593,9973889,TSargs);	/* p*q = 2^47-3*2^14+1 */
	test1p(972111817,144775,TSargs);	/* p*q = 2^47-3*2^14-1 */
	test1p(22257664,1472212,TSargs);	/* p*q = (10^9+1)*2^15 */
	test1p(3120967,10499310,TSargs);	/* p*q = (10^9+1)*2^15+2 */
	test1p(4891729,6698654,TSargs);		/* p*q = (10^9+1)*2^15-2 */
	test1p(858993459,163840,TFargs);	/* p*q = 2^47-2^15 */
	test1p(8177307,17210738,TFargs);	/* p*q = 2^47-2^15+6 */
	test1p(68066497,2067647,TFargs);	/* p*q = 2^47-2^15-1 */
	test1p(4196353,33538048,TFargs);	/* p*q = 2^47-2^14 */
	test1p(2586167,54419335,TFargs);	/* p*q = 2^47-2^14+1 */
	test1p(79105513,1779111,TFargs);	/* p*q = 2^47-2^14-1 */
	test1p(475136,296204641,TFargs);	/* p*q = 2^47-3*2^14 */
	test1p(14110593,9973889,TFargs);	/* p*q = 2^47-3*2^14+1 */
	test1p(972111817,144775,TFargs);	/* p*q = 2^47-3*2^14-1 */
	test1p(22257664,1472212,TFargs);	/* p*q = (10^9+1)*2^15 */
	test1p(3120967,10499310,TFargs);	/* p*q = (10^9+1)*2^15+2 */
	test1p(4891729,6698654,TFargs);		/* p*q = (10^9+1)*2^15-2 */
	test1p(8000,1000,MFargs);		/* 2^29*p+q=2q*(2^31)+1000 */
	test1p(1000000001,536870912,MFargs);	/* 2^29*p+q=2q*(5*10^8+1)+0 */
	test1p(1000000000,327705601,MFargs);	/* 2^29*p+q=2q*(819136003)-5 */
	test1p(1000000000,1346553211,MFargs);	/* 2^29*p+q=2q*(199350055)+1 */
	test1p(1000000000,667258220,MFargs);	/* 2^29*p+q=2q*(402296215)-2^14+4 */
	test1p(1000000000,226721939,MFargs);	/* 2^29*p+q=2q*(1183985358)-2^14-1 */
	test1p(1000000000,1995378729,MFargs);	/* 2^29*p+q=2q*(134528575)+2^14-5 */
	test1p(1000000000,300144206,MFargs);	/* 2^29*p+q=2q*(894354951)+2^14+10 */
	test1p(1000000001,131072,MSargs);	/* 2^17*p+q=2q*(5*10^8+1)+0 */
	test1p(1000000000,10916187,MSargs);	/* 2^17*p+q=2q*(6003562)-1 */
	test1p(1000000000,25884318,MSargs);	/* 2^17*p+q=2q*(2531881)+2 */
	test1p(1000000000,2775385,MSargs);	/* 2^17*p+q=2q*(23613301)-2^14-1 */
	return trouble;
}
