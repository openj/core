/** 
 * This is a loader for libj on android
 * It attempts to determine whether or not 
 * the device is equipped with a hardware
 * FPU, and then loader the version which
 * has been compiled explicitly for the current 
 * platform
 * - mdykman
 */

#include<stdio.h>
#include <jni.h>
#include <dlfcn.h>

#ifdef __ARM_ARCH_5__
   #include <machine/cpu-features.h>
#endif


int fpuEmu();

jint JNI_On_Load(JavaVM*env, void* reserved) {
 // TODO: can I capture stderr here??
 
 // I don't need my full path, I don't think
 char*lib = fpuEmu() ? "./libj-emu.so" : "./libj-fpu.so";
 void*r=dlopen(lib,RTLD_LAZY);
 if(r==NULL) {
	fprintf(stderr,"error in library loader %s: %s\n",lib,dlerror());
	return 1;

 } else {
	fprintf(stderr,"successfully loaded: %s\n",lib);
	/*
	 // this probably is neither neccessary nor advisable
 	int(*onload)(JavaVM*jvm,void*res) = dlsym(r,"JNI_On_Load");
	return onload(env,reserved);
	*/
 }
 return 0;
}

#ifdef __ARM_ARCH_5__
int __fpuEmu() {
	uint64_t flags = android_getCpuFeatures();
}
#endif
// return 1 if using fpu-emu, otherwise 0
int fpuEmu() {
 return system("grep \'\\<fpu\\>\' /proc/cpuinfo");
}
