
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := j-netdefs

LOCAL_LDLIBS := -llog  -ldl -lm -lc 

LOCAL_CFLAGS := -O0  -fno-omit-frame-pointer -fno-strict-aliasing -fno-unwind-tables -fno-tree-vectorize -D_MISALIGN_BYTEVECTOR  -DNOASM  -fPIC


LOCAL_SRC_FILES := ../netdefs.c


include $(BUILD_EXECUTABLE)



