#include "j.h"
#include "org_dykman_j_android_JInterface.h"
#include "j-jni-interface.h"
#include <strings.h>

/**
This is designed to explicitly to be used with the class file org.dykman.dykman.j.JInterface whic is part of a larger Android project hosted at
	https://github.com/mdykman/jconsole_for_android
It consists of the implementations of the native function declared in the class as well as a method for sending output ansynchronously to the Java layer.
While written a part of an Android project, JInterface is generic enough to be used in any Java context that whishes to interact with J and capture it's output.
A subclass of JInterface, org.dykman.j.android.AndroidJInterface include additional android-specific methods which can be invoke from J, via 15!:0

Under this implementation, we rely on the jobject which calls these methods from java being a singleton.
 */

// #define JNIGNULL (*env)->NewGlobalRef(env, NULL)
#define JNIGNULL (void*)0

/*
char android_temp_dir[240];
 */
static JavaVM *jvm;
static JNIEnv *local_jnienv;
static jobject local_baseobj;

jmethodID outputId = 0;

int _stdcall GetJavaVM(JavaVM ** pvm, JNIEnv ** penv){
 *pvm = jvm;
 *penv = local_jnienv;
 return 0;
}

void consoleAppend(JNIEnv *env, jobject obj,int type, const char*chars) {
	if(outputId == 0) {
  	   jclass the_class = (*env)->GetObjectClass(env,obj);
		outputId = (*env)->GetMethodID(env,the_class,"output","(ILjava/lang/String;)V" );
	}
	if(outputId == 0) {
		LOGD("failed to get the method id for " "output:" "(ILjava/lang/String;)V");
	} else {
		jstring str = (*env)->NewStringUTF(env,chars);
		(*env)->CallVoidMethod(env,obj,outputId,(jint)type,str);
	}
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	LOGD("jni-onload called");
    jvm = vm;
    if ((*vm)->GetEnv(vm, (void **)&local_jnienv, JNI_VERSION_1_6) != JNI_OK) {
	LOGD("failed jni check");
        return -1;
    }

    // Get jclass with env->FindClass.
    // Register methods with env->RegisterNatives.

	LOGD("returning from jni-onload");
    return JNI_VERSION_1_6;
}

JNIEXPORT jint JNICALL Java_org_dykman_j_JInterface_callJNative
  (JNIEnv * env, jobject obj, jlong inst, jstring js) {
	LOGD("called callJNative ");
	J jengine = (J)inst;

	LOGD(":::: callJNative format string");
	const char *nativeString = (*env)->GetStringUTFChars(env, js, 0);
	LOGD(":::: callJNative jdo");
	int jc = JDo(jengine,(C*)nativeString);
	LOGD(":::: callJNative returning");
	return (jint) jc;
}

JNIEXPORT void JNICALL Java_org_dykman_j_JInterface_destroyJNative
  (JNIEnv *env, jobject obj, jlong inst) {
	LOGD("free called");
	JFree((J)inst);
	outputId = 0;
}

JNIEXPORT jobject JNICALL Java_org_dykman_j_JInterface_getVariableNative
  (JNIEnv *env, jobject obj, jlong inst, jstring jname) {
	J jengine = (J)inst;
	const char *name = (*env)->GetStringUTFChars(env, jname, 0);
	long type, rank;
	long *shape;
	char *data;

	JGetM(jengine,(I*)&type,(I*)&rank,(I*)&shape,(I*)&data);
LOGFD("name=%s,type=%l,rank=%l,shapehead=%l,data=%p",name,type,rank,*shape,data);
		return NULL;
 }


void _stdcall outputHandler(J jt,int type, const char* s) {
		 consoleAppend(local_jnienv,local_baseobj,type,s);
}

JNIEXPORT void JNICALL Java_org_dykman_j_JInterface_setEnv
  (JNIEnv *env, jobject obj, jstring jkey, jstring jval) {
  char*key =  (*env)->GetStringUTFChars(env, jkey, 0);
  char*val =  (*env)->GetStringUTFChars(env, jval, 0);
  /*
  if(strcmp(key,"TMP")==0) {
  	 strcpy(android_temp_dir,val);
  }
  */
  setenv(key,val,0);
  free(key);
  free(val);
}



int __unzipViaJava(
		JNIEnv *env,
		jobject obj,
		const char* file,
		const char* dir) {
	jclass the_class = (*env)->GetObjectClass(env,obj);
	jmethodID unzipId = (*env)->GetMethodID(env,the_class,"unzipS","(Ljava/lang/String;Ljava/lang/String;)I" );
	jstring jfile = (*env)->NewStringUTF(env,file);
	jstring jdir = dir == NULL ? NULL : (*env)->NewStringUTF(env,dir);
	jint res = (*env)->CallIntMethod(env,obj,unzipId,jfile,jdir);
	return (int)res;
}


int _stdcall java_unzip_file(const char* file, const char* todir) {
/* make the empty string equate to null to accomodate J (he guessed) */
	const char* _todir = todir == NULL || strlen(todir) == 0 ? NULL : todir;
	return __unzipViaJava(local_jnienv, local_baseobj,file,_todir);
}


#ifdef ANDROID
const char* android_next_ptr = NULL;
const char* __nextLineFromAndroid(
		JNIEnv *env,
		jobject obj) {
	jclass the_class = (*env)->GetObjectClass(env,obj);
	jmethodID nextLineId = (*env)->GetMethodID(env,the_class,"nextLine","()Ljava/lang/String;" );
	/* this method blocks via sleep until a line is available */
	jstring res = (jstring) (*env)->CallObjectMethod(env,obj,nextLineId);
	if(android_next_ptr != NULL) {
		free((char*)android_next_ptr);
	}
	android_next_ptr = (*env)->GetStringUTFChars(env, res, 0);
	return android_next_ptr;
}

const char * _stdcall android_next_line() {
	return __nextLineFromAndroid(local_jnienv,local_baseobj);
}
int __downloadViaAndroid(
		JNIEnv *env,
		jobject obj,
		const char* furl,
		const char* ff) {
	jclass the_class = (*env)->GetObjectClass(env,obj);
	jmethodID downloadId = (*env)->GetMethodID(env,the_class,"downloadFile","(Ljava/lang/String;Ljava/lang/String;)I" );
	jstring jurl = (*env)->NewStringUTF(env,furl);
	jstring jfile = (*env)->NewStringUTF(env,ff);
	jint res = (*env)->CallIntMethod(env,obj,downloadId,jurl,jfile);
	return (int)res;
}

int _stdcall android_download_file(const char* furl, const char* ff) {
	return __downloadViaAndroid(local_jnienv, local_baseobj,furl,ff);
}

void __quitViaAndroid(
		JNIEnv *env,
		jobject obj) {
	jclass the_class = (*env)->GetObjectClass(env,obj);
	jmethodID quitId = (*env)->GetMethodID(env,the_class,"quit","()V" );
	(*env)->CallVoidMethod(env,obj,quitId);
}


int _stdcall android_get_abi() {
	return android_abi;
}

void _stdcall android_quit() {
  __quitViaAndroid(local_jnienv,local_baseobj);
}

/*
const char * __hostExecAndroid(
	JNIEnv* env,
	jobject obj,
	const char* cmd) {
	jclass the_class = (*env)->GetObjectClass(env,obj);


	jmethodID execId = (*env)->GetMethodID(env,the_class,"execHostCommand","(Ljava/lang/String;)Ljava/lang/String;");
	jstring jcmd = (*env)->NewStringUTF(env,cmd);
	jstring jres = (jstring) (*env)->CallObjectMethod(env,obj,execId,jcmd);
	const char *res = (*env)->GetStringUTFChars(env, jres, 0);
	return res;
}

char* _stdcall android_exec_host(const char *cmd) {
	return __hostExecAndroid(local_jnienv,local_baseobj,cmd);
}
 */

void _stdcall android_free(void *ptr) {
	free(ptr);
}

int __launchActivityAndroid(
	JNIEnv* env,
	jobject obj,
	const char* action,
	const char* data,
	const char* type,
	int flags
	) {
	jclass the_class = (*env)->GetObjectClass(env,obj);
	jmethodID methodId = (*env)->GetMethodID(env,the_class,"launchActivity","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)I");
	jstring jaction = (*env)->NewStringUTF(env,action);
	jstring jdata = (*env)->NewStringUTF(env,data);
	jstring jtype = (*env)->NewStringUTF(env,type);
	jint jres = (*env)->CallIntMethod(env,obj,methodId,jaction,jdata,jtype,(jint)flags);
	return (int) jres;
}
int _stdcall android_launch_app(const char* action, const char* data, const char* type,int flags) {
  return __launchActivityAndroid(local_jnienv,local_baseobj,action,data,type,flags);
}
#endif

/*
 * Class:     org_dykman_j_android_JActivity
 * Method:    initializeJNative
 * Signature: ()V
 */

JNIEXPORT jlong JNICALL Java_org_dykman_j_JInterface_initializeJNative
  (JNIEnv * env, jobject obj) {
	LOGD("init called");
//	local_jnienv = env;
	local_baseobj = (*env)->NewGlobalRef(env,obj);

  (*env)->ExceptionClear(env);
	outputId = 0;
	 J j = JInit();
#ifdef ANDROID
	 void* callbacks[] = {outputHandler,0,android_next_line,0,(void*)SMJAVA};
#else
	 void* callbacks[] = {outputHandler,0,0,0,(void*)SMJAVA};
#endif
	 JSM(j,callbacks);
	return (jlong) j;
}

/*
 *   jnido....   callback to j
 */

static A jnidocall (JNIEnv * env, jobject obj, J jt, jobject appobj, jstring verb, jobjectArray objarr) {
  const char *nativeverb = (*env)->GetStringUTFChars(env, verb, 0);
  char str[200];   /* do not reduce to 100, crash will occur if verb is long. This had happened */
#if SY_64
  sprintf(str, "\'%s\' (jnhandler ::0:) (%li),(%li),(%li),(%li)", nativeverb, (jlong)env, (jlong)obj, (jlong)appobj, (jlong)objarr);
#else
  sprintf(str, "\'%s\' (jnhandler ::0:) (%i),(%i),(%i),(%i)", nativeverb, (jint)env, (jint)obj, (jint)appobj, (jint)objarr);
#endif
  (*env)->ReleaseStringUTFChars(env, verb, nativeverb);
  A ret = exec1(cstr(str));
  (*env)->ExceptionClear(env);
  return ret;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnido
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_dykman_j_JInterface_jnido
  (JNIEnv * env, jobject obj, jlong jt0, jobject appobj, jstring verb, jobjectArray objarr) {
  J jt = (J)jt0;
  PROLOG;
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jclass clz;
  jmethodID mid;
  jobject retobj;
  I rc = 0;int rettype = 0;
  if(!r||(1!=(AN(r))&&((BOX==AT(r))||(INT==AT(r))||(FL==AT(r))||(B01==AT(r))))) {tpop(_ttop); /* LOGD("jnido return null object"); */ return JNIGNULL;}
  if(B01==AT(r)) {rettype = B01;
  clz = (*env)->FindClass( env, "java/lang/Boolean" );
  mid = (*env)->GetMethodID( env, clz, "<init>", "(Z)V" );
  retobj = (*env)->NewObject( env, clz, mid, (jboolean)*(unsigned char*)AV(r) );
  (*env)->DeleteLocalRef(env, clz);
	// LOGD("jnido return boolean object");
  tpop(_ttop); return retobj;
  }
  if(INT==AT(r)) { rettype = INT;
#if SY_64
  clz = (*env)->FindClass( env, "java/lang/Long" );
  mid = (*env)->GetMethodID( env, clz, "<init>", "(J)V" );
  retobj = (*env)->NewObject( env, clz, mid, (jlong)*(I*)AV(r) );
#else
  clz = (*env)->FindClass( env, "java/lang/Integer" );
  mid = (*env)->GetMethodID( env, clz, "<init>", "(I)V" );
  retobj = (*env)->NewObject( env, clz, mid, (jint)*(I*)AV(r) );
#endif
  (*env)->DeleteLocalRef(env, clz);
	// LOGD("jnido return integer object");
  tpop(_ttop); return retobj;
  }
  if(FL==AT(r)) {rettype = FL;
  clz = (*env)->FindClass( env, "java/lang/Double" );
  mid = (*env)->GetMethodID( env, clz, "<init>", "(D)V" );
  retobj = (*env)->NewObject( env, clz, mid, *(D*)AV(r) );
  (*env)->DeleteLocalRef(env, clz);
	// LOGD("jnido return double object");
  tpop(_ttop); return retobj;
  }
  if(LIT==AT(r)) {rettype = LIT;
	jstring str = (*env)->NewStringUTF(env,(C*)AV(r));
	// LOGD("jnido return string object");
  tpop(_ttop); return str;
  }
  if(C2T==AT(r)) {rettype = C2T;
  retobj = (*env)->NewString( env, (jchar*)AV(r), AN(r) );
	// LOGD("jnido return string (from wchar) object");
  tpop(_ttop); return retobj;
  }
  if(BOX==AT(r)) {
  A ra = (A)*AV(r);
  if (B01==AT(ra)&&(1==AN(ra))) {rettype = BOX;
  if(!(*(unsigned char*)AV(ra))) {tpop(_ttop); /* LOGD("jnido return null object"); */ return JNIGNULL;}
  else {tpop(_ttop); return (jobject)*(unsigned char*)AV(ra);}
  } else if(INT==AT(ra)&&(1==AN(ra))) {rettype = BOX;
  if(!(*(I*)AV(ra))) {tpop(_ttop); /* LOGD("jnido return null object"); */ return JNIGNULL;}
  else {tpop(_ttop); 
	// LOGD("jnido return jobject object");
  return (jobject)*(I*)AV(ra);}
  }
  }
  tpop(_ttop); /* LOGD("jnido return null object"); */ return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidoz
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[Z
 */
JNIEXPORT jbooleanArray JNICALL Java_org_dykman_j_JInterface_jnidoz
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jbooleanArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (B01==AT(r)) {
    retobjarr = (*env)->NewBooleanArray( env, n );
    (*env)->SetBooleanArrayRegion( env, retobjarr, 0, n, (jboolean*)AV(r) );
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidos
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[S
 */
JNIEXPORT jshortArray JNICALL Java_org_dykman_j_JInterface_jnidos
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jshortArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (INT==AT(r)) {
    retobjarr = (*env)->NewShortArray( env, n );
    I* pr = (I*)AV(r); jshort tmp;
    for (int i=0; i<n; i++) {tmp = (jshort)*(pr+i); (*env)->SetShortArrayRegion( env, retobjarr, i, 1, &tmp ); }
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidoi
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[I
 */
JNIEXPORT jintArray JNICALL Java_org_dykman_j_JInterface_jnidoi
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jintArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (INT==AT(r)) {
    retobjarr = (*env)->NewIntArray( env, n );
#if SY_64
    jlong* pr = (I*)AV(r); jint tmp;
    for (int i=0; i<n; i++) {tmp = (jint)*(pr+i); (*env)->SetIntArrayRegion( env, retobjarr, i, 1, &tmp ); }
#else
    (*env)->SetIntArrayRegion( env, retobjarr, 0, n, (jint*)AV(r) );
#endif
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidol
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[J
 */
JNIEXPORT jlongArray JNICALL Java_org_dykman_j_JInterface_jnidol
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jlongArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (INT==AT(r)) {
    retobjarr = (*env)->NewLongArray( env, n );
#if SY_64
    (*env)->SetLongArrayRegion( env, retobjarr, 0, n, (jlong*)AV(r) );
#else
    jint* pr = (I*)AV(r); jlong tmp;
    int i;
    for (i=0; i<n; i++) {tmp = (jlong)*(pr+i); (*env)->SetLongArrayRegion( env, retobjarr, i, 1, &tmp ); }
#endif
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidof
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[F
 */
JNIEXPORT jfloatArray JNICALL Java_org_dykman_j_JInterface_jnidof
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jfloatArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (FL==AT(r)) {
    retobjarr = (*env)->NewFloatArray( env, n );
    D* pr = (D*)AV(r); jfloat tmp;
    for (int i=0; i<n; i++) {tmp = (jfloat)*(pr+i); (*env)->SetFloatArrayRegion( env, retobjarr, i, 1, &tmp ); }
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidod
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_org_dykman_j_JInterface_jnidod
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jdoubleArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (FL==AT(r)) {
    retobjarr = (*env)->NewDoubleArray( env, n );
    (*env)->SetDoubleArrayRegion( env, retobjarr, 0, n, (jdouble*)AV(r) );
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidoc
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dykman_j_JInterface_jnidoc
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jbyteArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (LIT==AT(r)) {
    retobjarr = (*env)->NewByteArray( env, n );
    (*env)->SetByteArrayRegion( env, retobjarr, 0, n, (jbyte*)AV(r) );
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidow
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[C
 */
JNIEXPORT jcharArray JNICALL Java_org_dykman_j_JInterface_jnidow
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jcharArray retobjarr;
  I n = AN(r);
  if(!r) {return JNIGNULL;}
  else if (C2T==AT(r)) {
    retobjarr = (*env)->NewCharArray( env, n );
    (*env)->SetCharArrayRegion( env, retobjarr, 0, n, (jchar*)AV(r) );
    return retobjarr;
  } else return JNIGNULL;
}

/*
 * Class:     org_dykman_j_JInterface
 * Method:    jnidox
 * Signature: (JLjava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)[Ljava/lang/Object;
 */
JNIEXPORT jobjectArray JNICALL Java_org_dykman_j_JInterface_jnidox
  (JNIEnv * env, jobject obj, jlong jt, jobject appobj, jstring verb, jobjectArray objarr) {
  A r = jnidocall (env, obj, (J)jt, appobj, verb, objarr);

  jobjectArray retobjarr;
  I n = AN(r);
  if (B01==AT(r)) {
    C* rab = (C*)AV(r);
    jclass clzobject = (*env)->FindClass( env, "java/lang/Object" );
    retobjarr = (*env)->NewObjectArray( env, n, clzobject, 0 );
    int i;
    for (i=0;i<n;i++) {
      if(!(*(unsigned char*)(i+rab))) (*env)->SetObjectArrayElement( env, retobjarr, i, JNIGNULL );
      else (*env)->SetObjectArrayElement( env, retobjarr, i, (jobject)*(unsigned char*)(i+rab) );
    }
    return retobjarr;
  } else if (INT==AT(r)) {
    I* rai = (I*)AV(r);
    jclass clzobject = (*env)->FindClass( env, "java/lang/Object" );
    retobjarr = (*env)->NewObjectArray( env, n, clzobject, 0 );
    int i;
    for (i=0;i<n;i++) {
      if(!(*(I*)(i+rai))) (*env)->SetObjectArrayElement( env, retobjarr, i, JNIGNULL );
      else (*env)->SetObjectArrayElement( env, retobjarr, i, (jobject)*(I*)(i+rai) );
    }
    return retobjarr;
  } else if (BOX==AT(r)) {
    A ra;
    A* rap = (A*)AV(r);
    int err=0;
    jclass clzobject = (*env)->FindClass( env, "java/lang/Object" );
    retobjarr = (*env)->NewObjectArray( env, n, clzobject, 0 );
    int i,j;
    for (i=0;i<n;i++) {
      ra = rap[i];
      if((B01==AT(ra))&&(1==AN(ra))) {
        if(!(*(unsigned char*)AV(ra))) (*env)->SetObjectArrayElement( env, retobjarr, i, JNIGNULL );
        else (*env)->SetObjectArrayElement( env, retobjarr, i, (jobject)*(unsigned char*)AV(ra) );
      } else if((INT==AT(ra))&&(1==AN(ra))) {
        if(!(*(I*)AV(ra))) (*env)->SetObjectArrayElement( env, retobjarr, i, JNIGNULL );
        else (*env)->SetObjectArrayElement( env, retobjarr, i, (jobject)*(I*)AV(ra) );
      } else {err=1; break;}
    }
    if (!err) {
      return retobjarr;
    } else {
//    for (j=0;j<i;j++) (*env)->DeleteLocalRef(env, (*env)->GetObjectArrayElement( env, retobjarr, j  ) );

      (*env)->DeleteLocalRef(env, retobjarr);
      return JNIGNULL;
    }
  } else return JNIGNULL;
}

