# Copyright (C) 2003, 2006 International Business Machines and others
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id: Makefile.am 735 2006-06-04 06:10:05Z andreasw $

AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = INSTALL.HSL

noinst_LTLIBRARIES = libcoinhsl.la

nodist_libcoinhsl_la_SOURCES =

if COIN_HAS_MA27
  nodist_libcoinhsl_la_SOURCES += ma27ad.f
endif

if COIN_HAS_MA57
  nodist_libcoinhsl_la_SOURCES += ma57ad.f
endif

if COIN_HAS_MC19
  nodist_libcoinhsl_la_SOURCES += mc19ad.f
endif

libcoinhsl_la_LDFLAGS = $(LT_LDFLAGS)

########################################################################
#                         Maintainer Stuff                             #
########################################################################

# Files that are generated and should be cleaned with make distclean
DISTCLEANFILES =

include ../../BuildTools/Makemain.inc
