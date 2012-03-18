#ifndef J_JNI_INTERFACE

#ifdef ANDROID


#define ANDROID_ABI_ARM5 1
#define ANDROID_ABI_ARM7 2
#define ANDROID_ABI_x86  3

int _stdcall android_get_abi();
int _stdcall android_download_file(const char* url, const char* file);
int _stdcall android_unzip_file(const char* file, const char* todir);
void _stdcall android_quit();
#endif

#endif // J_JNI_INTERFACE
