# Copyright (C) 2006 International Business Machines.
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id$

# Author:  Andreas Waechter            IBM    2006-04-13

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_PREREQ(2.59)

AC_INIT([ThirdPartyHSL],[0.0],
        [http://projects.coin-or.org/BuildTools/newticket])

AC_COPYRIGHT([
Copyright 2006 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package Coin which is distributed
under the Common Public License.])

# List one file in the package so that the configure script can test
# whether the package is actually there
# Here we don't know yet which files are actually provided...
AC_CONFIG_SRCDIR(configure.ac)

# Where should everything be installed by default?  Here, we want it
# to be installed directly in 'bin', 'lib', 'include' subdirectories
# of the directory where configure is run.  The default would be
# /usr/local.
AC_PREFIX_DEFAULT([`pwd`])

AC_COIN_PROJECTDIR_INIT

#############################################################################
#                         Standard build tool stuff                         #
#############################################################################

# Get the system type
AC_CANONICAL_BUILD

# Check if user wants to produce debugging code
AC_COIN_DEBUG_COMPILE(HSL)

# Get the name of the Fortran compiler and appropriate compiler options
AC_COIN_PROG_F77

# Need egrep later on
AC_PROG_EGREP

# Initialize autotools
AC_COIN_INIT_AUTO_TOOLS

#############################################################################
#                    Find out which files are available                     #
#############################################################################

AC_DEFUN([MY_CHECK_HSLFILE],
         [AC_CHECK_FILE([$srcdir/$1.f],
                        [hsl_files="$hsl_files $1.f"
                         coin_has_$1=yes],
                        [coin_has_$1=no])
          AM_CONDITIONAL([COIN_HAS_$2],[test $coin_has_$1 = yes])])

MY_CHECK_HSLFILE(ma27ad,MA27)
if test coin_has_ma27ad = yes; then
  AC_MSG_CHECKING([whether MA27 is threadsafe])
  if $EGREP MA27UD $srcdir/ma27ad.f >/dev/null 2>&1; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([Please obtain the threadsafe (newer) version of MA27])
  fi
fi
MY_CHECK_HSLFILE(mc19ad,MC19)
MY_CHECK_HSLFILE(ma57ad,MA57)
MY_CHECK_HSLFILE(ma28ad,MA28)

#############################################################################
#                              Write the output                             #
#############################################################################

AC_CONFIG_FILES([Makefile])

AC_COIN_FINALIZE
