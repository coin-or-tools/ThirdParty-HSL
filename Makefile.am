# Copyright (C) 2003, 2009 International Business Machines and others
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

includecoindir = $(includedir)/coin-or/hsl
includecoin_HEADERS = CoinHslConfig.h

lib_LTLIBRARIES = libcoinhsl.la

libcoinhsl_la_SOURCES =

if COIN_HAS_MC19
  libcoinhsl_la_SOURCES += coinhsl/mc19/mc19d.f
endif
if COIN_HAS_MC19S
  libcoinhsl_la_SOURCES += coinhsl/mc19/mc19s.f
endif

if COIN_HAS_MA27
  libcoinhsl_la_SOURCES += coinhsl/ma27/ma27d.f
endif
if COIN_HAS_MA27S
  libcoinhsl_la_SOURCES += coinhsl/ma27/ma27s.f
endif

if COIN_HAS_MA28
  libcoinhsl_la_SOURCES += coinhsl/ma28/ma28d.f
endif
if COIN_HAS_MA28S
  libcoinhsl_la_SOURCES += coinhsl/ma28/ma28s.f
endif

if COIN_HAS_MA57
  libcoinhsl_la_SOURCES += coinhsl/ma57/ma57d.f
endif
if COIN_HAS_MA57S
  libcoinhsl_la_SOURCES += coinhsl/ma57/ma57s.f
endif

if COIN_HAS_DEPSF
  libcoinhsl_la_SOURCES += coinhsl/common/deps.f
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
if COIN_HAS_HSL_MA77S
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma77/hsl_ma77s.f90 coinhsl/hsl_ma77/C/hsl_ma77s_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma77/C/hsl_ma77s.h
endif

if COIN_HAS_HSL_MA86
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma86/hsl_ma86d.f90 coinhsl/hsl_ma86/C/hsl_ma86d_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma86/C/hsl_ma86d.h
endif
if COIN_HAS_HSL_MA86S
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma86/hsl_ma86s.f90 coinhsl/hsl_ma86/C/hsl_ma86s_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma86/C/hsl_ma86s.h
endif

if COIN_HAS_HSL_MA97
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma97/hsl_ma97d.f90 coinhsl/hsl_ma97/C/hsl_ma97d_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma97/C/hsl_ma97d.h
endif
if COIN_HAS_HSL_MA97S
  libcoinhsl_la_SOURCES += coinhsl/hsl_ma97/hsl_ma97s.f90 coinhsl/hsl_ma97/C/hsl_ma97s_ciface.f90
  includecoin_HEADERS += coinhsl/hsl_ma97/C/hsl_ma97s.h
endif

libcoinhsl_la_SOURCES += metis_adapter.c
if COIN_HAS_METIS
  # call coinmetis_nodend from metis_adapter.c instead of metis_nodend (coinhsl < 2024.05.15) or hsl_metis (coinhsl >= 2024.05.15) in common/deps90.f90
  AM_FCFLAGS = $(FC_DEFINE)metis_nodend=coinmetis_nodend $(FC_DEFINE)hsl_metis=coinmetis_nodend $(FCFLAGS_f90)
  # call COINMETIS_NODEND from metis_adapter.c instead of METIS_NODEND (coinhsl < 2024.05.15) or hsl_metis (coinhsl >= 2024.05.15) in ma57/ma57d.f
  AM_FFLAGS  = $(FC_DEFINE)METIS_NODEND=COINMETIS_NODEND $(FC_DEFINE)hsl_metis=COINMETIS_NODEND $(FCFLAGS_f)
endif
AM_CFLAGS = $(HSL_CFLAGS)

libcoinhsl_la_LIBADD = $(HSL_LFLAGS)

AM_LDFLAGS = $(LT_LDFLAGS)

# dependencies
#  need to define dependencies in terms of variables, since automake does not allow multiple rules for the same target
ma77d=coinhsl/hsl_ma77/hsl_ma77d
ma77dC=coinhsl/hsl_ma77/C/hsl_ma77d_ciface
ma77s=coinhsl/hsl_ma77/hsl_ma77s
ma77sC=coinhsl/hsl_ma77/C/hsl_ma77s_ciface
ma86d=coinhsl/hsl_ma86/hsl_ma86d
ma86dC=coinhsl/hsl_ma86/C/hsl_ma86d_ciface
ma86s=coinhsl/hsl_ma86/hsl_ma86s
ma86sC=coinhsl/hsl_ma86/C/hsl_ma86s_ciface
ma97d=coinhsl/hsl_ma97/hsl_ma97d
ma97dC=coinhsl/hsl_ma97/C/hsl_ma97d_ciface
ma97s=coinhsl/hsl_ma97/hsl_ma97s
ma97sC=coinhsl/hsl_ma97/C/hsl_ma97s_ciface
mc68=coinhsl/hsl_mc68/hsl_mc68i
mc68C=coinhsl/hsl_mc68/C/hsl_mc68i_ciface
$(ma77d).lo: coinhsl/common/deps90.lo
$(ma77s).lo: coinhsl/common/deps90.lo
$(ma86d).lo: coinhsl/common/deps90.lo
$(ma86s).lo: coinhsl/common/deps90.lo
$(ma97d).lo: coinhsl/common/deps90.lo
$(ma97s).lo: coinhsl/common/deps90.lo
$(ma77dC).lo: $(ma77d).lo
$(ma77sC).lo: $(ma77s).lo
$(ma86dC).lo: $(ma86d).lo
$(ma86sC).lo: $(ma86s).lo
$(ma97dC).lo: $(ma97d).lo
$(ma97sC).lo: $(ma97s).lo
$(mc68C).lo: coinhsl/common/deps90.lo

pkgconfiglibdir = $(libdir)/pkgconfig
pkgconfiglib_DATA = coinhsl.pc

test:
	@echo "No test available for HSL."

########################################################################
#                         Maintainer Stuff                             #
########################################################################

CLEANFILES = *.mod
