LOCAL_PATH:= $(call my-dir)

# first lib, which will be built statically
#
include $(CLEAR_VARS)

LOCAL_MODULE    := libprovider
LOCAL_SRC_FILES := one.c
LOCAL_SRC_FILES += two.c

include $(BUILD_STATIC_LIBRARY)

# second lib, which will depend on and include the first one
#
include $(CLEAR_VARS)

LOCAL_MODULE    := main
LOCAL_SRC_FILES := three.c
LOCAL_LDLIBS    := -llog

LOCAL_STATIC_LIBRARIES := libprovider

include $(BUILD_SHARED_LIBRARY)
