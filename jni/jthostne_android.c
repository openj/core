#ifdef ANDROID

#include "j.h"
#include "x.h"
#include "jni/j-jni-interface.h"

#include<stdlib.h>

F1(jthostne){A z;
 F1RANK(1,jthostne,0);
 ASSERT(AT(w)==BOX,EVFACE);
 ASSERT(AN(w)==3,EVFACE);
 A* l=AAV(w);
 char* ac; char* d; char* t; I lr;

#define BXD(ptr,arr)            \
 ASSERT(AT(*(arr))==LIT,EVFACE);  \
 lr = AN(*(arr));                 \
 ptr=(char*)malloc((int)lr+1);  \
 strncpy(ptr,CAV(*(arr)),lr);     \
 *(ptr+(int)lr) = 0;            \

 BXD(ac,l+0);
 BXD(d,l+1);
 BXD(t,l+2);

 int res = android_launch_app(ac,d,t);
 free(t); free(d); free(ac);
 R sc(res);
}

#endif
