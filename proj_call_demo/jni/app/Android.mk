LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JniModules

$(info app local path = $(LOCAL_PATH))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../

$(info app c_include_path = $(LOCAL_C_INCLUDES))

LOCAL_SRC_FILES := JniModules.cpp

LOCAL_STATIC_LIBRARIES := libpng libzip

include $(BUILD_SHARED_LIBRARY)
