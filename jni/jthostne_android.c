#ifdef ANDROID

#include "j.h"
#include "x.h"
#include "jni/j-jni-interface.h"

#include<stdlib.h>



#if defined(link)
//#error link is as *link*
#undef link
#endif
#include<unistd.h>

F1(jthostne){A z;C*s;
 F1RANK(1,jthostne,0);
 if (isatty(0)) {
 ASSERT(AT(w)==LIT,EVFACE);
 RZ(w=vs(w));
 s=CAV(w);
#if SYS & SYS_PCWIN
 ASSERT(0,EVNONCE);
#else
 {
  I b;
  b=system(s);
#if !SY_64 && (SYS&SYS_LINUX) && !ANDROID
  //Java-jnative-j.so system always returns -1
  if(jt->sm==SMJAVA&&-1==b) b=-1==system("")?0:-1;
#endif
  b=!b;
  ASSERT(b,EVFACE);
 }
#endif
 R mtv;
 } else {
 ASSERT(AT(w)==BOX,EVFACE);
 int an=AN(w);
 ASSERT(an>=2,EVFACE);
 A* l=AAV(w);
 char* ac; char* d; char* t; I lr;
 int flags=0;

#define BXD(ptr,arr,nn)              \
 if(nn<an) {                         \
   ASSERT(AT(*(arr+nn))==LIT,EVFACE);  \
   lr = AN(*(arr+nn));                 \
   ptr=(char*)malloc((int)lr+1);       \
   strncpy(ptr,CAV(*(arr+nn)),lr);     \
   *(ptr+(int)lr) = 0;                 \
 } else {                              \
   ptr = NULL;                         \
 }

 BXD(ac,l,0);
 BXD(d,l,1);
 BXD(t,l,2);
 if(an>3) {
   ASSERT(AT(*(l+3))==INT,EVFACE);
 	flags=*IAV(*(l+3));
 }

 int res = android_launch_app(ac,d,t,flags);
 if(t!=NULL) free(t); if(d!=NULL) free(d); if(ac!=NULL) free(ac);
 R sc(res);
 }
}

#endif
