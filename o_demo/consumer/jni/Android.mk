LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libtwolib-second
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_SRC_FILES := consumer.c
LOCAL_SRC_FILES += two.c				# 其他模块以源码形式发布！

LOCAL_LDLIBS := $(LOCAL_PATH)/one.o		# one模块以.o形式发布

include $(BUILD_SHARED_LIBRARY)

