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

/* Master configuration file for WEB to C.  Almost all the definitions
   are wrapped with #ifndef's, so that you can override them from the
   command line, if you want to.  */

#ifndef __WEB2C_SITE_H
#define __WEB2C_SITE_H


/* Define if you're running under 4.2 or 4.3 BSD.  */
#ifndef BSD
#undef	BSD
#endif

/* Define if you're running under System V.  */
#ifndef SYSV
#undef	SYSV
#endif

/* I doubt if this works--There is a separate DOS version of MetaPost  */
#ifndef MS_DOS
#undef	MS_DOS
#endif

/* Define if you're running under a POSIX conforming OS  */
#ifndef _POSIX_SOURCE
#define	_POSIX_SOURCE
#endif

/* Define this if the system will be compiled with an ANSI C compiler,
   and never with a non-ANSI compiler.  It changes older versions of
   web2c so that they produce ANSI C as their output.  This may be a
   good idea, but you don't necessarily gain anything in the production
   programs by doing it.  With WEB2C Version 5.851 or later, always
   leave ANSI undefined.  */
#ifndef ANSI
#undef	ANSI
#endif

/* Define these according to your local setup.  Only the paths actually
   needed by MetaPost are define here.  */
#define	TEXFONTS	".:/usr/lib/tex/fonts/tfm"
#define	MFINPUTS	".:/usr/lib/mf"


/* MetaPost does not need window support, so nothing needs to be defined
   here.  */


/* Define to be the return type of your signal handlers.  POSIX says it
   should be `void', but some older systems want `int'.  Check your
   <signal.h> include file if you're not sure.  */
#ifndef SIGNAL_HANDLER_RETURN_TYPE
#define SIGNAL_HANDLER_RETURN_TYPE void
#endif

/* MetaPost doesn't use the `glueratio' type, so there is no need to
   typedef it here.  */


/* Define this if you want mp to be compiled with local variables
   declared as `register'.  On SunOS 3.2 and 3.4 (at least), compiling
   with cc, this may cause problems.  If you're using gcc or the SunOS
   4.x compiler, and compiling with -O, register declarations are
   ignored, so there is no point in defining this.  */
#ifndef REGFIX
#undef	REGFIX
#endif

/* If the type `int' is at least 32 bits (including a sign bit), this
   symbol should be #undef'd; otherwise, it should be #define'd.  If
   your compiler uses 16-bit int's, arrays larger than 32K may give you
   problems, especially if indices are automatically cast to int's.  */
#ifndef SIXTEENBIT
#undef	SIXTEENBIT
#endif

/* Our character set is 8-bit ASCII unless NONASCII is defined.  For
   other character sets, make sure that first_text_char and
   last_text_char are defined correctly (they're 0 and 255,
   respectively, by default).  In the *.defines files, change the
   indicated range of type `char' to be the same as
   first_text_char..last_text_char, `#define NONASCII', and retangle and
   recompile everything.  */
#ifndef NONASCII
#undef	NONASCII
#endif

/* Default editor command string: %d expands to the line number where
   TeX or Metafont found an error and %s expands to the name of the
   file.  The environment variables TEXEDIT and MFEDIT override this.  */
#define	EDITOR	"/bin/ed %s"

/* The type `schar' should be defined here to be the smallest signed
   type available.  ANSI C compilers may need to use `signed char'.  If
   you don't have signed characters, then define schar to be the type
   `short'.  */
typedef	signed char schar;

/* The type `integer' must be a signed integer capable of holding at
   least the range of numbers (-2^31)..(2^32-1).  The ANSI C
   standard says that `long' meets this requirement, but if you don't
   have an ANSI C compiler, you might have to change this definition.  */
typedef long integer;

/* Define MAXPATHLENGTH to be the maximum number of characters in a
   search path.  This is used to size the buffers for the environment
   variables.  It is good to be quite generous here.  */
#ifndef MAXPATHLENGTH
#define	MAXPATHLENGTH	5000
#endif

/* Define PATHEXP if you want mp, dvitomp, and dmp to understand
   double slashes "//" in the paths here and in the corresponding
   environment variables.  There can only be one "//" per path.  It means
   "expand zero or more levels of subdirectories, assuming that directories
   contain files or subdirectories, but not both".  This is for compatibility
   with recent versions of the Web2c distribution.  If you set it, be prepared
   to edit mp/pathexp.c.  That code has only been tested on one system.
*/
#ifndef PATHEXP
#undef PATHEXP
#endif


/*******************************************************************
  The following definitions are unique to MetaPost
*******************************************************************/

/* Where dvitomp looks for virtual fonts. (May be called TEXVFONTS in
   the WEB2C distribution.)  */
#define VFPATH		"/usr/lib/tex/fonts/psvf"

/* Where dmp looks for troff font tables */
#define TRFONTS		"/usr/lib/font/devpost"

/* Define FIXPT if you want to use the arithmetic routines in mp.web
   instead of the external routines in mpmath.c that use double precision
   floating point to compute the same results.  You should probably do
   this only if your machine does not have hardware floating point.
   If you aren't sure, go to the mp subdirectory, make timemath, and
   run the resulting test program.  It prints execution times for both
   versions of the arithmetic routines and warns if the floating point
   versions produce incorrect results. */
#undef FIXPT

/* MetaPost search paths (MetaPost also uses TEXFONTS and MFINPUTS.)
   Changes to all the paths listed below should probably be confined
   to globally replacing `/usr/lib/mp' with some other directory name. */
#define	MPINPUTS	".:/usr/lib/mp"
#define	MPMEMS		".:/usr/lib/mp"
#define	MPPOOL		".:/usr/lib/mp"

/*
 * Command for translating MetaPost input to an mpx file
 * (Can be overridden by an environment variable)
 */
#define MPXCOMMAND	"/usr/lib/mp/bin/makempx"
#define TROFFMPX	"/usr/lib/mp/bin/troffmpx"

/************ End of MetaPost stuff *******************************/


#include "defaults.h"

#endif /* __WEB2C_H */
