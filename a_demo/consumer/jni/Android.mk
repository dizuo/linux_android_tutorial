LOCAL_PATH:= $(call my-dir)

# 自己编译的库采用这种形式
include $(CLEAR_VARS)
LOCAL_MODULE := lib_provider
LOCAL_SRC_FILES := libprovider.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libtwolib-second
LOCAL_SRC_FILES := consumer.c

LOCAL_STATIC_LIBRARIES := lib_provider

# 系统的库采用这种形式
# LOCAL_LDLIBS := $(LOCAL_PATH)/libprovider.a			# input *.o, *.a files !

include $(BUILD_SHARED_LIBRARY)
