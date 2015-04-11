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

/* Include site.h in case it defines _POSIX_SOURCE */
#include "site.h"

#include <sys/types.h>
#include <sys/stat.h>

/*
 *	newer x y
 *
 *	returns 0 if x exists and y does not, or if
 *	files x and y both exist and x was modified
 *	at least as recently as y, and nonzero otherwise.
 */

main (argc, argv)
	int argc;
	register char **argv;
{
	struct stat x, y;

	/* insist on exactly two args */
	if (argc != 3)
		exit(1);
	
	/* does the first file exist? */
	if (stat (argv[1], &x) < 0)
		exit(1);
	
	/* does the second file exist? */
	if (stat (argv[2], &y) < 0)
		exit(0);
	
	/* fail if the first file is older than the second */
	if (x.st_mtime < y.st_mtime)
		exit(1);
	
	/* otherwise, succeed */
	exit(0);
}
