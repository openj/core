/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Memory Management                                                       */

/* ANSI C already has malloc by j.h include of stdlib.h                    */
#if (SYS & SYS_PCWIN+SYS_PC386+SYS_UNIX) && !(SYS+SYS_ANSI)
#include <malloc.h>
#endif

#if SY_WIN32 && !SY_WINCE
#define FREE(a)     HeapFree(jt->heap,0,a)
#define MALLOC(n)   (void*)HeapAlloc(jt->heap,0,n)
#else
#define FREE(a) free(a)
#define MALLOC(n) malloc(n)
#endif

typedef struct {I*a;S j;C mflag,unused;} MS;

/* layout of the two words before every A array                            */
/* a: ptr to next block (when in free list)                                */
/*    address of SMM array, or 0 (when allocated)                          */
/* j: mfree/msize index                                                    */
/* mflag: bit flags                                                        */

#define MFHEAD  1      /* head of 64k block (returned by malloc() */


extern I mhb;
extern I mhw;
