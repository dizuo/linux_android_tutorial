#ifndef COMMON_201501231122_H
#define COMMON_201501231122_H

#ifdef WIN32
	#include <gl/glut.h>
#elif defined(ES_ANDROID) || defined(__APPLE__)
	#include <GLES/gl.h>
	#include <android/log.h>
	#include <math.h>
#endif

typedef struct sVec2f
{
	float x;
	float y;
} vec2f_t;

typedef struct sVec3f
{
	float x;
	float y;
	float z;
} vec3f_t;

enum {
	BITMAP_FORMAT_RGBA = 0,
	BITMAP_FORMAT_RGB565,
	BITMAP_FORMAT_ALPHA
};

typedef struct _textBitmap {
	unsigned char* buffer;
	int width;
	int height;
	int format;
} text_bmp_t;

#define SYS_OK (0)
#define SYS_NOT_FINISH (1)
#define SYS_ERROR (-1)

#define NTAG "dizuo_nt"

#endif
