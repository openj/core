
# This makefile fragment calls for the building of subdirectories containing their own Android.mk

# In this case, it causes netdefs and hostdefs to be created. The Android build system copys the final
# binary to the directory <PROJECT_ROOT>/libs/<platform>
# In order to build an Android package,
# those binaries must be uploaded onto an android device or emulator and executed.
# The output of these programs become netdefs_android.ijs and hostdefs_android.ijs respectively.
# They must be placed in <PROJECT_ROOT>/assets/system/defs in the final package in order to
# be installed at first boot along with the rest of the system files.

# If you have the Android emulator installed as part of the Android Developers Toolkit (ADK), the
# tool adb may be used to automate the generation of XXXdefs_android.ijs for the ARM5 processor only
# as neither the ARM7 nor x86 are directly supported by the emulator.  The NDK (the native development toolkit)
# provides cross-compilers and build support for all 3 platforms
#
# This might be integrated into the final step of the make process, after the NDK has built the binaries.
# The following assumes that an emulator is running on your system.  Below is an example of how it might be
# automated with a shell script.

# The emulator is assumed to be running Android version 2.2
#
# ADB=<ANDROID_SDK_HOME>/platform-tools/adb
# BINSRC=<PROJECT_ROOT>/libs/armeabi
# EMUNAME=<emulator-name>
#
# $ADB start-server
# $ADB -s $EMUNAME wait-for-device # blocks until the device is available
# $ADB -s $EMUNAME push ${BINSRC}/j-hostdefs /data/local/tmp
# $ADB -s $EMUNAME shell /data/local/tmp/j-hostdefs > hostdefs_android.ijs
# $ADB -s $EMUNAME shell rm /data/local/tmp/j-hostdefs
# $ADB -s $EMUNAME shell /data/local/tmp/j-netdefs > netdefs_android.ijs
# $ADB -s $EMUNAME shell rm /data/local/tmp/j-hostdefs
#

# For convenience, a copy of these 2 def files have already been generated on an armeabi (ARM5) emulator
# and placed in assets/system/defs.


LOCAL_PATH:=(call my-dir)

TARGET_PLATFORM := android-8

# include $(call all-subdir-makefiles)

include jni/openj-core/defs/hostdefs/Android.mk
include jni/openj-core/defs/netdefs/Android.mk
