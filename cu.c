/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Conjunctions: Under and Each                                            */

#include "j.h"
#include "ve.h"


static A jteverysp(J jt,A w,A fs,AF f1){A*wv,x,z,*zv;P*wp,*zp;
 RZ(w);
 ASSERT(SBOX&AT(w),EVNONCE);
 RZ(z=ca(w));
 wp=PAV(w); x=SPA(wp,x); wv=AAV(x);
 zp=PAV(z); x=SPA(zp,x); zv=AAV(x);
 DO(AN(x), RZ(*zv++=CALL1(f1,*wv++,fs)););
 R z;
}

#define EVERYI(exp)  {RZ(*zv++=x=exp); ASSERT(!(SPARSE&AT(x)),EVNONCE);}
     /* note: x can be non-noun */

A jtevery(J jt,A w,A fs,AF f1){A*wv,x,z,*zv;I wd;
 RZ(w);
 if(SPARSE&AT(w))R everysp(w,fs,f1);
 if(!(BOX&AT(w)))RZ(w=box0(w));
 GA(z,BOX,AN(w),AR(w),AS(w));
 zv=AAV(z); wv=AAV(w); wd=(I)w*ARELATIVE(w);
 DO(AN(w), EVERYI(CALL1(f1,WVR(i),fs)););
 R z;
}

A jtevery2(J jt,A a,A w,A fs,AF f2){A*av,*wv,x,z,*zv;B ab,b,wb;I ad,an,ar,*as,wd,wn,wr,*ws;
 RZ(a&&w); 
 an=AN(a); ar=AR(a); as=AS(a); ab=BOX==AT(a); ad=(I)a*ARELATIVE(a);
 wn=AN(w); wr=AR(w); ws=AS(w); wb=BOX==AT(w); wd=(I)w*ARELATIVE(w);
 b=!ar||!wr||ar==wr; if(b&&ar&&wr)DO(ar, b&=as[i]==ws[i];);
 if(!b)R df2(a,w,atop(ds(CBOX),amp(fs,ds(COPE))));
 GA(z,BOX,ar?an:wn,ar?ar:wr,ar?as:ws);  zv=AAV(z);
 if(ar&&!ab)RZ(a=box0(a)); av=AAV(a);
 if(wr&&!wb)RZ(w=box0(w)); wv=AAV(w);
 if(ar&&wr)                   DO(an, EVERYI(CALL2(f2,AVR(i),      WVR(i),      fs))) 
 else if(wr){if(ab)a=AAV0(a); DO(wn, EVERYI(CALL2(f2,a,           WVR(i),      fs)));}
 else if(ar){if(wb)w=AAV0(w); DO(an, EVERYI(CALL2(f2,AVR(i),      w,           fs)));}
 else                                EVERYI(CALL2(f2,ab?AAV0(a):a,wb?AAV0(w):w,fs)) ;
 R z;
}

static DF1(jteach1){DECLF; R every (  w,fs,f1);}
static DF2(jteach2){DECLF; R every2(a,w,fs,f2);}

DF2(jteachl){RZ(a&&w&&self); R rank2ex(a,w,self,-1L, RMAX,VAV(self)->f2);}
DF2(jteachr){RZ(a&&w&&self); R rank2ex(a,w,self,RMAX,-1L, VAV(self)->f2);}

static DF1(jtunder1){DECLFG; R df1(  w,atop(inv(gs),amp(fs,gs)));}
static DF2(jtunder2){DECLFG; R df2(a,w,atop(inv(gs),amp(fs,gs)));}

static DF1(jtundco1){DECLFG; R df1(  w,atop(inv(gs),ampco(fs,gs)));}
static DF2(jtundco2){DECLFG; R df2(a,w,atop(inv(gs),ampco(fs,gs)));}


static DF1(jtunderai1){DECLF;A x,y,z;B b;I j,n,*u,*v;UC f[256],*wv,*zv;
 RZ(w);
 if(b=LIT&AT(w)&&256<AN(w)){
        x=df1(iota(v2(128L, 2L)),fs); b=x&&256==AN(x)&&NUMERIC&AT(x);
  if(b){y=df1(iota(v2(  8L,32L)),fs); b=y&&256==AN(y)&&NUMERIC&AT(y);}
  if(b){x=vi(x); y=vi(y); b=x&&y;} 
  if(b){u=AV(x); v=AV(y); DO(256, j=*u++; if(j==*v++&&-256<=j&&j<256)f[i]=(UC)(0<=j?j:j+256); else{b=0; break;});}
  if(jt->jerr)RESETERR;
 }
 if(!b)R from(df1(indexof(alp,w),fs),alp);
 n=AN(w);
 GA(z,LIT,n,AR(w),AS(w)); zv=UAV(z); wv=UAV(w);
 if(!bitwisecharamp(f,n,wv,zv))DO(n, *zv++=f[*wv++];); 
 R z;
}    /* f&.(a.&i.) w */

F2(jtunder){A x;AF f1,f2;B b,b1;C c;I m,r;V*u,*v;
 ASSERTVV(a,w);
 c=0; f1=jtunder1; f2=jtunder2; r=mr(w); v=VAV(w); 
 switch(v->id){
  case COPE:  f1=jteach1; f2=jteach2; break;
  case CFORK: c=ID(v->h); /* fall thru */
  case CAMP:  
   u=VAV(a);
   if(b1=CSLASH==u->id){x=u->f; u=VAV(x);}
   b=CBDOT==u->id&&(x=u->f,!AR(x)&&INT&AT(x)&&(m=*AV(x),16<=m&&m<32));
   if(CIOTA==ID(v->g)&&(!c||c==CLEFT||c==CRIGHT)&&equ(alp,v->f)){
    f1=b&& b1?jtbitwiseinsertchar:jtunderai1; 
    f2=b&&!b1?jtbitwisechar:u->id==CMAX||u->id==CMIN?jtcharfn2:jtunder2;
 }}
 R CDERIV(CUNDER,f1,f2,r,r,r);
}

F2(jtundco){
 ASSERTVV(a,w); 
 R CDERIV(CUNDCO,jtundco1,jtundco2,RMAX,RMAX,RMAX);
}
