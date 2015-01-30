#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#include "gl_world.h"
#include "native.h"

int global_var = 5;

#ifndef NULL
#define NULL (0)
#endif

/*
 * callback的jni上下文
 */
typedef struct _cbcontext {
	JavaVM *jvm; // java虚拟机
	jobject thiz; // jni对象
} CBContext;

/*
 * 引擎的运行上下文
 */
typedef struct _context {
	void *handle;
	CBContext cbContext;
} Context;

static JNIEnv *getEnv(CBContext *context) {
	JavaVM *jvm = context->jvm;
	JNIEnv *env;
	int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);

	switch (status) {
	case JNI_OK:
		return env;
	case JNI_EDETACHED:
		status = jvm->AttachCurrentThread(&env, NULL);
		if (status < 0) {
			return NULL;
		} else {
			return env;
		}
	default:
		return NULL;
	}
}

/*
 * unicode chars 2 jstring
 */
static jstring getJString(JNIEnv *env, unsigned short *cstr, int strLen) {
	if (cstr == NULL || strLen == 0) {
		return NULL;
	}

	return (jstring) env->NewString((const jchar*) cstr, strLen);
}

//char* to jstring
//NOTICE: you need free return value,like  (*env)->DeleteLocalRef( env, myObj );
static jstring charToJstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("java/lang/String");

	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");

	jbyteArray bytes = env->NewByteArray(strlen(pat));

	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);

	jstring encoding = env->NewStringUTF("utf-8");
	jstring result= (jstring) env->NewObject(strClass, ctorID, bytes, encoding);

	env->DeleteLocalRef(bytes);
	env->DeleteLocalRef(encoding);

	return result;
}

static jobject callback(void* context, int what, int arg1, jstring arg2)
{
	CBContext* pContext = (CBContext*)context;

	JNIEnv *env = getEnv(pContext);
	jobject obj = pContext->thiz;

	jclass cls = env->GetObjectClass(obj);
	jmethodID javaCallback = env->GetMethodID(cls, "callback", "(IILjava/lang/String;)Ljava/lang/Object;");

	jobject ret = env->CallObjectMethod(obj, javaCallback, what, arg1, arg2);

	if (arg2 != NULL)
	{
		env->DeleteLocalRef(arg2);
	}

	return ret;
}

static void glDrawTextCallback(text_bmp_t* textBitmap, const char* text, int fontSize, void* context)
{
	CBContext *pContext = (CBContext *) context;
	JNIEnv *env = getEnv(pContext);
	if (env == NULL)
	{
		__android_log_print(ANDROID_LOG_INFO, NTAG, "empty environment");
		return;
	}

	jstring jtext = charToJstring(env, text);

	if (jtext == NULL)
	{
		__android_log_print(ANDROID_LOG_INFO, NTAG, "empty string [%s]", text);
		return;
	}

	int type = 0;
	jobject bitmap = callback(context, type, fontSize, jtext);
	if (bitmap == NULL)
	{
		return;
	}

	AndroidBitmapInfo info;
	int r = AndroidBitmap_getInfo(env, bitmap, &info);
	if (r < 0)
	{
		return;
	}

	int width = info.width;
	int height = info.height;

	if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888
	// if (info.format != ANDROID_BITMAP_FORMAT_A_8
			|| width <= 0
			|| height <= 0)
	{
		__android_log_print(ANDROID_LOG_INFO, NTAG, "error format [%d, %d, %d]", info.format, width, height);

		return;
	}

	textBitmap->format = BITMAP_FORMAT_RGBA;
	textBitmap->width = width;
	textBitmap->height = height;
	textBitmap->buffer = (unsigned char*)malloc(width * height * 4);

	void *pixels;
	r = AndroidBitmap_lockPixels(env, bitmap, &pixels);
	if (r < 0)
	{
		return;
	}

	int colorLen = width * height * 4;
	char *colors = (char *) pixels;

	for (int index = 0; index < colorLen; index++)
	{
		textBitmap->buffer[index] = (unsigned char) (colors[index]);
	}

	// Cannot delete. OtherWise JNI ERROR: accessed deleted local reference.
	// if (jtext) env->DeleteLocalRef(jtext);

	AndroidBitmap_unlockPixels(env, bitmap);
}

GLWorld gl_world;

JNIEXPORT jlong JNICALL Java_com_dizuo_parking_JNI_nativeInit(JNIEnv *env, jobject thiz)
{
	int* engine_handle = &global_var;

	Context* context = new Context();
	context->handle = engine_handle;

	JavaVM *pjvm;
	env->GetJavaVM(&pjvm);
	context->cbContext.jvm = pjvm;
	context->cbContext.thiz = env->NewGlobalRef(thiz);

	gl_world.set_callback(glDrawTextCallback, &context->cbContext);

	return (jlong)context;
}

JNIEXPORT jlong JNICALL Java_com_dizuo_parking_JNI_nativeTestCallback(JNIEnv* env, jobject thiz, jlong handle)
{
	int ret = 0;
	Context* context = (Context*)handle;

/*	unsigned short nameBuf[] = {35140, 38451, 24066};

	jstring jname = getJString(env, nameBuf, sizeof(nameBuf) / sizeof(nameBuf[0]));
	int type = 1;
	int arg = 888;
	jobject ret = callback(&context->cbContext, type, arg, jname);

	// python2.7.8 us = u'我叫任亚飞' print(us)
	unsigned short nameBuf1[] = {0x6211, 0x53eb, 0x4efb, 0x4e9a, 0x98de};
	jname = getJString(env, nameBuf1, sizeof(nameBuf1) / sizeof(nameBuf1[0]));
	type = 0;
	arg = 111;
	ret = callback(&context->cbContext, type, arg, jname);
*/

	// char buffer[] = "dizuo";
	// text_bmp_t textBitmap;
	// glDrawTextCallback(&textBitmap, buffer, 14, &context->cbContext);

	return (jlong)ret;
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeDestroy(JNIEnv *env, jobject thiz, jlong handle)
{
	Context *context = (Context *) handle;

	env->DeleteGlobalRef(context->cbContext.thiz);

	delete context;
}

JNIEXPORT int JNICALL Java_com_dizuo_parking_JNI_nativePrepareGLData(JNIEnv *env, jobject thiz, jstring dir, jlong handle)
{
	Context* context = (Context*)handle;

	const char* c_data_dir = env->GetStringUTFChars(dir, NULL);

	int ret = gl_world.gl_load_data(c_data_dir);

	if (dir)
	{
		env->ReleaseStringUTFChars(dir, c_data_dir);
	}

	return ret;
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLDestroy(JNIEnv *env, jobject thiz)
{
	gl_world.gl_destroy();
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLInit(JNIEnv *env, jobject thiz)
{
	gl_world.gl_init();
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLReshape(JNIEnv *env, jobject thiz, jint width, jint height)
{
	gl_world.gl_reshape(width, height);
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLRender(JNIEnv *env, jobject thiz)
{
	gl_world.gl_render();
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLTrackball(JNIEnv *env, jobject thiz, jint type, jint x, jint y)
{
	if (type == 0)
	{
		gl_world.gl_begin_track(x, y);
	}
	else if (type == 1)
	{
		gl_world.gl_tracking(x, y);
	}
}

JNIEXPORT void JNICALL Java_com_dizuo_parking_JNI_nativeGLAdjustView(JNIEnv *env, jobject thiz, jfloat d_angx, jfloat d_angy, jfloat d_camz)
{
	gl_world.gl_adjust_view(d_angx, d_angy, d_camz);
}
