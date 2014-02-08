LOCAL_PATH:= $(call my-dir)

#
## 导入libprovider.so库
# 
include $(CLEAR_VARS)
LOCAL_MODULE := provider-prebuilt
LOCAL_SRC_FILES := libprovider.so
include $(PREBUILT_SHARED_LIBRARY)

#
## 每次build时会清空libs/armeabi下面的所有so包.
## 将指定的so包拷贝到libs/armeabi目录下，
# 
include $(CLEAR_VARS)
LOCAL_MODULE := navengine-prebuilt
LOCAL_SRC_FILES := libnavengine.so
include $(PREBUILT_SHARED_LIBRARY)

#
## 主模块定义
#
include $(CLEAR_VARS)
LOCAL_MODULE    := libtwolib-second
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := consumer.c

# 关联libprovider.so 没有这句话会找不到函数定义！
#refer : http://answers.opencv.org/question/18608/android-ndk-many-undefined-references/
LOCAL_SHARED_LIBRARIES += provider-prebuilt		

LOCAL_CFLAGS := -DANDROID_NDK \
				-DDEBUG \
				-fno-omit-frame-pointer -fno-function-sections \
				-funwind-tables	# 打印完整堆栈

include $(BUILD_SHARED_LIBRARY)

