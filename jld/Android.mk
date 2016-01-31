
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := jld

LOCAL_LDLIBS := -llog  -ldl -lc 

LOCAL_CFLAGS := -O0  -fno-omit-frame-pointer -fno-strict-aliasing -fno-unwind-tables -fno-tree-vectorize -D_MISALIGN_BYTEVECTOR  -DNOASM  -fPIC


LOCAL_SRC_FILES := jld.c


ifneq ($(TARGET_ARCH_ABI),x86)
LOCAL_STATIC_LIBRARIES := cpufeatures
endif

include $(BUILD_SHARED_LIBRARY)

ifneq ($(TARGET_ARCH_ABI),x86)
$(call import-module,android/cpufeatures)
endif



