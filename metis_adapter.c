/* Copyright (C) 2020 COIN-OR
 * All Rights Reserved.
 * This file is distributed under the Eclipse Public License.
 */

#include "CoinHslConfig.h"

#ifndef COINHSL_HAS_METIS

/* provide dummy implementations of the method metis_nodend as expected by the HSL codes if Metis is not available
 * as in Metis, we implement the method in several naming variants to copy with C and fortran naming style conventions
 * Not defining COINMETIS_NODEND, as the renaming metis -> coinmetis only happens if Metis is available
 */
typedef int idxtype;

void METIS_NODEND(int * a, idxtype * b, idxtype * c, int * d, int * e, idxtype * f, idxtype * perm)
{
  perm[0] = -1;
}

void metis_nodend(int * a, idxtype * b, idxtype * c, int * d, int * e, idxtype * f, idxtype * perm)
{
  perm[0] = -1;
}

void metis_nodend_(int * a, idxtype * b, idxtype * c, int * d, int * e, idxtype * f, idxtype * perm)
{
  perm[0] = -1;
}

void metis_nodend__(int * a, idxtype * b, idxtype * c, int * d, int * e, idxtype * f, idxtype * perm)
{
  perm[0] = -1;
}

void METIS_NodeND(int * a, idxtype * b, idxtype * c, int * d, int * e, idxtype * f, idxtype * perm)
{
  perm[0] = -1;
}

#else /* COINHSL_HAS_METIS */

#include "metis.h"

#ifndef METIS_VER_MAJOR
#define METIS_VER_MAJOR 4
#endif

/* if metis.h defines IDXTYPEWIDTH to 64, then this version of Metis cannot be used with HSL */
#ifdef IDXTYPEWIDTH
#if IDXTYPEWIDTH != 32
#error "Metis must have been build for 32-bit integers. Expected IDXTYPEWIDTH == 32 in metis.h."
#endif
#endif

/* wrapper to map COINMETIS_NODEND to METIS_NODEND from Metis 4 or 5 */
typedef int idxtype;

extern void COINMETIS_NODEND(int *, idxtype *, idxtype *, int *, int *, idxtype *, idxtype *);
extern void coinmetis_nodend(int *, idxtype *, idxtype *, int *, int *, idxtype *, idxtype *);
extern void coinmetis_nodend_(int *, idxtype *, idxtype *, int *, int *, idxtype *, idxtype *);
extern void coinmetis_nodend__(int *, idxtype *, idxtype *, int *, int *, idxtype *, idxtype *);

#if METIS_VER_MAJOR < 5

void COINMETIS_NODEND(
   int*   nvtxs,
   idxtype* xadj,
   idxtype* adjncy,
   int*   numflag,
   int*   options,
   idxtype* perm,
   idxtype* iperm)
{
   METIS_NODEND(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

void coinmetis_nodend(
   int*   nvtxs,
   idxtype* xadj,
   idxtype* adjncy,
   int*   numflag,
   int*   options,
   idxtype* perm,
   idxtype* iperm)
{
   metis_nodend(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

void coinmetis_nodend_(
   int*   nvtxs,
   idxtype* xadj,
   idxtype* adjncy,
   int*   numflag,
   int*   options,
   idxtype* perm,
   idxtype* iperm)
{
   metis_nodend_(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

void coinmetis_nodend__(
   int*   nvtxs,
   idxtype* xadj,
   idxtype* adjncy,
   int*   numflag,
   int*   options,
   idxtype* perm,
   idxtype* iperm)
{
   metis_nodend__(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

#else /* METIS_VER_MAJOR >= 5 */

#if 0
#include <stdio.h>
#endif

static
void COINMETIS_NodeND(
   int*   nvtxs,
   idx_t* xadj,
   idx_t* adjncy,
   int*   numflag,
   int*   options,
   idx_t* perm,
   idx_t* iperm)
{
   idx_t options5[METIS_NOPTIONS];

#if 0
   {
      int i;
      printf("METIS_NodeND called with nvtxs = %d numflag=%d\n", *nvtxs, *numflag);

      printf("xadj:");
      for( i = 0; i < *nvtxs; ++i )
         printf(" %d", xadj[i]);
      printf("\nadjncy:");
      for( i = 0; i < xadj[*nvtxs] - *numflag; ++i )
         printf(" %d", adjncy[i]);
      printf("\n");

      printf("options:");
      if( options[0] == 0 )
         printf(" default\n");
      else
      {
         for( i = 0; i < 8; ++i )
            printf(" %d", options[i]);
         printf("\n");
      }
   }
#endif

   if( *nvtxs == 1 )
   {
      /* MA57 seems to call metis with a graph containing 1 vertex and a self-loop
       * Metis5 prints an error for this
       */
      perm[0] = *numflag;
      iperm[0] = *numflag;
      return;
   }

   METIS_SetDefaultOptions(options5);
   options5[METIS_OPTION_NUMBERING] = *numflag;

   if( options[0] != 0 )
   {
      if( options[1] == 1 ) /* random matching */
         options5[METIS_OPTION_CTYPE] = METIS_CTYPE_RM;
      else /* heavy-edge or sorted heavy-edge matching; map both to shem, as heave-edge matching not available in metis5 */
         options5[METIS_OPTION_CTYPE] = METIS_CTYPE_SHEM;

      if( options[2] == 1 ) /* edge-based region-growing */
         options5[METIS_OPTION_IPTYPE] = METIS_IPTYPE_EDGE;
      else /* node-based region-growing */
         options5[METIS_OPTION_IPTYPE] = METIS_IPTYPE_NODE;

      if( options[3] == 1 ) /* two-sided node FM refinement */
         options5[METIS_OPTION_RTYPE] = METIS_RTYPE_SEP2SIDED;
      else  /* one-sided node FM refinement */
         options5[METIS_OPTION_RTYPE] = METIS_RTYPE_SEP1SIDED;

      options5[METIS_OPTION_DBGLVL] = options[4];

      switch( options[5] )
      {
         case 0:  /* do not try to compress or order connected components */
            options5[METIS_OPTION_COMPRESS] = 0;
            options5[METIS_OPTION_CCORDER] = 0;
            break;
         case 1:  /* try to compress graph */
            options5[METIS_OPTION_COMPRESS] = 1;
            options5[METIS_OPTION_CCORDER] = 0;
            break;
         case 2:  /* order each component separately */
            options5[METIS_OPTION_COMPRESS] = 0;
            options5[METIS_OPTION_CCORDER] = 1;
            break;
         case 3:  /* try to compress and order components */
            options5[METIS_OPTION_COMPRESS] = 1;
            options5[METIS_OPTION_CCORDER] = 1;
            break;
      }

      options5[METIS_OPTION_PFACTOR] = options[6];

      options5[METIS_OPTION_NSEPS] = options[7];
   }

   METIS_NodeND(nvtxs, xadj, adjncy, (void*)0, options5, perm, iperm);

#if 0
   {
      int i;
      printf("perm:");
      for( i = 0; i < *nvtxs; ++i )
         printf(" %d", perm[i]);
      printf("\niperm");
      for( i = 0; i < *nvtxs; ++i )
         printf(" %d", iperm[i]);
      printf("\n");
   }
#endif
}

void COINMETIS_NODEND(
   int*   nvtxs,
   idx_t* xadj,
   idx_t* adjncy,
   int*   numflag,
   int*   options,
   idx_t* perm,
   idx_t* iperm)
{
   COINMETIS_NodeND(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

void coinmetis_nodend(
   int*   nvtxs,
   idx_t* xadj,
   idx_t* adjncy,
   int*   numflag,
   int*   options,
   idx_t* perm,
   idx_t* iperm)
{
   COINMETIS_NodeND(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

void coinmetis_nodend_(
   int*   nvtxs,
   idx_t* xadj,
   idx_t* adjncy,
   int*   numflag,
   int*   options,
   idx_t* perm,
   idx_t* iperm)
{
   COINMETIS_NodeND(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

void coinmetis_nodend__(
   int*   nvtxs,
   idx_t* xadj,
   idx_t* adjncy,
   int*   numflag,
   int*   options,
   idx_t* perm,
   idx_t* iperm)
{
   COINMETIS_NodeND(nvtxs, xadj, adjncy, numflag, options, perm, iperm);
}

#endif /* METIS_VER_MAJOR */ 

#endif /* COINHSL_HAS_METIS */
