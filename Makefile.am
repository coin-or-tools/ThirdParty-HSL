# Copyright (C) 2003, 2009 International Business Machines and others
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id$

AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = INSTALL.HSL

thirdpartylibdir = $(libdir)/coin/ThirdParty
thirdpartylib_LTLIBRARIES = libcoinhsl.la

libcoinhsl_la_SOURCES = dummy.c

if COIN_HAS_MA27
  libcoinhsl_la_SOURCES += ma27ad.f
endif

if COIN_HAS_MA57
  libcoinhsl_la_SOURCES += ma57ad.f
endif

if COIN_HAS_MC19
  libcoinhsl_la_SOURCES += mc19ad.f
endif

if COIN_HAS_MA28
  libcoinhsl_la_SOURCES += ma28ad.f ma30ad.f mc13dd.f mc20ad.f \
	mc21ad.f mc22ad.f mc23ad.f mc24ad.f
endif

if COIN_HAS_MA77
  libcoinhsl_la_SOURCES += hsl_ma77d.f90 hsl_ma77d.deps90.f90 hsl_ma77d.deps77.f
endif

libcoinhsl_la_LDFLAGS = $(LT_LDFLAGS)

# dependencies
hsl_ma77d.lo: hsl_ma77d.deps90.lo

#############################################################################
#  Generating a shared library for delay loading

if EXTRA_SHARED_COMMAND

$(HSL_SHARED_LIB): $(thirdpartylib_LTLIBRARIES) $(DEFFILE)
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
	test -z "$(DESTDIR)$(libdir)/coin/ThirdParty" || $(mkdir_p) "$(DESTDIR)$(libdir)/coin/ThirdParty"
	$(libLTLIBRARIES_INSTALL) $(HSL_SHARED_LIB) "$(DESTDIR)$(libdir)/coin/ThirdParty/$(HSL_SHARED_LIB)"

uninstall-local:
	rm -f "$(DESTDIR)$(libdir)/coin/ThirdParty/$(HSL_SHARED_LIB)"
endif

pkgconfiglibdir = $(libdir)/pkgconfig
pkgconfiglib_DATA = coinhsl.pc

if COIN_HAS_PKGCONFIG
addlibsdir = $(DESTDIR)$(datadir)/coin/doc/ThirdParty/HSL
	
install-data-hook:
	@$(mkdir_p) "$(addlibsdir)"
	PKG_CONFIG_PATH=@COIN_PKG_CONFIG_PATH@ \
	$(PKG_CONFIG) --libs coinhsl > $(addlibsdir)/hsl_addlibs.txt

uninstall-hook:
	rm -f $(addlibsdir)/hsl_addlibs.txt
endif

test: $(libampl)
	@echo "No test available for HSL."

# Need to overwrite automake definition since otherwise libtool does not
# understand the fortran file (need to add --tag=F77)
LTFCCOMPILE = $(LIBTOOL) --tag=F77 --mode=compile $(FC) $(AM_FCFLAGS) $(FCFLAGS)


########################################################################
#                         Maintainer Stuff                             #
########################################################################

CLEANFILES = $(HSL_SHARED_LIB) $(DEFFILE)

# Files that are generated and should be cleaned with make distclean
DISTCLEANFILES =

include BuildTools/Makemain.inc
