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

/* This program transforms a MetaPost input file into a Troff input
 * file by stripping out btex...etex and verbatimtex...etex sections.
 * Leading and trailing spaces and tabs are removed from the extracted
 * material and it is surrounded by the preceeding and following strings
 * defined immediately below.  The input file should be given as argument 1
 * and the resulting TeX file is written on standard output.
 */

#include <stdio.h>
#define bufsize 1000

char*	predoc = ".po 0\n";
char*	postdoc = "";
char*	pretex1 = ".lf %d %s\n";		/* first instance */
char*	pretex = ".bp\n.lf line %d %s\n";	/* subsequent instances */
char*	posttex = "\n";
char*	preverb = ".lf %d %s\n";
char*	postverb = "\n";

char *mpname;
FILE *mpfile;
int lnno = 0;		/* current line number */
int texcnt = 0;		/* btex..etex blocks so far */
char buf[bufsize];	/* the input line */
char *bb, *tt, *aa;	/* start of before, token, and after strings */

void usage(nam)
	char *nam;
{
	fprintf(stderr, "Usage: %s <mp-file>\n", nam);
	exit(1);
}

void err(msg)
	char *msg;
{
	fprintf(stderr, "! Error in %s at line %d: %s\n", mpname, lnno, msg);
	exit(1);
}

char *getline()	/* returns NULL on EOF or error, otherwise buf */
{
	char *s;

	if (fgets(buf, bufsize, mpfile)==NULL)
		return NULL;
	lnno++;
	for (s= &buf[1]; *s!='\0'; s++) /* do nothing */;
	if (s==&buf[bufsize-1] && s[-1]!='\n') err("Line is too long");
	s[-1] = '\0';
	return buf;
}


/* Return nonzero if a prefix of string s matches the null-terminated string t
 * and the next character is not a letter of an underscore.
 */
int match_str(s, t)
	char *s, *t;
{
	while (*t!=0) {
		if (*s!=*t) return 0;
		s++; t++;
	}
	switch (*s) {
	case 'a': case 'c': case 'd': case 'f': case 'g': case 'h':
	case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'w': case 'x': case 'y': case 'z': case '_':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
	case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
	case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
	case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
	case 'Y': case 'Z': case 'b': case 'e': case 'v':
		return 0;
	default:
		return 1;
	}
}


/* This function tries to express s as the concatination of three strings
 * b, t, a, with the global pointers bb, tt, and aa set to the start of the
 * corresponding strings.  String t is either a quote mark, a percent sign,
 * or an alphabetic token "btex", "etex", or "verbatimtex".  (An alphabetic
 * token is a maximal sequence of letters and underscores.)  If there are
 * several possible substrings t, we choose the leftmost one.  If there is
 * no such t, we set b=s and return 0.
 */
int getbta(s)
	char *s;
{
	int ok=1;	/* zero if last character was a-z, A-Z, or _ */

	bb = s;
	for (tt=bb; *tt!=0; tt++)
		switch (*tt) {
		case '"': case '%':
			aa = tt+1;
			return 1;
		case 'b':
			if (ok && match_str(tt,"btex")) {
				aa = tt+4;
				return 1;
			} else ok=0;
			break;
		case 'e':
			if (ok && match_str(tt,"etex")) {
				aa = tt+4;
				return 1;
			} else ok=0;
			break;
		case 'v':
			if (ok && match_str(tt,"verbatimtex")) {
				aa = tt+11;
				return 1;
			} else ok=0;
			break;
		case 'a': case 'c': case 'd': case 'f': case 'g': case 'h':
		case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
		case 'o': case 'p': case 'q': case 'r': case 's': case 't':
		case 'u': case 'w': case 'x': case 'y': case 'z': case '_':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
		case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
		case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
		case 'Y': case 'Z':
			ok = 0;
			break;
		default:
			ok = 1;
		}
	aa = tt;
	return 0;
}


void copytex()
{
	char *s;	/* where a string to print stops */
	char c;
	int ignore = 1;

	do {	if (*aa==0)
			if ((aa=getline())==NULL)
				err("btex section does not end");
			else if (--ignore<0) printf("\n");
		if (getbta(aa) && *tt=='e') {
			s = tt-1;
			while (s>=bb && (*s==' ' || *s=='\t'))
				s--;
			s++;
		} else {
			if (*tt=='b') err("btex in TeX mode");
			if (*tt=='v') err("verbatimtex in TeX mode");
			s = aa;
		}
		c = *s;
		*s = 0;
		printf("%s", bb);
		*s = c;
	} while (*tt!='e');
}


void do_line()
{
	aa = buf;
	while (getbta(aa))
		if (*tt=='%') break;
		else if (*tt=='"') {
			do if (!getbta(aa)) err("string does not end");
			while (*tt!='"');
		} else if (*tt=='b') {
			if (texcnt++ ==0) printf(pretex1,lnno,mpname);
			else printf(pretex,lnno,mpname);
			while (*aa==' ' || *aa=='\t') aa++;
			copytex();
			printf("%s",posttex);
		} else if (*tt=='v') {
			printf(preverb,lnno,mpname);
			while (*aa==' ' || *aa=='\t') aa++;
			copytex();
			printf("%s",postverb);
		} else err("unmatched etex");
}



void main(argc, argv)
	char *argv[];
{
	if (argc!=2) usage(argv[0]);
	mpname = argv[1];
	mpfile = fopen(mpname, "r");
	if (mpname==NULL) usage(argv[0]);
	printf("%s",predoc);
	while (getline()!=NULL)
		do_line();
	printf("%s",postdoc);
	exit(0);
}
