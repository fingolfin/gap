# Actual build rules are in GNUmakefile
.DEFAULT:
	@if test -f GNUmakefile ; then \
	    echo "Please use GNU make to build GAP (try 'gmake' or 'gnumake')" ; \
	  else \
	    echo "You need to run ./configure before make (please refer to INSTALL for details)" ; \
	  fi
all: .DEFAULT
