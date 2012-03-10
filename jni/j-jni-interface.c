#include "j.h"
#include "org_dykman_j_android_JInterface.h"
#include "j-jni-interface.h"
#include <strings.h>


/**
This is designed to explicitly to be used with the class file org.dykman.dykman.j.JInterface whic is part of a larger Android project hosted at
	https://github.com/mdykman/jconsole_for_android
It consists of the implementations of the native function declared in the class as well as a method for sending output ansynchronously to the Java layer.
While wrriten a part of an Android project, JInterface is generic enough to be used in any Java context that whishes to interact with J and capture it's output.
A subclass of JInterface, org.dykman.j.android.AndroidJInterface include additional android-specific methods which can be invoke from J, via 15!:0
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
jclass local_class;
jobject local_baseobj;

jmethodID outputId = 0;

void consoleAppend(JNIEnv *env, jobject obj,int type, const char*chars) {
	if(outputId == 0) {
//		jclass cls = (*env)->GetObjectClass(env,obj);
		outputId = (*env)->GetMethodID(env,local_class,"output","(ILjava/lang/String;)V" );
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
	local_class = (*env)->GetObjectClass(env,obj);
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
  setenv(key,val,0);
  free(key);
  free(val);
}



#ifdef ANDROID
const char* android_next_ptr = NULL;
const char* __nextLineFromAndroid(
		JNIEnv *env, 
		jobject obj) {
	local_class = (*env)->GetObjectClass(env,obj);
	jmethodID nextLineId = (*env)->GetMethodID(env,local_class,"nextLine","()Ljava/lang/String;" );
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
//	jclass cls = (*env)->GetObjectClass(env,obj);
	local_class = (*env)->GetObjectClass(env,obj);
	jmethodID downloadId = (*env)->GetMethodID(env,local_class,"downloadFile","(Ljava/lang/String;Ljava/lang/String;)I" );
	jstring jurl = (*env)->NewStringUTF(env,furl);
	jstring jfile = (*env)->NewStringUTF(env,ff);
	jint res = (*env)->CallIntMethod(env,obj,downloadId,jurl,jfile);
	return (int)res;
}


int _stdcall android_download_file(const char* furl, const char* ff) {
	return __downloadViaAndroid(local_jnienv, local_baseobj,furl,ff);
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
	local_jnienv = env;
	local_baseobj = obj;
	local_class = (*env)->GetObjectClass(env,obj);

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

