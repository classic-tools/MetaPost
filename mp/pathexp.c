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

#include "site.h"

#ifndef PATHEXP

void pathexpand(buf, dirlen, bufsize)
	char* buf;		/* input path */
	int dirlen;		/* limit search to buf[0]..buf[dirlen-1] */
	int bufsize;		/* number of character in buf array */
{
	/* NO-OP when PATHEXP is not defined */
}

#else

/**********************************************************
 You might have to modify the following includes and defines.
 They are supposed to declare opendir(), readdir(), closedir()
 and define how to access the result of readdir().
 **********************************************************/
#ifdef BSD
#include <sys/types.h>
#include <sys/dir.h>
#define DIRentry  struct direct		/* readdir() returns pointer to this */
#define de_name   d_name		/* field in DIRentry for file name */

#else
/* This is for SYSV and _POSIX_SOURCE; I don't know about other systems
 */
#include <dirent.h>
#define DIRentry  struct dirent		/* readdir() returns pointer to this */
#define de_name   d_name		/* field in DIRentry for file name */
#endif


/**********************************************************
 Nothing below here should need changing
 **********************************************************/

#include <stdio.h>

#ifndef	BSD
#include <string.h>
#else
#include <strings.h>
#endif

#ifdef _POSIX_SOURCE
#define	index	strchr
#define rindex	strrchr
#else
#ifdef	SYSV
#define	index	strchr
extern int sprintf ();
#else
extern char *sprintf ();
#endif /* SYSV */
#endif /* _POSIX_SOURCE */

/* C library routines and system calls.  */
extern char *index (), *rindex ();
extern void exit();
extern int access();


#ifdef PEDEBUG
/* The PEDEBUG flag is meant for seperate debugging of this file.  Do not
   set it when compiling MetaPost.
*/
int myaccess(nam, mode)
{
	int r;
	r = access(nam, mode);
	printf("can%s access %s\n", (r==0 ? "" : "not"), nam);
	return r;
}
#else
#define myaccess   access
#endif


void move_str(dest, src)		/* strcpy() for overlapping strings */
	char *dest, *src;
{
	char *s, *d;
	int n;

	if (dest < src) {
		while (*src != '\0')
			*dest++ = *src++;
		*dest = '\0';
	} else {
		n = strlen(src);
		d = dest + n;
		s = src + n;
		*d = '\0';
		while (s != src)
			*--d = *--s;
	}
}


/* Find the first "//" within the first dirlen characters of buf[], or return
 * zero to indicate failure.
 */
char* find_dblslash(buf, dirlen)
	char* buf;
	int dirlen;
{
	char* p;
	int k;

	k = 0;
	dirlen--;
	while ((p = index(buf+k, '/')) != 0) {
		if (p-buf >= dirlen)
			return 0;
		if (p[1]=='/')
			return p;
		k = 1 + p-buf;
	}
	return 0;
}


/* Pretend the string ends at endp and call opendir().
 */
DIR* pe_opendir(buf, endp)
	char *buf, *endp;
{
	DIR* dirp;
	char s;

	s = *endp;
	*endp = '\0';
	dirp = opendir(buf);
#ifdef PEDEBUG
	printf("%s directory %s\n", (dirp==0 ? "cannot open" : "opening"), buf);
#endif
	*endp = s;
	return dirp;
}


/* A file name begins at buf and has a slash at slash followed by a final
 * component of length tail.  Append one or more intermediate directories and
 * then the final component so as to make an accessible path name.  If this can
 * be done, return the length of the path name; otherwise return something
 * negative and leave buf set to a bad path name.  On exit, *tailp is pointed
 * to the tail string.  Buffer overflow happens when the tail string would have
 * to start at a position greater than lim.
 * The algorithm is depth-first search with pruning based on the idea that
 * directories contain files or subdirectories, but not both.
 */
int expand_dblslash(buf, slash, tail, lim, tailp)
	char *buf, *slash, *lim;
	int tail;
	char** tailp;
{
	DIR* dirp;
	DIRentry* de;
	char *t, *tt;		/* old and new positions of tail string */
	char *ds;
	int r;

	t = slash + 1;
	*tailp = t;
	dirp = pe_opendir(buf, slash);
	if (dirp==0)
		return -2;
	if (myaccess(buf, 04) == 0) {
		closedir(dirp);
		return (slash-buf) + 1 + tail;
	}
	while ((de = readdir(dirp)) != 0) {
		ds = de->de_name;
		if (ds[0]=='.' && (ds[1]==0 || ds[1]=='.' && ds[2]==0))
			continue;
		tt = slash + 2 + strlen(ds);
		if (tt > lim) {
			*slash = '\0';
			fprintf(stderr,"> %s/%s/%s\n", buf, de->de_name, t);
			fprintf(stderr,"! Fatal error: %s\n",
				"// expansion makes path name too long");
			exit(1);
		}
		move_str(tt, t);
		strcpy(slash+1, ds);
		tt[-1] = '/';
		r = expand_dblslash(buf, tt-1, tail, lim, &t);
		if (r != -1) {
			*tailp = t;
			return (r<0) ? -1 : r;
		}
	}
	closedir(dirp);
	*tailp = t;
	return -1;
}



/* Assume that buf points to an array of length at least bufsize that
 * contains a path name.  Modify the path name by expanding "//" if it occurs
 * in the first dirlen characters.  The expansions consist of zero or more
 * intermediate directories.  If the expansion fails, buf will contain an
 * invalid path name.
 */
void pathexpand(buf, dirlen, bufsize)
	char* buf;		/* input path */
	int dirlen;		/* limit search to buf[0]..buf[dirlen-1] */
	int bufsize;		/* number of character in buf array */
{
	char *p;
	int tail, junk;

	if ((p = find_dblslash(buf, dirlen)) != 0) {
		tail = strlen(p+1);
		move_str(p, p+1);
		expand_dblslash(buf, p, tail, buf+bufsize-tail-1, &junk);
	}
}

#endif /* PATHEXP */
