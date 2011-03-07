/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Xenos: Host Command Facilities                                          */

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#else
#include <unistd.h>
#endif

#include "j.h"
#include "x.h"

#if (SYS & SYS_ARCHIMEDES)
#define Wimp_StartTask 0x400DE
extern int os_swi1(I,I);
#endif


#if (SYS & SYS_MACINTOSH)

F1(jthost  ){ASSERT(0,EVDOMAIN);}
F1(jthostne){ASSERT(0,EVDOMAIN);}

#else

F1(jthost){A z;
 F1RANK(1,jthost,0);
 RZ(w=vs(w));
#if (SYS & SYS_PCWIN)
 ASSERT(0,EVDOMAIN);
#else
{
 A t;I b;C*fn,*s;F f;I n;
 n=AN(w);
 GA(t,LIT,n+5+L_tmpnam,1,0); s=CAV(t);
 fn=5+n+s; MC(s,AV(w),n);
 MC(n+s,"   > ",5L); {C* t=tmpnam(fn);}
 b=!system(s);
 if(b){f=fopen(fn,FREAD); z=rd(f,0L,-1L); fclose(f);}
 unlink(fn);
 ASSERT(b&&f,EVFACE);
}
#endif
 R z;
}

F1(jthostne){C*s;
 F1RANK(1,jthostne,0);
 RZ(w=vs(w));
 s=CAV(w);
#if SYS & SYS_PCWIN
 ASSERT(0,EVNONCE);
#else
 {
  I b;
  b=system(s);
#if !SY_64 && (SYS&SYS_LINUX)
  //Java-jnative-j.so system always returns -1
  if(jt->sm==SMJAVA&&-1==b) b=-1==system("")?0:-1;
#endif
  b=!b;
  ASSERT(b,EVFACE);
 }
#endif
 R mtv;
}

#endif


#if !(SYS & SYS_UNIX)

F1(jthostio){ASSERT(0,EVDOMAIN);}
F1(jtjwait ){ASSERT(0,EVDOMAIN);}

#else

#define CL(f) {close(f[0]);close(f[1]);}

F1(jthostio){C*s;A z;F*pz;I fi[2],fo[2],r;int fii[2],foi[2];
 fii[0]=fi[0];fii[1]=fi[1];foi[0]=fo[0];foi[1]=fo[1];
 F1RANK(1,jthostio,0);
 RZ(w=vs(w));
 s=CAV(w); GA(z,INT,3,1,0); pz=(F*)AV(z);
 if((r=pipe(fii))==-1||pipe(foi)==-1){if(r!=-1)CL(fi); ASSERT(0,EVFACE);}
 if(!((pz[1]=fdopen(fi[0],"r"))&&(pz[2]=fdopen(fo[1],"w")))){
  if(pz[1])fclose(pz[1]); CL(fi);CL(fo);}
 if(!add2(pz[1],pz[2],s)){fclose(pz[1]);fclose(pz[2]);
                               CL(fi);CL(fo);}
 switch(r=fork()){
  case -1:CL(fi);CL(fo);ASSERT(0,EVFACE);
  case 0:close(0);{int i=dup(fo[0]);};close(1);{int i=dup(fi[1]);};CL(fi);CL(fo);
         execl("/bin/sh","/bin/sh","-c",s,NULL); exit(-1);
 }close(fo[0]);close(fi[1]);
 add2(NULL,NULL,NULL); pz[0]=(F)r;
 R z;
}

F1(jtjwait){I k;int s; RE(k=i0(w)); if(-1==waitpid(k,&s,0))jerrno(); R sc(s);}

#endif
