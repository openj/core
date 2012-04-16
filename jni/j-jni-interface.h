#ifndef J_JNI_INTERFACE
#define J_JNI_INTERFACE

#ifdef ANDROID


#define ANDROID_ABI_ARM5 1
#define ANDROID_ABI_ARM7 2
#define ANDROID_ABI_x86  3

int _stdcall android_get_abi();
int _stdcall android_download_file(const char* url, const char* file);
int _stdcall android_unzip_file(const char* file, const char* todir);
int _stdcall android_launch_app(const char* action, const char* data, const char* type,int flags);
//char* _stdcall android_exec_host(const char *cmd);
void _stdcall android_quit();
void _stdcall android_free(void* ptr);
//extern char android_temp_dir[];
#endif

#ifdef ANDROID
#define LOCALOGTAG "j-interface"
#include <android/log.h>
#define LOGD(msg) __android_log_write(ANDROID_LOG_DEBUG,LOCALOGTAG,msg)
#define LOGFD(...) __android_log_print(ANDROID_LOG_DEBUG,LOCALOGTAG,__VA_ARGS__)

#ifdef __ARM_ARCH_7__
/* ARM-7 */
static int android_abi = ANDROID_ABI_ARM7;
#elseif defined(__ARM_ARCH_5__)
/* ARM-5 */
static int android_abi = ANDROID_ABI_ARM5;
#else
/*  x86 */
static int android_abi = ANDROID_ABI_x86;
#endif

#else
#include <stdio.h>
#define LOGD(msg) printf("%s: %s\n",LOCALOGTAG,msg)

#define LOGFD(str,...) printf(LOCALOGTAG " " str,__VA_ARGS__)

#endif

#endif // J_JNI_INTERFACE
