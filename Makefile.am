# Copyright (C) 2003, 2009 International Business Machines and others
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

AUTOMAKE_OPTIONS = foreign subdir-objects

EXTRA_DIST = INSTALL.HSL

includecoindir = $(includedir)/coin-or/hsl
includecoin_HEADERS = CoinHslConfig.h

lib_LTLIBRARIES = libcoinhsl.la

libcoinhsl_la_SOURCES = coinhsl/common/deps.f

if COIN_HAS_MC19
  libcoinhsl_la_SOURCES += coinhsl/mc19/mc19d.f
endif

if COIN_HAS_MA27
  libcoinhsl_la_SOURCES += coinhsl/ma27/ma27d.f
endif

if COIN_HAS_MA28
  libcoinhsl_la_SOURCES += coinhsl/ma28/ma28d.f
endif

if COIN_HAS_MA57
  libcoinhsl_la_SOURCES += coinhsl/ma57/ma57d.f
endif

if COIN_HAS_DEPSF90
  libcoinhsl_la_SOURCES += coinhsl/common/deps90.f90
endif

if COIN_HAS_HSL_MC68
  libcoinhsl_la_SOURCES += coinhsl/hsl_mc68/C/hsl_mc68i_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_mc68/C/hsl_mc68i.h
endif

if COIN_HAS_HSL_MA77
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma77/hsl_ma77d.f90 coinhsl/hsl_ma77/C/hsl_ma77d_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma77/C/hsl_ma77d.h
endif

if COIN_HAS_HSL_MA86
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma86/hsl_ma86d.f90 coinhsl/hsl_ma86/C/hsl_ma86d_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma86/C/hsl_ma86d.h
endif

if COIN_HAS_HSL_MA97
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma97/hsl_ma97d.f90 coinhsl/hsl_ma97/C/hsl_ma97d_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma97/C/hsl_ma97d.h
endif

if COIN_HAS_METIS
else
  libcoinhsl_la_SOURCES += metis_dummy.c
endif

libcoinhsl_la_LIBADD = $(HSL_LFLAGS)

libcoinhsl_la_LDFLAGS = $(LT_LDFLAGS)

# dependencies
#  need to define dependencies in terms of variables, since automake does not allow multiple rules for the same target
ma77=hsl_ma77d
ma86=hsl_ma86d
ma97=hsl_ma97d
mc68=hsl_mc68i
$(ma77).lo: deps90.lo
$(ma86).lo: deps90.lo
$(ma97).lo: deps90.lo
$(ma77)_ciface.lo: $(ma77).lo
$(ma86)_ciface.lo: $(ma86).lo
$(ma97)_ciface.lo: $(ma97).lo
$(mc68)_ciface.lo: deps90.lo

pkgconfiglibdir = $(libdir)/pkgconfig
pkgconfiglib_DATA = coinhsl.pc

test:
	@echo "No test available for HSL."

########################################################################
#                         Maintainer Stuff                             #
########################################################################

CLEANFILES = *.mod

# Files that are generated and should be cleaned with make distclean
DISTCLEANFILES =
