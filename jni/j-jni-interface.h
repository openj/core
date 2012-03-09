#ifndef J_JNI_INTERFACE

#ifdef ANDROID
int _stdcall android_download_file(const char* url, const char* file);
int _stdcall android_unzip_file(const char* file, const char* todir);
#endif

#endif // J_JNI_INTERFACE
