##################################
# Makefile for MetaPost in C	 #
##################################

SITEDIR	=..
CC=cc
OPT=-O
CFLAGS=$(OPT) -I$(SITEDIR)
LDFLAGS=$(OPT)
SHELL=/bin/sh
TANGLE=../web/tangle
TFTOPL=../texware/tftopl
PLTOTF=../texware/pltotf

#########################################################
# Everything below here should seldom need changing	#
#########################################################

OBJS= mp0.o mp1.o mp2.o mp3.o mp4.o mp5.o mp6.o mp7.o mp8.o mp9.o mp10.o
IOBJS=mpext.o mpmath.o pathexp.o inimp.o $(OBJS)
VOBJS=mpext.o mpmath.o pathexp.o imp.o $(OBJS)



.SUFFIXES:
.SUFFIXES: .o .c
.c.o:
		$(CC) $(CFLAGS) -c $*.c


default:	all

all:		inimp plain.mem mfplain.mem
triptrap:	etrapmp


inimp:		stamp-orig $(IOBJS)
		$(CC) $(LDFLAGS) -o inimp $(IOBJS)


# You don't need to make virmp because the change file makes inimp behave
# like virmp when not invoked with a -I switch.  The `virmp' target is provided
# just in case you want a separate executable that is slightly more compact.
virmp:		stamp-orig $(VOBJS)
		$(CC) $(LDFLAGS) -o virmp $(VOBJS)


# This target is only for testing arithmetic routines.  Run timemath with
# no arguments and use the results printed on standard output to decide if
# the external routines used when `FIXPT' is not defined in site.h work
# properly and run faster than the standard arithmetic routines.

timemath:	time.o cmath.o pmath.o mathtest.o
		$(CC) $(LDFLAGS) -o timemath time.o cmath.o pmath.o mathtest.o

time.o:     test_mpd.h mp.h
mathtest.o: test_mpd.h mp.h
pmath.o:   test_mpd.h mp.h
cmath.o:   test_mpd.h mp.h
	rm -f stamp-orig stamp-trap
	cp test_mpd.h mpd.h
	cp mpmath.c cmath.c
	$(CC) $(CFLAGS) -c cmath.c


trapf.tfm:	trapdir/trapf.pl
		$(PLTOTF) trapdir/trapf.pl trapf.tfm
	

# trapmp is a shell script that sets environment variables and runs etrapmp
#
run-triptrap:	etrapmp trapf.tfm
		-ln trapdir/mtrap.mp .
		-./trapmp -I mtrap
		-diff trapdir/mtrap.log mtrap.log
		-diff trapdir/mtrap.0 mtrap.0
		-diff trapdir/mtrap.1 mtrap.1
		-diff trapdir/writeo writeo
		-diff trapdir/writeo.2 writeo.2
		-ln trapdir/trap.mp .
		-ln trapdir/trap.mpx .
		touch trap.mpx
		-./trapmp -I <trapdir/trap1.in >/dev/null
		mv trap.log  trapin.log
		-diff trapdir/trapin.log trapin.log
		-./trapmp -I <trapdir/trap2.in >trap.fot
		-diff trapdir/trap.log trap.log
		-diff trapdir/trap.fot trap.fot
		-diff trapdir/trap.5 trap.5
		-diff trapdir/trap.6 trap.6
		-diff trapdir/trap.148 trap.148
		-diff trapdir/trap.149 trap.149
		-diff trapdir/trap.150 trap.150
		-diff trapdir/trap.151 trap.151
		-diff trapdir/trap.197 trap.197
		-diff trapdir/trap.200 trap.200
		$(TFTOPL) trap.tfm trap.pl
		-diff trapdir/trap.pl trap.pl


# After changing constants, making a trapmp is just like making an inimp.
# 
etrapmp:	stamp-trap $(IOBJS)
		$(CC) $(LDFLAGS) -o etrapmp $(IOBJS)



# Only one of stamp-trap and stamp-orig should exist at any given time.
# They just keep track of whether mpd.h came from trap_mpd.h or orig_mpd.h
#
stamp-trap:	stamp-convert
		cp trap_mpd.h mpd.h
		rm -f stamp-orig
		touch stamp-trap

stamp-orig:	stamp-convert
		cp orig_mpd.h mpd.h
		rm -f stamp-trap
		touch stamp-orig

# tangle produces mf.p and mf.pool.
# 
mp.p:		mp.web mp.ch
		$(TANGLE) mp.web mp.ch

# The convert script produces mp[0-9].c, imp.c, coerce.h, orig_mpd.h,
# and trapmpd.h.
#
stamp-convert:	mp.p fixcoerce.h mp.def fix.c
		$(CC) $(CFLAGS) $(LDFLAGS) -o fix fix.c -ll
		$(SHELL) ./convert
		touch stamp-convert

# This filter is used in ./convert; it might not be necessary anymore
# but the web2c version of METAFONT used to use it.
#
fix.c:		fix.lex
		lex fix.lex
		mv -f lex.yy.c fix.c

# The (generated) file imp.c has #ifdefs on INIMP, so we have to compile
# it with -DINIMP for inimp.
# 
inimp.o:	imp.c mp.h mpd.h		# mp.h is included by mpd.h.
		$(CC) $(CFLAGS) -DINIMP -c imp.c && mv imp.o inimp.o

$(OBJS) imp.o:	stamp-convert mp.h mpd.h	# mp.h is included by mpd.h.
mpext.o mpmath.o: mp.h mpd.h   			# mp.h is included by mpd.h.


# inimp requires mp.pool to be in one of the directories mentioned in the
# MPPOOL path from site.h.  This version should work if the path includes "."
#
plain.mem:	inimp
		./inimp -I ../mplib/plain dump

mfplain.mem:	inimp
		./inimp -I ../mplib/mfplain dump


clean:
		rm -f *mp*.o mpext.o pathexp.o  fix.o core
		rm -f trap.* trapin.log trapf.tfm fix inimp virmp etrapmp
		rm -f time.o mpmath.o mathtest.o timemath pmath.o cmath.*
		rm -f mtrap.* writeo writeo.2 *.mem

veryclean:	clean
		rm -f mp?.c mp1?.c imp.c tmp.c mpd.h coerce.h mp.pool mp.p \
			fix.c *.log stamp-* orig_mpd.h trap_mpd.h
		rm -f \#*\# *~ *.bak *.ckp core

