#ifdef ANDROID

#include "j.h"
#include "x.h"
#include "jni/j-jni-interface.h"

#include<stdlib.h>

F1(jthostne){A z;
 F1RANK(1,jthostne,0);
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

#endif
