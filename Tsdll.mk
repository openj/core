# This make file can be used to build J as part of an Android project.
# The project it was created for is hosted on github at
# https://github.com/mdykman/jconsole_for_android .
# openj should be checked out into a seperate folder under
# <project-root>/jni . That project is equipped with an Android.mk
# file which will invoke this one.
# Further detais on building J within the Android
# context can be found in that project
#
# this has been built under Android 2.1, API level 7. see note below
# this has been built under Android 2.2, API level 8.

# TARGET PLATFORMS

# As long as graphics are not a defining goal,
# Android 2.1 (API 7) has been selected as the
# target platform to admit the largest possible
# potential user base.
# Android 2.2 (API 8) offers a great deal more
# graphical power to applications with the
# inclusion of libGLESv2.so and should be the
# target for future builds hoping to integrate
# native graphics into the Android app.

# When building under Android API 7 (2.1)
# hostdefs.c fails to build as that platform
# lacks regex.h.  Under API 8 (2.2), the
# include below should be uncommented.
# The current release for Android 2.1 includes
# XXX_defs.ijs files generated under API 8.
# I am confident that these are sufficient
# for the present build.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := tsdll

LOCAL_LDLIBS := -lc

ifeq ($(TARGET_ARCH),arm)
  ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS := -Os -fno-strict-aliasing -fomit-frame-pointer -std=c99 -pedantic -mfloat-abi=softfp -mfpu=vfpv3-d16 -march=armv7-a -D__TARGET_FPU_VFP -D_MISALIGN_BYTEVECTOR -DNOASM -DOPENJ -D_FILE_OFFSET_BITS=64 -fPIC
  else
    LOCAL_CFLAGS := -Os -fno-strict-aliasing -fomit-frame-pointer -std=c99 -pedantic -mfloat-abi=softfp -D_MISALIGN_BYTEVECTOR -DNOASM -DOPENJ -D_FILE_OFFSET_BITS=64 -fPIC
  endif
endif
ifeq ($(TARGET_ARCH),mips)
  LOCAL_CFLAGS := -Os -fno-strict-aliasing -fomit-frame-pointer -std=c99 -pedantic -D_MISALIGN_BYTEVECTOR -DNOASM -DOPENJ -D_FILE_OFFSET_BITS=64 -fPIC
endif
ifeq ($(TARGET_ARCH),x86)
  LOCAL_CFLAGS := -Os -fno-strict-aliasing -fomit-frame-pointer -std=c99 -pedantic -msse2 -mfpmath=sse -D_MISALIGN_BYTEVECTOR -DNOASM -DOPENJ -D_FILE_OFFSET_BITS=64 -fPIC
endif

LOCAL_SRC_FILES :=  tsdll.c

include $(BUILD_SHARED_LIBRARY)
