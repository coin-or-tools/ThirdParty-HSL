# ThirdParty-HSL

This is an autotools-based build system to build and install routines from
the [Harwell Subroutine Library](http://www.hsl.rl.ac.uk/) (HSL).
This installation of HSL routines is used by some other COIN-OR projects,
in particular [Ipopt](https://github.com/coin-or/Ipopt).

For use by COIN-OR, STFC provides special packages at

https://licences.stfc.ac.uk/product/coin-hsl

which can be build independently or within the buildsystem in this
directory.

Version 2021.05.05 of the Coin-HSL packages include single-precision
versions of HSL routines. These are also compiled if found.

Alternatively, STFC provides a package that includes only the routines
MA27, MA28, and MC19, but has more liberal license terms, at

https://licences.stfc.ac.uk/product/coin-hsl-archive

This Coin-HSL Archive package can also be used with ThirdParty-HSL.

Prebuild libraries with many HSL routines, including these from coin-hsl,
are available at https://licences.stfc.ac.uk/products/Software/HSL/LibHSL.

## Dependencies

- HSL routines require a Fortran compiler.
  Some of them are written in Fortran 77, others in Fortran 90.
  
- MA57, HSL_MA77, and HSL_MA86 require BLAS, HSL_MA97 requires LAPACK.
  `configure` will look for a LAPACK installation (and assume that it
  includes BLAS), but if that does not succeed, the flags to link with LAPACK
  should be specified with the `--with-lapack-lflags` argument of `configure`.

- MA57, HSL_MA77, HSL_MA97, and MC68 can use METIS. `configure` will look
  for a METIS library and header, but if that does not succeed, the
  arguments `--with-metis-lflags` and `--with-metis-cflags` can be
  specified for `configure`.

  Both Metis 4 and Metis 5 can be used with ThirdParty-HSL.

To install BLAS, LAPACK, and METIS on a standard Debian-based Linux distribution, e.g., Ubuntu:
```
apt install libblas-dev liblapack-dev libmetis-dev
```

## Installation steps

1. Obtain a tarball with Coin-HSL source code from https://licences.stfc.ac.uk/product/coin-hsl.

   **********************************************************************
   Note: It is YOUR RESPONSIBILITY to ensure that you are entitled to
         download and use this third party package.
   **********************************************************************

2. Inside the ThirdParty-HSL directory, unpack this tarball via

       gunzip coinhsl-x.y.z.tar.gz
       tar xf coinhsl-x.y.z.tar

3. Rename the directory `coinhsl-x.y.z` to `coinhsl`, or set a symbolic link:

       ln -s coinhsl-x.y.z coinhsl

4. Run `./configure`. Use `./configure --help` to see available options.

   The `configure` script will detect which source files are available
   in your `coinhsl` package and prepare the `Makefile` accordingly.

5. Run `make` to build the HSL library (namestem `coinhsl`).

6. Run `make install` to install the HSL library and header files.

For Coin-HSL Archive, follow the above steps, but download from
https://licences.stfc.ac.uk/product/coin-hsl-archive and adjust the tarball
names accordingly. Make sure that the directory with the source files is
still called `coinhsl`.

## Use of generated library for runtime-loading by Ipopt

If you intend for Ipopt to load the generated HSL library at __runtime__,
then be aware that Ipopt looks for a library with a name different than the
one build here: https://coin-or.github.io/Ipopt/OPTIONS.html#OPT_hsllib

You should thus either set option `hsllib` of Ipopt to the full path of
the library build here (e.g., `$libdir/libcoinhsl.so`, `$libdir/libcoinhsl.dylib`,
`$bindir/coinhsl-2.dll`), or rename the `coinhsl` library appropriately.

Do not do this if you intend to build Ipopt such that it links to the
`coinhsl` library.
