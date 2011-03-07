/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Conjunctions                                                            */

#include "j.h"


static CS1(obv1, CALL1(f1,  w,fs))
static CS2(obv2, CALL2(f2,a,w,fs))

F2(jtobverse){ASSERTVV(a,w); R CDERIV(COBVERSE,obv1,obv2,mr(a),lr(a),rr(a));}


static DF1(ad1){DECLFG;A z;I od=jt->db; 
 RZ(w); 
 jt->db=0; z=CALL1(f1,  w,fs); jt->db=od;
 if(EWTHROW==jt->jerr)R 0;
 RESETERR;  
 R z?z:CALL1(g1,  w,gs);
}

static DF2(ad2){DECLFG;A z;I od=jt->db;
 RZ(a&&w); 
 jt->db=0; z=CALL2(f2,a,w,fs); jt->db=od;
 if(EWTHROW==jt->jerr)R 0;
 RESETERR; 
 R z?z:CALL2(g2,a,w,gs);
}

F2(jtadverse){ASSERTVV(a,w); R CDERIV(CADVERSE,ad1,ad2,RMAX,RMAX,RMAX);}


static CS1(even1, halve(df1(w,folk(fs,ds(CPLUS ),atop(fs,gs)))))
static CS1(odd1,  halve(df1(w,folk(fs,ds(CMINUS),atop(fs,gs)))))

F2(jteven){ASSERTVV(a,w); R CDERIV(CEVEN,even1,0L, RMAX,0L,0L);}
F2(jtodd ){ASSERTVV(a,w); R CDERIV(CODD, odd1, 0L, RMAX,0L,0L);}
