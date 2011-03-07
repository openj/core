/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: Character Functions  u&(a.&i.) and u&.(a.&i.)                    */

#include "j.h"


static APFX(maxC, UC,UC,UC, MAX)
static APFX(minC, UC,UC,UC, MIN)

static AIFX(ltC,  B, UC,UC, <  )
static AIFX(leC,  B, UC,UC, <= )
static AIFX(geC,  B, UC,UC, >= )
static AIFX(gtC,  B, UC,UC, >  )

#define PLUSX +

DF2(jtcharfn2){A z;B b;C c;I an,ar,*as,m,n,wn,wr,*ws,zn,zt;V*v;VF ado=0;
 RZ(a&&w);
 v=VAV(self); c=ID(v->f);
 if(CUNDER==v->id)switch(c){
  case CMAX:  zt=LIT; ado=maxC; break;
  case CMIN:  zt=LIT; ado=minC; break;
  case CAT:   z=VAV(v->f)->f; v=VAV(z); if(CAMP==v->id&&256==i0(v->f)&&CSTILE==ID(v->g));
 }else switch(c){
  case CEQ:   R eq(a,w);
  case CNE:   R ne(a,w);
  case CLT:   zt=B01; ado=ltC;  break;
  case CLE:   zt=B01; ado=leC;  break;
  case CGE:   zt=B01; ado=geC;  break;
  case CGT:   zt=B01; ado=gtC;  break;
 }
 if(!ado)R df2(a,w,self);
 an=AN(a); ar=AR(a); as=AS(a);
 wn=AN(w); wr=AR(w); ws=AS(w);
 ASSERT(!ICMP(as,ws,MIN(ar,wr)),EVLENGTH);
 b=ar<=wr; zn=b?wn:an; m=b?an:wn; n=m?zn/m:0;
 GA(z,zt,zn,b?wr:ar,b?ws:as); if(!zn)R z;
 ado(jt,b,m,n,CAV(z),CAV(a),CAV(w));
 R z;
}
