LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := native
LOCAL_SRC_FILES := native.cpp
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib

include $(BUILD_SHARED_LIBRARY)