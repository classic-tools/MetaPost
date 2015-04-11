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
 * Main include file for TeXware in C.
 *
 * Tim Morgan  2/11/88
 */

#include <stdio.h>
#include "site.h"

/*
 * Global routines implemented as macros, plus some type coercion stuff.
 */

#define	toint(x)	((integer) (x))
#define	odd(x)		((x) % 2)
#define	putbyte(x,f)	putc((char) ((x)&255), f)
#define	round(x)	zround((double)(x))
#define incr(x)		++x
#define	decr(x)		--x
#define	trunc(x)	( (integer) (x) )
#define	readln(f)	{register c; while ((c=getc(f)) != '\n' && c != EOF);}
#define	read(f, b)	b = getc(f)
#define	input3ints(a,b,c)	zinput_3ints(&a, &b, &c)
#define zfseek(f,n,w)	(void) fseek(f, (long) n, (int) w)
#define eof(f)		test_eof(f)
#define	abs(x)		((x>=0)?(x):(-(x)))
#define	fabs(x)		((x>=0.0)?(x):(-(x)))
#define	Fputs(stream, s)	(void) fputs(s, stream)
#ifdef	OUT_BIN
#define	rewrite(f,n)	f = openf(n+1, "wb")
#define	reset(f,n)	((f)?fclose(f),(f=openf(n+1, "rb")):(f=openf(n+1,"rb")))
#else
#define rewrite(f,n)	f = openf(n+1, "w")
#define	reset(f,n)	((f)?fclose(f),(f=openf(n+1, "r")):(f=openf(n+1,"r")))
#endif
#define flush(f)	(void) fflush(f)
#define	true		1
#define	false		0
#define	chr(x)		(x)
#define	ord(x)		(x)
#define	vgetc(f)	(void) getc(f)
#define	uexit(x)	exit(x)

/*
 * Global types.
 */
typedef FILE	*text, *file_ptr;
typedef char	*ccharpointer;

/*
 * Global data and data structures.
 */

extern integer argc;
extern integer zround();
extern integer inputint();


/*
 * One global routine: test_eof
 * Return true if we're at the end of the file, else false.
 */
#ifdef ANSI /*prototype the function*/
int test_eof(FILE *);
#endif /*ANSI*/
test_eof(file)
FILE *file;
{
    int ch;

    if (feof(file))
	return(true);
    if ((ch = getc(file)) == EOF)
	return(true);
    (void) ungetc(ch,file); /* yuck */
    return(false);
}

#ifdef ANSI /* prototypes for all the functions.  */
extern  void argv(integer,char *);
extern  void main(int,char * *);
extern  int eoln(FILE *);
extern  FILE *openf(char *,char *);
extern  void setpaths(void);
extern  int testaccess(int,int);
extern  void packrealnameoffile(char * *);
extern  char *char_index(char *,char);
extern  void printreal(double,int,int);
extern  long zround(double);
extern  void main_body(void);
extern  void exit(int);
#else
FILE *openf();
void main_body();
#endif
