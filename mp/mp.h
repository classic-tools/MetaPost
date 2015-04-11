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

/*
 * Main include file for MetaPost in C
 *
 * Based on Tim Morgan's mf.h of  2/12/88
 * Adapted to MetaPost by John Hobby
 */


#include <stdio.h>
#include "site.h"

#ifndef	BSD
#include <string.h>
#else
#include <strings.h>
#endif

/*
 * Some types we're going to need
 */
typedef FILE	*file_ptr;

/*
 * Global routines implemented as macros, plus some type coercion stuff.
 */

/* This is a workaround to a casting bug in the Sequent Dynix 2.1 C compiler */
#ifndef	sequent
#define	toint(x)	((integer) (x))
#else
#define	toint(x)	ztoint((integer)(x))
extern integer ztoint();
#endif

/* Older versions of web2c omit these defs when ANSI defined in site.h */
#ifdef ANSI
#define takefraction(x,y)	ztakefraction((integer)(x), (fraction)(y))
#define makefraction(x,y)	zmakefraction((integer)(x), (integer)(y))
#define takescaled(x,y)		ztakescaled((integer)(x), (scaled)(y))
#define makescaled(x,y)		zmakescaled((integer)(x), (integer)(y))
#endif

#define	inputln(file,flag)	zinputln(file)
#define	uexit(x)		exit((int) (x))
#define	incr(x)			++(x)
#define	decr(x)			--(x)
#define halfp(x)		((x) >> 1)
#define	flush(f)		(void) fflush(f)
#define	bwritebuf(a,b,c,d)	zbwritebuf(a,b,(integer)(c),(integer)(d))
#define	bwritebyte(f,b)		(void) putc((char)((b)&255), (f))
#define	bwrite2bytes(f,b)	zbwrite2bytes(f,(integer)(b))
#define	bwrite4bytes(f,b)	zbwrite4bytes(f,(integer)(b))
#define	abs(x)		zabs((integer) (x))
integer zabs();
#define	Fputs(stream, s)	(void) fputs(s, stream)
#define	read(f, c)	(c = getc(f))
#define readln(f)	{register c; while ((c=getc(f))!='\n' && c!=EOF); }
#define	true		1
#define	false		0
#define	chr(x)		(x)
#define get(x)		(void) getc(x)
#define	close(x)	if (x) (void) fclose(x)
#define	aclose(x)	if (x) (void) fclose(x)
#define	bclose(x)	if (x) (void) fclose(x)
#define	wclose(x)	if (x) (void) fclose(x)
#define odd(x)		((x)%2)

FILE *Fopen();
#define zfopen(f,n,m)	(f = Fopen(n+1, m)) != NULL
#define aopenin(f,p)	\
	(testaccess (nameoffile, realnameoffile, 4, (int)(p)) ? \
	zfopen(f, realnameoffile, "r") : false )
#define aopenout(f)	\
	(testaccess (nameoffile, realnameoffile, 2, 0) ? \
	zfopen(f, realnameoffile, "w") : false )
#define wopenin(f)	\
	(testaccess (nameoffile, realnameoffile, 4, 10) ? \
	zfopen(f, realnameoffile, "r") : false )
#define wopenout(f)	\
	(testaccess (nameoffile, realnameoffile, 2, 0) ? \
	zfopen(f, realnameoffile, "w") : false )

#ifdef _POSIX_SOURCE
#define bopenin(f)	\
	(testaccess (nameoffile, realnameoffile, 4, 3) ? \
	zfopen(f, realnameoffile, "rb") : false )
#define bopenout(f)	\
	(testaccess (nameoffile, realnameoffile, 2, 0) ? \
	zfopen(f, realnameoffile, "wb") : false )
#else
#define bopenin(f)	\
	(testaccess (nameoffile, realnameoffile, 4, 3) ? \
	zfopen(f, realnameoffile, "r") : false )
#define bopenout(f)	\
	(testaccess (nameoffile, realnameoffile, 2, 0) ? \
	zfopen(f, realnameoffile, "w") : false )
#endif


#define	amakenamestring(f)	makenamestring()
#define	bmakenamestring(f)	makenamestring()
#define	wmakenamestring(f)	makenamestring()

#ifdef	notdef
#define bopenin(b, n, p)	ybopenin(&(b), n, p)
#endif

#ifdef	SIXTEENBIT
#define	dumpint(x)	{integer x_val=(x); (void) fwrite((char *) &x_val, sizeof(x_val), 1, memfile);}
#else
#define	dumpint(x)	(void) putw((int)(x), memfile)
#endif
#define	dumpqqqq(x)	(void) fwrite((char *) &(x), sizeof(x), 1, memfile)
#define	dumpwd(x)	(void) fwrite((char *) &(x), sizeof(x), 1, memfile)
#define	dumphh(x)	(void) fwrite((char *) &(x), sizeof(x), 1, memfile)

#ifdef	SIXTEENBIT
#define	undumpint(x)	(void) fread((char *) &(x), sizeof(x), 1, memfile)
#else
#define	undumpint(x)	x = getw(memfile)
#endif
#define	undumpqqqq(x)	(void) fread((char *) &(x), sizeof(x), 1, memfile)
#define	undumpwd(x)	(void) fread((char *) &(x), sizeof(x), 1, memfile)
#define	undumphh(x)	(void) fread((char *) &(x), sizeof(x), 1, memfile)

#define dateandtime(a,b,c,d) ydateandtime(&(a), &(b), &(c), &(d))

/*
 * Global Data and Datastructures
 */

extern int argc;

/*
 * Global Data and Datastructures
 */

typedef union {
    struct {
	unsigned short RH, LH;
    } v;
    struct {
	unsigned short junk_space;	/* Make B0,B1 overlap LH in memory */
	unsigned char  B0, B1;
    } u;
} twohalves;
#define rh	v.RH
#define lhfield	v.LH
#define	b0	u.B0
#define	b1	u.B1

typedef struct {
    struct {
	unsigned char B0;
	unsigned char B1;
    } u;
    unsigned char b2;
    unsigned char b3;
} fourquarters;

typedef union {
    integer cint;
    twohalves hhfield;
    fourquarters qqqq;
} memoryword; 
