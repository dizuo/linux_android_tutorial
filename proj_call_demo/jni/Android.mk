LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(info super local path = $(LOCAL_PATH))

include jni/app/Android.mk  
include jni/libpng/Android.mk

