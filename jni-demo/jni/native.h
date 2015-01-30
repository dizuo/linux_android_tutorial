#ifndef NATIVE_H
#define NATIVE_H

#include <jni.h>
#include <GLES/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_dizuo_parking_JNI_nativeInit(JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeDestroy(JNIEnv *env, jobject thiz, jlong handle);
JNIEXPORT jlong JNICALL Java_com_dizuo_parking_JNI_nativeTestCallback(JNIEnv* env, jobject thiz, jlong handle);
JNIEXPORT int JNICALL Java_com_dizuo_parking_JNI_nativePrepareGLData(JNIEnv *env, jobject thiz, jstring dir, jlong handle);

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLReshape(JNIEnv *env, jobject thiz, jint width, jint height);
JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLRender(JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLTrackball(JNIEnv *env, jobject thiz, jint type, jint x, jint y);
JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLAdjustView(JNIEnv *env, jobject thiz, jfloat d_angx, jfloat d_angy, jfloat d_camz);

#ifdef __cplusplus
}
#endif


#endif
