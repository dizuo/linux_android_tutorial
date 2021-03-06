LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := native

LOCAL_C_INCLUDES := $(LOCAL_PATH)/gtl \

LOCAL_SRC_FILES := native.cpp \
	gl_world.cpp \
	renderable.cpp \
	bp_loader.cpp \
	under_park.cpp \
	trackball.cpp \
	
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -lGLESv1_CM -llog -ljnigraphics

LOCAL_CFLAGS := -DES_ANDROID\
	-DANDROID_NDK \

include $(BUILD_SHARED_LIBRARY)