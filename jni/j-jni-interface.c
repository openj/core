#include "j.h"
#include "org_dykman_j_android_JInterface.h"
#include <strings.h>
/*
#include <stdio.h>
*/



#define LOCALOGTAG "j-interface"
#ifdef ANDROID
#include <android/log.h>
#define LOGD(msg) __android_log_write(ANDROID_LOG_DEBUG,LOCALOGTAG,msg)
#define LOGFD(...) __android_log_print(ANDROID_LOG_DEBUG,LOCALOGTAG,__VA_ARGS__)
#else
#include <stdio.h>
#define LOGD(msg) printf("%s: %s\n",LOCALOGTAG,msg)

// TODO..  this is not right...
#define LOGFD(...) printf("%s: %s\n",LOCALOGTAG,__VA_ARGS__)
#endif

JNIEnv *local_jnienv;
jobject local_baseobj;

jmethodID outputId = 0;

void consoleAppend(JNIEnv *env, jobject obj,int type, const char*chars) {
	if(outputId == 0) {
		jclass cls = (*env)->GetObjectClass(env,obj);
		outputId = (*env)->GetMethodID(env,cls,"output","(ILjava/lang/String;)V" );
	}
	if(outputId == 0) {
		LOGD("failed to get the method id for " "output:" "(ILjava/lang/String;)V");
	} else {
		jstring str = (*env)->NewStringUTF(env,chars);
		(*env)->CallVoidMethod(env,obj,outputId,(jint)type,str);
	}
}

JNIEXPORT jint JNICALL Java_org_dykman_j_JInterface_callJNative
  (JNIEnv * env, jobject obj, jlong inst, jstring js) {
	J jengine = (J)inst;
	local_jnienv = env;
	local_baseobj = obj;
	const char *nativeString = (*env)->GetStringUTFChars(env, js, 0);
	int jc = JDo(jengine,(C*)nativeString);
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
LOGFD("type=%l,rank=%l,shapehead=%l,data=%p",type,rank,*shape,data);
		return NULL;
 }


void _stdcall outputHandler(J jt,int type, const char* s) {
		 consoleAppend(local_jnienv,local_baseobj,type,s);
}

/*
 * Class:     org_dykman_j_android_JActivity
 * Method:    initializeJNative
 * Signature: ()V
 */

JNIEXPORT jlong JNICALL Java_org_dykman_j_JInterface_initializeJNative
  (JNIEnv * env, jobject obj) {
	LOGD("init called");
	local_jnienv = env;
	local_baseobj = obj;
	outputId = 0;
	 J j = JInit();
	 void* callbacks[] = {outputHandler,0,0,0,(void*)SMJAVA};
	 JSM(j,callbacks);
	return (jlong) j;
}
