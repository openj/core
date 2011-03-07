/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Xenos: File Lock/Unlock                                                 */

#include "j.h"
#include "x.h"

#if SY_WINCE || !(SYS & SYS_DOS+SYS_MACINTOSH)
#define LOCK 1
static B jtdolock(J jt,B lk,F f,I i,I n){ASSERT(0,EVNONCE);}
#endif

#if SY_WIN32 && SYS&SYS_DOS && !SY_WINCE
#define LOCK 1
#include <sys/locking.h>

extern int _locking(int,int,long);

static B jtdolock(J jt,B lk,F f,I i,I n){I e;long c;fpos_t v; fpos_t q;
 c=fgetpos(f,(fpos_t*)&q);
 if(0!=c)R (B)jerrno();
 v=i;
 c=fsetpos(f,(fpos_t*)&v);
 if(0!=c)R (B)jerrno();
 e=_locking(_fileno(f),lk?_LK_NBLCK:_LK_UNLCK,(long)n);
 fsetpos(f,(fpos_t*)&q);
 R !e?1:errno==EACCES?0:(B)jerrno();
}
#endif

#ifndef LOCK
static B jtdolock(J jt,B lk,F f,I i,I n){I e;
 e=lk?lock(fileno(f),i,n):unlock(fileno(f),i,n);
 R !e?1:errno==EACCES?0:jerrno();
}
#endif

#define LKC  3      /* number of columns in jt->flkd table       */

B jtxlinit(J jt){A x;I*s;
 GA(x,INT,20*LKC,2,0); s=AS(x); s[0]=20; s[1]=LKC; ra(x); 
 jt->flkd=x;
 R 1;
}

F1(jtjlocks){A y; ASSERTMTV(w); y=take(sc(jt->flkn),jt->flkd); R grade2(y,y);}
     /* return the locks, a 3-column table of (number,index,length) */

F1(jtjlock){B b;I*v;
 F1RANK(1,jtjlock,0);
 RZ(w=vi(w)); 
 ASSERT(LKC==AN(w),EVLENGTH);
 v=AV(w); RE(vfn((F)*v)); ASSERT(0<=v[1]&&0<=v[2],EVDOMAIN); 
 if(jt->flkn==*AS(jt->flkd))RZ(jt->flkd=ext(1,jt->flkd));
 RE(b=dolock(1,(F)v[0],v[1],v[2]));
 if(!b)R zero;
 ICPY(AV(jt->flkd)+LKC*jt->flkn,v,LKC); ++jt->flkn;
 R one;
}    /* w is (number,index,length); lock the specified region */

static A jtunlj(J jt,I j){B b;I*u,*v;
 RE(j);
 ASSERT(0<=j&&j<jt->flkn,EVINDEX);
 u=AV(jt->flkd); v=u+j*LKC;
 RE(b=dolock(0,(F)v[0],v[1],v[2]));
 if(!b)R zero;
 --jt->flkn; 
 if(j<jt->flkn)ICPY(v,u+jt->flkn*LKC,LKC); else *v=0; 
 R one;
}    /* unlock the j-th entry in jt->flkd */

B jtunlk(J jt,I x){I j=0,*v=AV(jt->flkd); 
 while(j<jt->flkn){while(x==*v)RZ(unlj(j)); ++j; v+=LKC;} 
 R 1;
}    /* unlock all existing locks for file# x */

F1(jtjunlock){
 F1RANK(1,jtjunlock,0); 
 ASSERT(INT&AT(w),EVDOMAIN); 
 R unlj(i0(indexof(jt->flkd,w))); 
}    /* w is (number,index,length); unlock the specified region */
