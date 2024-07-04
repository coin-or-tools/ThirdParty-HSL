# Copyright (C) 2006, 2009 International Business Machines.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.
#
# Author:  Andreas Waechter            IBM    2006-04-13

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_INIT([CoinHSL],[2.2.5],[https://github.com/coin-or-tools/ThirdParty-HSL/issues/new],[],[https://github.com/coin-or-tools/ThirdParty-HSL])

AC_COPYRIGHT([
Copyright 2006, 2009 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package BuildTools which is distributed
under the Eclipse Public License.])

# List one file in the package so that the configure script can test
# whether the package is actually there
AC_CONFIG_SRCDIR([coinhsl.pc.in])

AC_COIN_INITIALIZE

#############################################################################
#                         Standard build tool stuff                         #
#############################################################################

# Get the name of the C compiler (for metis_adapter.c)
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

# check for single precision files
AC_DEFUN([MY_CHECK_HSLFILE_S],
[AC_MSG_CHECKING([for m4_toupper(m4_bpatsubst($1S, hsl_))])
if test -r "$srcdir/coinhsl/$1/$1s.f" ; then
  AC_DEFINE(m4_toupper(COINHSL_HAS_$1S), [1], Define to 1 if m4_toupper(m4_bpatsubst($1S, hsl_)) is available.)
  coin_has_$1s=yes
else
  coin_has_$1s=no
fi
AC_MSG_RESULT($coin_has_$1s)
AM_CONDITIONAL(m4_toupper(COIN_HAS_$1S),[test $coin_has_$1s = yes])
])

AC_DEFUN([MY_CHECK_HSLFILE_F90_S],
[if test -n "$FC" ; then
   AC_MSG_CHECKING([for m4_toupper(m4_bpatsubst($1S, hsl_))])
   if test -r "$srcdir/coinhsl/$1/$1s.f90" ; then
     AC_DEFINE([COINHSL_HAS_]m4_toupper(m4_bpatsubst($1S, hsl_)), [1], Define to 1 if m4_toupper(m4_bpatsubst($1S, hsl_)) is available.)
     coin_has_$1s=yes
   else
     coin_has_$1s=no
   fi
   AC_MSG_RESULT($coin_has_$1s)
else
  coin_has_$1s=no
fi
AM_CONDITIONAL(m4_toupper(COIN_HAS_$1S),[test $coin_has_$1s = yes])
])

MY_CHECK_HSLFILE(mc19)
MY_CHECK_HSLFILE(ma27)
MY_CHECK_HSLFILE(ma28)
MY_CHECK_HSLFILE(ma57)
MY_CHECK_HSLFILE_F90(hsl_ma77)
MY_CHECK_HSLFILE_F90(hsl_ma86)
MY_CHECK_HSLFILE_F90(hsl_ma97)

MY_CHECK_HSLFILE_S(mc19)
MY_CHECK_HSLFILE_S(ma27)
MY_CHECK_HSLFILE_S(ma28)
MY_CHECK_HSLFILE_S(ma57)
MY_CHECK_HSLFILE_F90_S(hsl_ma77)
MY_CHECK_HSLFILE_F90_S(hsl_ma86)
MY_CHECK_HSLFILE_F90_S(hsl_ma97)

coin_has_hsl_mc68=no
if test -n "$FC"; then
  AC_MSG_CHECKING([for C interface to MC68])
  if test -r "$srcdir/coinhsl/hsl_mc68/C/hsl_mc68i_ciface.f90" ; then
    AC_DEFINE(COINHSL_HAS_MC68, [1], Define to 1 if MC68 is available.)
    coin_has_hsl_mc68=yes
  fi
  AC_MSG_RESULT($coin_has_hsl_mc68)
fi
AM_CONDITIONAL(COIN_HAS_HSL_MC68,[test $coin_has_hsl_mc68 = yes])

# the F77 codes depend on deps.f
coin_has_depsf=no
if test $coin_has_ma28$coin_has_ma57$coin_has_mc19$coin_has_ma28s$coin_has_ma57s$coin_has_mc19s != nononononono ; then
  AC_MSG_CHECKING([for deps.f])
  if test -r "$srcdir/coinhsl/common/deps.f" ; then
    coin_has_depsf=yes
  fi
  AC_MSG_RESULT($coin_has_depsf)
  if test $coin_has_depsf = no; then
    AC_MSG_ERROR([Required file common/deps.f not found])
  fi
fi
AM_CONDITIONAL(COIN_HAS_DEPSF,[test $coin_has_depsf = yes])

# the F90 codes depend on deps90.f90
coin_has_depsf90=no
if test $coin_has_hsl_mc68$coin_has_hsl_ma77$coin_has_hsl_ma86$coin_has_hsl_ma97$coin_has_hsl_ma77s$coin_has_hsl_ma86s$coin_has_hsl_ma97s != nonononononono ; then
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

# MA27, MA57, MA77, and MA86 require BLAS, MA97 requires LAPACK
if test $coin_has_ma27$coin_has_ma57$coin_has_ma57s$coin_has_hsl_ma77$coin_has_hsl_ma77s$coin_has_hsl_ma86$coin_has_hsl_ma86s$coin_has_hsl_ma97$coin_has_hsl_ma97s != nonononononononono ; then
  AC_COIN_CHK_LAPACK(HSL)
  if test $coin_has_lapack != yes ; then
    AC_MSG_ERROR([Required package LAPACK not found.])
  fi
else
  AM_CONDITIONAL(COIN_HAS_LAPACK, [false])
fi

# MA57, MA77, MA97, and MC68 can use Metis
# the check intentionally uses int instead of idx_t (defined in metis.h), because HSL routines expect to use int, too (see #8)
# also we try to do another check to see whether IDXTYPEWIDTH is same as INT_WIDTH
if test $coin_has_ma57$coin_has_ma57s$coin_has_hsl_ma77$coin_has_hsl_ma77s$coin_has_hsl_ma97$coin_has_hsl_ma97s$coin_has_hsl_mc68 != nonononononono ; then
  AC_COIN_CHK_LIBM(METISCHECK)
  AC_LANG_PUSH(C)
  AC_COIN_CHK_LIBHDR(Metis,[HSL],[-lmetis "$METISCHECK_LFLAGS"],[],[],
    [#if METIS_VER_MAJOR < 5
     metis_nodend((int*)0, (int*)0, (int*)0, (int*)0, (int*)0, (int*)0, (int*)0);
     #else
     METIS_NodeND((int*)0, (int*)0, (int*)0, (int*)0, (int*)0, (int*)0, (int*)0);
     #endif
    ],
    [#define __STDC_WANT_IEC_60559_BFP_EXT__
     #ifdef __STDC__
      #include <limits.h>
     #endif
     #include "metis.h"
     #ifndef METIS_VER_MAJOR
      #define METIS_VER_MAJOR 4
      #ifdef IDXTYPE_INT
       #define IDXTYPEWIDTH 32
      #else
       #define IDXTYPEWIDTH 64
      #endif
     #endif
     #if defined(INT_WIDTH) && INT_WIDTH != IDXTYPEWIDTH
      #error "Metis does not use int for idx_t. This isn't supported by HSL, afaik."
     #endif
    ])
  AC_LANG_POP(C)
else
  coin_has_metis=no
fi

# check that Metis flags also work with Fortran compiler
if test "$coin_has_metis" = yes ; then
  AC_MSG_CHECKING([whether Metis library is linkable with Fortran compiler])
  AC_LANG_PUSH(Fortran)
  orig_LIBS="$LIBS"
  LIBS="$LIBS $metis_lflags"
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[])],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])
     if test "$metis_userflags" = yes ; then
       AC_MSG_ERROR([Metis linker flags $metis_lflags worked with C compiler, but failed with Fortran compiler. Check config.log for details.])
     else
       AC_MSG_WARN([Metis linker flags $metis_lflags worked with C compiler, but failed with Fortran compiler. Check config.log for details. Disabling Metis.])
       coin_has_metis=no
     fi])
  LIBS="$orig_LIBS"
  AC_LANG_POP(Fortran)
fi

# check whether we can redefine metis_nodend to cmets_nodend from metis_adapter
if test $coin_has_metis = yes ; then
  AC_FC_PP_DEFINE([],[coin_has_metis=no])
fi
if test $coin_has_metis = yes ; then
  AC_FC_PP_SRCEXT(f,[],[coin_has_metis=no])
fi
if test $coin_has_metis = yes ; then
  AC_FC_PP_SRCEXT(f90,[],[coin_has_metis=no])
fi
AM_CONDITIONAL(COIN_HAS_METIS, [test $coin_has_metis = yes])

# MA86 and MA97 can use OpenMP
if test $coin_has_hsl_ma86$coin_has_hsl_ma86s$coin_has_hsl_ma97$coin_has_hsl_ma97s != nononono ; then
  # on macOS, turn off OpenMP by default if the C compiler does not seem to support OpenMP
  # the reason is that if for the Fortran compiler (likely gfortran), -fopenmp is recognized, then this
  # makes it into the linker flags of libraries that link against libcoinhsl (through inherited_linker_flags in libcoinhsl.la)
  # but Apple's variant of clang does not understand -fopenmp, which then gives a linker error
  # (it understands -Xpreprocessor -fopenmp, and we rely here on AC_OPENMP not testing this)
  if test -z "$enable_openmp" ; then
    case "$build_os" in darwin*)
      AC_LANG_PUSH(C)
      AC_OPENMP
      AC_LANG_POP(C)
      if test "$ac_cv_prog_c_openmp" = "unsupported" ; then
        enable_openmp=no
        AC_MSG_NOTICE([Turning off check for OpenMP support of $FC. You can force it with --enable-openmp, but may need to patch up installed libcoinhsl.la (remove -fopenmp ?) before linking it with $CC.])
      fi
      ;;
    esac
  fi

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

AC_CONFIG_HEADERS([config.h CoinHslConfig.h])

AC_COIN_FINALIZE_FLAGS([HSL])
AC_COIN_FINALIZE
