/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Xenos: Custom                                                           */

#include "j.h"


F2(jtforeignextra){
 RZ(a&&w);
 R CDERIV(CIBEAM, 0,0, RMAX,RMAX,RMAX);
}

F2(jtfixrecursive){A f,g,y;
 RZ(a&&w);
 RZ(y=lrep(w)); 
 if(a==one   ||a==num[3])RZ(f=colon(num[3],                over(y,cstr(" y")) ));
 if(a==num[2]||a==num[3])RZ(g=colon(num[4],over(cstr("x "),over(y,cstr(" y")))));
 R a==num[3]?colon(f,g):a==one?f:g;
}
