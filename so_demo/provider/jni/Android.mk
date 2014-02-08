LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libprovider
LOCAL_SRC_FILES := one.c
LOCAL_SRC_FILES += two.c
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
