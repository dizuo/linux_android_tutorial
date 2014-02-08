LOCAL_PATH:= $(call my-dir)

#
## ����libprovider.so��
# 
include $(CLEAR_VARS)
LOCAL_MODULE := provider-prebuilt
LOCAL_SRC_FILES := libprovider.so
include $(PREBUILT_SHARED_LIBRARY)

#
## ÿ��buildʱ�����libs/armeabi���������so��.
## ��ָ����so��������libs/armeabiĿ¼�£�
# 
include $(CLEAR_VARS)
LOCAL_MODULE := navengine-prebuilt
LOCAL_SRC_FILES := libnavengine.so
include $(PREBUILT_SHARED_LIBRARY)

#
## ��ģ�鶨��
#
include $(CLEAR_VARS)
LOCAL_MODULE    := libtwolib-second
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := consumer.c

# ����libprovider.so û����仰���Ҳ����������壡
#refer : http://answers.opencv.org/question/18608/android-ndk-many-undefined-references/
LOCAL_SHARED_LIBRARIES += provider-prebuilt		

LOCAL_CFLAGS := -DANDROID_NDK \
				-DDEBUG \
				-fno-omit-frame-pointer -fno-function-sections \
				-funwind-tables	# ��ӡ������ջ

include $(BUILD_SHARED_LIBRARY)

