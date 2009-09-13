# Copyright (C) 2003, 2008 International Business Machines and others
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id$

AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = INSTALL.HSL

noinst_LTLIBRARIES = libcoinhsl.la

nodist_libcoinhsl_la_SOURCES = dummy.c

if COIN_HAS_MA27
  nodist_libcoinhsl_la_SOURCES += ma27ad.f
endif

if COIN_HAS_MA57
  nodist_libcoinhsl_la_SOURCES += ma57ad.f
endif

if COIN_HAS_MC19
  nodist_libcoinhsl_la_SOURCES += mc19ad.f
endif

if COIN_HAS_MA28
  nodist_libcoinhsl_la_SOURCES += ma28ad.f ma30ad.f mc13dd.f mc20ad.f \
	mc21ad.f mc22ad.f mc23ad.f mc24ad.f
endif

lib_LTLIBRARIES =
if INSTALL_LOADABLE_LIBRARY
if EXTRA_SHARED_COMMAND
else
  lib_LTLIBRARIES += libhsl.la
  libhsl_la_SOURCES = $(nodist_libcoinhsl_la_SOURCES)
endif
endif

libcoinhsl_la_LDFLAGS = $(LT_LDFLAGS)

#############################################################################
#  Generating a shared library for delay loading

if EXTRA_SHARED_COMMAND

$(HSL_SHARED_LIB): $(noinst_LTLIBRARIES) $(DEFFILE)
	bla=; \
	for i in $(nodist_libcoinhsl_la_SOURCES); do \
	  case $$i in \
	    *.f) \
	      obj=`echo $$i| sed -e 's|\(.*\).[cf]|.libs/\1.$(OBJEXT)|g'` ;\
	      if test -r $$obj; then \
	        bla="$$bla $$obj" ;\
	      else \
	        bla="$$bla `echo $$i| sed -e 's|\(.*\).[cf]|\1.$(OBJEXT)|g'`" ;\
	      fi ;\
	      ;; \
	  esac ;\
	done ;\
	$(F77_SHARED_CMD) $$bla -o $(HSL_SHARED_LIB) $(F77_DLL_LINKFLAGS)

if NEED_DEFFILE
$(DEFFILE): config.status
	echo 'LIBRARY LIBHSL' > $(DEFFILE)
	echo 'EXPORTS' >> $(DEFFILE)
	for i in $(EXPORT_SYMBOLS); do \
	  echo "  $$i" >> $(DEFFILE); \
	done
endif

install-exec-local: $(HSL_SHARED_LIB)
	test -z "$(libdir)" || $(mkdir_p) "$(DESTDIR)$(libdir)"
	$(libLTLIBRARIES_INSTALL) $(HSL_SHARED_LIB) "$(DESTDIR)$(libdir)/$(HSL_SHARED_LIB)"

CLEANFILES = $(HSL_SHARED_LIB) $(DEFFILE)

uninstall-local:
	rm -f "$(DESTDIR)$(libdir)/$(HSL_SHARED_LIB)"
endif

########################################################################
#                         Maintainer Stuff                             #
########################################################################

# Files that are generated and should be cleaned with make distclean
DISTCLEANFILES =

include ../../BuildTools/Makemain.inc
