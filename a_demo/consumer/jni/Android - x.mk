LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libtwolib-second
LOCAL_SRC_FILES := consumer.c
LOCAL_LDLIBS := $(LOCAL_PATH)/libprovider.a			# input *.o, *.a files !

include $(BUILD_SHARED_LIBRARY)
