# Directory that site.h is in. (`..' means the directory containing
# this Makefile.)
# 
SITEDIR=..

# Default C compiler.
CC=cc

# Default flags to give the C compiler.  (Don't define CFLAGS directly.)
OPT=-O

# Default flags to give to the loader.
LDFLAGS=


default: all


##########################################################################
# The next few lines could be merged with the top-level makefile in the
# web2c distribution, but I don't recommend it.
##########################################################################

# You only need to define these if you are going to do `make install',
# instead of installing the programs by hand.  They should match
# directories listed in the paths you define in ./site.h.
# 
INSTALL=cp
bindir=/usr/local/bin
mpname=mp			# name of main executable
makempxbin=/usr/lib/mp/bin	# must match MPXCOMMAND and TROFFMPX in site.h
#				  mppooldir must match MPPOOL in site.h
mppooldir=/usr/lib/mp
memdir=/usr/lib/mp		# must match MPMEMS in site.h
mpinputs=/usr/lib/mp		# must match MPINPUTS in site.h
texinputs=/usr/lib/tex/macros
texdocs=/usr/lib/tex/macros/doc


alldirs=mp mpware
triptrapdirs=mp

tex-install:
	$(INSTALL) mp/inimp $(bindir)/$(mpname)
	if test -s mp/mp.pool; then $(INSTALL) mp/mp.pool $(mppooldir); fi
	-$(INSTALL) mp/*.mem $(memdir)
	$(INSTALL) mpware/newer $(makempxbin);
	$(INSTALL) mpware/dvitomp mpware/makempx mpware/mptotex $(makempxbin)
	$(INSTALL) mplib/psfonts.map $(mppooldir)
	$(INSTALL) mplib/*.mp $(mpinputs)
	$(INSTALL) mplib/mproof.tex $(texinputs)
	$(INSTALL) doc/mpintro.* $(texdocs)
	$(INSTALL) doc/examples.mp $(mpinputs)

install:	tex-install
	$(INSTALL) mpware/dmp mpware/troffmpx mpware/mptotr $(makempxbin)
	$(INSTALL) mplib/trfonts.map mplib/trchars.adj $(mppooldir)
	-mkdir $(mppooldir)/charlib
	$(INSTALL) mplib/charlib/* $(mppooldir)/charlib

############################# end of lines to merge ##############################




############################################################
# Everything Below Here Should Seldom Need Changing        #
############################################################



makeargs=SITEDIR="$(SITEDIR)" CC="$(CC)" OPT="$(OPT)" \
SHELL="$(SHELL)" LDFLAGS="$(LDFLAGS)"

# Make sure we use the sh.  If your sh is broken, you might try bash,
# the GNU version.
# 
SHELL=/bin/sh


# This target is no longer needed.  You don't need to make `triptrap` before
# making `run-triptrap' since the Makefiles have the necessary dependencies.
triptrap:
	for name in $(triptrapdirs); \
        do \
          (cd $${name}; make $(makeargs) triptrap); \
        done  

run-triptrap:
	cd mp; make $(makeargs) run-triptrap
	cd mpware; make $(makeargs) run-triptrap


# This target is no longer needed.  You don't need to make `clean-triptrap'
# before making `all' since the Makefiles have the necessary dependencies.
clean-triptrap:
	cd mp; make veryclean
	cd mpware; make clean


all:
	for name in $(alldirs); \
	do \
	  (cd $${name}; echo $${name}; make $(makeargs) all); \
	done

clean:
	for name in $(alldirs); \
	do \
	  (cd $${name}; make clean); \
	done

veryclean:
	for name in $(alldirs); \
	do \
	  (cd $${name}; make veryclean); \
	done
	rm -f \#*\# *~ *.bak *.ckp core
