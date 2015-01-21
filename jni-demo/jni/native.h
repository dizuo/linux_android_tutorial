#ifndef NATIVE_H
#define NATIVE_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_dizuo_jnidemo_JNI_nativeInit(JNIEnv *env, jobject thiz);

JNIEXPORT jlong JNICALL Java_com_dizuo_jnidemo_JNI_nativeTestCallback(JNIEnv* env, jobject thiz, jlong handle);


#ifdef __cplusplus
}
#endif


#endif
