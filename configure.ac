# Copyright (C) 2006, 2009 International Business Machines.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

# Author:  Andreas Waechter            IBM    2006-04-13

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_PREREQ(2.59)

AC_INIT([ThirdPartyHSL],[trunk],[https://github.com/coin-or-tools/ThirdParty-HSL/issues/new],,[https://github.com/coin-or-tools/ThirdParty-HSL])

AC_COPYRIGHT([
Copyright 2006, 2009 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package BuildTools which is distributed
under the Eclipse Public License.])

# List one file in the package so that the configure script can test
# whether the package is actually there
AC_CONFIG_SRCDIR([coinhsl/common/deps.f])

AC_COIN_INITIALIZE(COINHSL)

#############################################################################
#                         Standard build tool stuff                         #
#############################################################################

# Get the name of the C compiler (for metis_dummy.c)
AC_COIN_PROG_CC

# Get the name of the Fortran 77 compiler and appropriate compiler options
AC_COIN_PROG_F77
if test -z "$F77" ; then
  AC_MSG_ERROR([No Fortran compiler.])
fi
AC_COIN_F77_SETUP

# Get the name of the Fortran 90 compiler and appropriate compiler options
AC_COIN_PROG_FC

# Initialize libtool
AC_COIN_PROG_LIBTOOL(no-win32-dll)

# Add FLIBS to HSL_LFLAGS, so that they get into the .pc files section for static builds
HSL_LFLAGS="$HSL_LFLAGS $FLIBS"

#############################################################################
#                    Find out which files are available                     #
#############################################################################

# do this unconditionally to make sure COIN_HAS_PKGCONFIG is also defined if no >= MA57
AC_COIN_HAS_PKGCONFIG

AC_DEFUN([MY_CHECK_HSLFILE],
[AC_MSG_CHECKING([for m4_toupper(m4_bpatsubst($1, hsl_))])
if test -r "$srcdir/coinhsl/$1/$1d.f" ; then
  AC_DEFINE(m4_toupper(COINHSL_HAS_$1), [1], Define to 1 if m4_toupper(m4_bpatsubst($1, hsl_)) is available.)
  coin_has_$1=yes
else
  coin_has_$1=no
fi
AC_MSG_RESULT($coin_has_$1)
AM_CONDITIONAL(m4_toupper(COIN_HAS_$1),[test $coin_has_$1 = yes])
])

AC_DEFUN([MY_CHECK_HSLFILE_F90],
[if test -n "$FC" ; then
   AC_MSG_CHECKING([for m4_toupper(m4_bpatsubst($1, hsl_))])
   if test -r "$srcdir/coinhsl/$1/$1d.f90" ; then
     AC_DEFINE([COINHSL_HAS_]m4_toupper(m4_bpatsubst($1, hsl_)), [1], Define to 1 if m4_toupper(m4_bpatsubst($1, hsl_)) is available.)
     coin_has_$1=yes
   else
     coin_has_$1=no
   fi
   AC_MSG_RESULT($coin_has_$1)
else
  coin_has_$1=no
fi
AM_CONDITIONAL(m4_toupper(COIN_HAS_$1),[test $coin_has_$1 = yes])
])

MY_CHECK_HSLFILE(mc19)
MY_CHECK_HSLFILE(ma27)
MY_CHECK_HSLFILE(ma28)
MY_CHECK_HSLFILE(ma57)
MY_CHECK_HSLFILE_F90(hsl_ma77)
MY_CHECK_HSLFILE_F90(hsl_ma86)
MY_CHECK_HSLFILE_F90(hsl_ma97)

coin_has_hsl_mc68=no
if test -n "$F90"; then
  AC_MSG_CHECKING([for C interface to MC68])
  if test -r "$srcdir/coinhsl/hsl_mc68/C/hsl_mc68i_ciface.f90" ; then
    AC_DEFINE(COINHSL_HAS_MC68, [1], Define to 1 if MC68 is available.)
    coin_has_hsl_mc68=yes
  fi
  AC_MSG_RESULT($coin_has_hsl_mc68)
fi
AM_CONDITIONAL(COIN_HAS_HSL_MC68,[test $coin_has_hsl_mc68 = yes])

# the F90 codes depend on deps90.f90
coin_has_depsf90=no
if test $coin_has_hsl_mc68$coin_has_hsl_ma77$coin_has_hsl_ma86$coin_has_hsl_ma97 != nononono ; then
  AC_MSG_CHECKING([for deps90.f90])
  if test -r "$srcdir/coinhsl/common/deps90.f90" ; then
    coin_has_depsf90=yes
  fi
  AC_MSG_RESULT($coin_has_depsf90)
  if test $coin_has_depsf90 = no; then
    AC_MSG_ERROR([Required file common/deps90.f90 not found])
  fi
fi
AM_CONDITIONAL(COIN_HAS_DEPSF90,[test $coin_has_depsf90 = yes])

# MA57, MA77, and MA86 require BLAS, MA97 requires LAPACK
if test $coin_has_ma57$coin_has_hsl_ma77$coin_has_hsl_ma86$coin_has_hsl_ma97 != nononono ; then
  AC_COIN_CHK_LAPACK(HSL)
  if test $coin_has_lapack != yes ; then
    AC_MSG_ERROR([Required package LAPACK not found.])
  fi
else
  AM_CONDITIONAL(COIN_HAS_LAPACK, [false])
fi

# MA57, MA77, MA97, and MC68 can use Metis
# if Metis is not available, then we compile a dummy metis.f that defines the Metis function symbol
if test $coin_has_ma57$coin_has_hsl_ma77$coin_has_hsl_ma97$coin_has_hsl_mc68 != nononono ; then
  AC_COIN_CHK_PKG(Metis,[HSL],[coinmetis],[build])
  if test $coin_has_metis = yes ; then
    AC_DEFINE(COINHSL_HAS_METIS, [1], Define to 1 if METIS is available)
  fi
else
  # do as if we had metis, so metis.f is not compiled
  AM_CONDITIONAL(COIN_HAS_METIS, [true])
fi

# MA86 and MA97 can use OpenMP
if test $coin_has_hsl_ma86$coin_has_hsl_ma97 != nono ; then
  AC_LANG_PUSH(Fortran)
  AC_OPENMP
  FCFLAGS="$FCFLAGS $OPENMP_FCFLAGS"
  HSL_LFLAGS="$HSL_LFLAGS $OPENMP_FCFLAGS"
  AC_LANG_POP(Fortran)
fi

#############################################################################
#                              Write the output                             #
#############################################################################

AC_CONFIG_FILES([Makefile coinhsl.pc])

AC_CONFIG_HEADER(config.h CoinHslConfig.h)

AC_COIN_FINALIZE_FLAGS([HSL])
AC_COIN_FINALIZE
