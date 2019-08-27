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

# Get the name of the Fortran 77 compiler and appropriate compiler options
AC_COIN_PROG_F77
if test -z "$F77" ; then
  AC_MSG_ERROR([No Fortran compiler.])
fi
AC_COIN_F77_SETUP

# Get the name of the Fortran 90 compiler and appropriate compiler options
AC_COIN_PROG_FC

# Get the name of the C compiler (for metis_dummy.c)
AC_COIN_PROG_CC

# Initialize libtool
AC_COIN_PROG_LIBTOOL

# Add FLIBS to HSL_LFLAGS, so that they get into the .pc files section for static builds
HSL_LFLAGS="$HSL_LFLAGS $FLIBS"

# recent autotools versions can recognize OpenMP with the following macro
# this would be useful when using MA86 and MA97 
# AC_OPENMP

#############################################################################
#                    Find out which files are available                     #
#############################################################################

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

# TODO remove (need to adapt Ipopt)
AC_DEFINE(COINHSL_HSL2013, [1], Define to 1 if HSL library is from 2013)

#############################################################################
#                        Setup build of loadable library                    #
#############################################################################

if test "$enable_shared" = yes; then
  case $build in
    *-cygwin* | *-mingw* | *-msys*)
      case $F77 in
        compile_f2c*)
          EXPORT_SYMBOLS=
          if test $coin_has_ma27 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS ma27ad_ ma27bd_ ma27cd_ ma27id_"
          fi
          if test $coin_has_ma28 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS ma28ad_"
          fi
          if test $coin_has_ma57 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS ma57ad_ ma57bd_ ma57cd_ ma57ed_ ma57id_"
          fi
          if test $coin_has_mc19 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS mc19ad_"
          fi
          if test $coin_has_hsl_ma77 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS ma77_default_control_ ma77_open_nelt_ ma77_open_ ma77_input_vars_ ma77_input_reals_ ma77_analyse_ ma77_factor_ ma77_factor_solve_ ma77_solve_ ma77_resid_ ma77_scale_ ma77_enquire_posdef_ ma77_enquire_indef_ ma77_alter_ ma77_restart_ ma77_finalise_"            
          fi
          if test $coin_has_hsl_ma86 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS ma86_default_control_ ma86_analyse_ ma86_factor_ ma86_factor_solve_ ma86_solve_ ma86_finalise_"
          fi
          if test $coin_has_hsl_ma97 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS ma97_default_control_ ma97_analyse_ ma97_factor_ ma97_factor_solve_ ma97_solve_ ma97_finalise_ ma97_free_akeep_"
          fi
          if test $coin_has_hsl_mc68 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS mc68_default_control_ mc68_order_"
          fi
          DEFFILE='Export.def'
          ;;
        ifort* | IFORT*)
          EXPORT_SYMBOLS=
          if test $coin_has_ma27 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MA27AD MA27BD MA27CD MA27ID"
          fi
          if test $coin_has_ma28 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MA28AD"
          fi
          if test $coin_has_ma57 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MA57AD MA57BD MA57CD MA57ED MA57ID"
          fi
          if test $coin_has_hsl_ma77 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MA77_DEFAULT_CONTROL MA77_OPEN_NELT MA77_OPEN MA77_INPUT_VARS MA77_INPUT_REALS MA77_ANALYSE MA77_FACTOR MA77_FACTOR_SOLVE MA77_SOLVE MA77_RESID MA77_SCALE MA77_ENQUIRE_POSDEF MA77_ENQUIRE_INDEF MA77_ALTER MA77_RESTART MA77_FINALISE"            
          fi
          if test $coin_has_mc19 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MC19AD"
          fi
          if test $coin_has_hsl_ma86 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MA86_DEFAULT_CONTROL MA86_ANALAYSE MA86_FACTOR MA86_FACTOR_SOLVE MA86_SOLVE MA86_FINALISE"
          fi
          if test $coin_has_hsl_ma97 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MA97_DEFAULT_CONTROL MA97_ANALAYSE MA97_FACTOR MA97_FACTOR_SOLVE MA97_SOLVE MA97_FINALISE MA97_FREE_AKEEP"
          fi
          if test $coin_has_hsl_mc68 = yes; then
            EXPORT_SYMBOLS="$EXPORT_SYMBOLS MC68_DEFAULT_CONTROL MC68_ORDER"
          fi
          DEFFILE='Export.def'
          ;;
      esac
      ;;
  esac
fi

#############################################################################
#                              Write the output                             #
#############################################################################

AC_CONFIG_FILES([Makefile coinhsl.pc])

AC_CONFIG_HEADER(config.h CoinHslConfig.h)

AC_COIN_FINALIZE_FLAGS([HSL])
AC_COIN_FINALIZE
