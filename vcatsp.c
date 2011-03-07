/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: ,. on Sparse Arguments of rank 2 or less                         */

#include "j.h"


F2(jtstitchsp2){I ar,wr;
 RZ(a&&w);
 ar=AR(a); wr=AR(w);
 R irs2(a,w,0L,ar?ar-1:0,wr?wr-1:0,jtover);
}    /* sparse arrays with rank 2 or less */
