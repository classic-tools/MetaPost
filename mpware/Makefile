#########################################################
# Makefile for MetaPost support programs                #
#########################################################

SITEDIR	=..
CC=cc
OPT=-O
CFLAGS=$(OPT) -I$(SITEDIR)
LDFLAGS=$(OPT)
SHELL=/bin/sh
TANGLE=../web/tangle

#########################################################
# Everything below here should seldom need changing	#
#########################################################

.SUFFIXES:
.SUFFIXES: .o .c .p .ch
.p.c:
		$(SHELL) ./convert $*.p $*.c
.ch.p:
		$(TANGLE) $*.web $*.ch
.c.o:
		$(CC) $(CFLAGS) -c $*.c


default:	all

all:		tex troff
tex:		dvitomp mptotex newer
troff:		dmp mptotr newer


# Don't test mptotr because its source file is identical to mptotex.c
# except for a few string constants.
# This will abort if either diff returns nonzero exit status
# otherwise the test is considered passed.
run-triptrap:	mptotex newer
		./mptotex testex.mp | diff testex.tex -
		sed '16s/^%//' <testex.mp >testex1
		-mptotex testex1 >/dev/null 2>testex2
		sed '17s/^%//' <testex.mp >testex1
		-mptotex testex1 >/dev/null 2>>testex2
		sed '18s/^%//' <testex.mp >testex1
		-mptotex testex1 >/dev/null 2>>testex2
		sed '19s/^%//' <testex.mp >testex1
		-mptotex testex1 >/dev/null 2>>testex2
		sed '20s/^%//' <testex.mp >testex1
		-mptotex testex1 >/dev/null 2>>testex2
		diff testex.err testex2

# DVItoMP
dvitomp:	dvitomp.o dvimpext.o pathexp.o
		$(CC) $(CFLAGS) -o dvitomp dvitomp.o dvimpext.o pathexp.o
dvimpext.o:	dvimpext.c ${SITEDIR}/site.h
dvitomp.o:	dvitomp.c mpware.h
dvitomp.c:	dvitomp.p mpware.def
dvitomp.p:	dvitomp.web dvitomp.ch

pathexp.o:	../mp/pathexp.c
		cp ../mp/pathexp.c .
		$(CC) $(CFLAGS) -c pathexp.c


# MPtoTEX
mptotex:	mptotex.o
		$(CC) $(CFLAGS) -o mptotex mptotex.o

# MPtoTR
mptotr:		mptotr.o
		$(CC) $(CFLAGS) -o mptotr mptotr.o

# DMP
dmp:		dmp.o pathexp.o
		$(CC) $(CFLAGS) -o dmp dmp.o pathexp.o -lm

# newer  (the default rules suffice)


clean:
	rm -f dvitomp.p dvitomp.pool *.o testex1 testex2
	rm -f dvitomp mptotex mptotr dmp newer pathexp.c
veryclean:	clean
	rm -f dvitomp.c dvitomp.h \#*\# *~ *.bak *.ckp core
