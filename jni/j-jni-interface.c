#include "j.h"
#include "org_dykman_j_android_JInterface.h"
#include "j-jni-interface.h"
#include <strings.h>
#include <fenv.h>


/**
This is designed to explicitly to be used with the class file org.dykman.dykman.j.JInterface whic is part of a larger Android project hosted at
	https://github.com/mdykman/jconsole_for_android
It consists of the implementations of the native function declared in the class as well as a method for sending output ansynchronously to the Java layer.
While written a part of an Android project, JInterface is generic enough to be used in any Java context that whishes to interact with J and capture it's output.
A subclass of JInterface, org.dykman.j.android.AndroidJInterface include additional android-specific methods which can be invoke from J, via 15!:0

Under this implementation, we rely on the jobject which calls these methods from java being a singleton.
 */

/*
char android_temp_dir[240];
 */
static JNIEnv *local_jnienv;
static jobject local_baseobj;


int jfetestexcept(int _except) {
	return fetestexcept(_except);
}

jmethodID outputId = 0;

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
	local_jnienv = env;
	local_baseobj = obj;

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

