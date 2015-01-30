#include "gl_world.h"

#if defined(ES_ANDROID) || defined(__APPLE__)
#include <GLES/gl.h>
#include <android/log.h>

/**
 * gluPerspective的实现（GLES不支持）。
 */
static void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
	GLfloat xmin, xmax, ymin, ymax;
	ymax = zNear * (GLfloat) tan(fovy * M_PI / 360);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustumx((GLfixed) (xmin * 65536), (GLfixed) (xmax * 65536),
			(GLfixed) (ymin * 65536), (GLfixed) (ymax * 65536),
			(GLfixed) (zNear * 65536), (GLfixed) (zFar * 65536));
}
double max(double a, double b)
{
	return a > b ? a : b;
}
double min(double a, double b)
{
	return a < b ? a : b;
}
#endif

GLWorld::GLWorld() 
: m_cameraz(-10.0f), m_fovy(60.0f)
, m_arcball(0, 0)
, m_park(NULL), width_(0), height_(0)
{
	m_park = new UnderPark();

	pthread_mutex_init(&dataMutex, NULL);
	//pthread_mutex_init(&eventMutex, NULL);
}

GLWorld::~GLWorld()
{
	pthread_mutex_destroy(&dataMutex);
	//pthread_mutex_destroy(&eventMutex);
}

int GLWorld::gl_load_data(const char* root_dir)
{
	// TODO 跨线程问题么？？？为何此处为m_fovy为0.
	__android_log_print(ANDROID_LOG_INFO, "dizuo", "load_data, fovy = %f", m_fovy);

	if (m_park == NULL)
	{
		return SYS_ERROR;
	}

	m_fovy = 60.0f;

	pthread_mutex_lock(&dataMutex);
	int ret = m_park->load_data(root_dir);
	m_cameraz = -m_park->get_cameraz(m_fovy*0.5f);
	pthread_mutex_unlock(&dataMutex);

	__android_log_print(ANDROID_LOG_INFO, "dizuo", "cameraz = %f", m_cameraz);

	return ret;
}

void GLWorld::gl_init()
{
	// glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	__android_log_print(ANDROID_LOG_INFO, NTAG, "init");
}

void GLWorld::gl_reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fovy, (float)width / (float)height, 0.001, 1000.0);

	width_ = width;
	height_ = height;

	// pthread_mutex_lock(&eventMutex);
	m_arcball.SetWnd(width, height);
	// pthread_mutex_unlock(&eventMutex);

	__android_log_print(ANDROID_LOG_INFO, NTAG, "reshape");
}

void GLWorld::gl_render()
{
	glClearDepthf(0.0f);
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, m_cameraz);	// set camera position.
	
	//pthread_mutex_lock(&eventMutex);
	m_arcball.toOpenGL();
	//pthread_mutex_unlock(&eventMutex);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	
	pthread_mutex_lock(&dataMutex);
	m_park->render();
	pthread_mutex_unlock(&dataMutex);

	int old_width = 0;
	glGetIntegerv(GL_LINE_WIDTH, &old_width);
	glLineWidth(2.0f);
	glLineWidth(old_width);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

#define RENDER_POI

#ifdef RENDER_POI
	// Use screenPos to render 2d dynamic label.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();		// save projection matrix.
		glLoadIdentity();
		glOrthof(0, width_, 0, height_, 0, 1);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();		// save modelview matrix.
		glLoadIdentity();

		glPushMatrix();
		{
			m_park->render_2d_poi();
		} glPopMatrix();

		glPopMatrix();		// restore modelview matrix.

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();		// restore projection matrix.
#endif

	int error = glGetError();
	__android_log_print(ANDROID_LOG_INFO, NTAG, "error = %d", error);

}

void GLWorld::_render_board()
{
	float vertices[] = {-5,5, 5,5, 5,-5, -5,-5};
	unsigned short indices[] = {0,2,1, 2,0,3};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWorld::gl_destroy()
{
	if (m_park)
	{
		m_park->gl_destroy();
	}
}

void GLWorld::gl_begin_track(int x, int y)
{
	__android_log_print(ANDROID_LOG_INFO, "dizuo", "begin track...");
	//pthread_mutex_lock(&eventMutex);
	m_arcball.BeginTracking(x, y);
	//pthread_mutex_unlock(&eventMutex);
}

void GLWorld::gl_tracking(int x, int y)
{
	__android_log_print(ANDROID_LOG_INFO, "dizuo", "tracking...");
	//pthread_mutex_lock(&eventMutex);
	m_arcball.Tracking(x, y);
	//pthread_mutex_unlock(&eventMutex);
}

void GLWorld::gl_adjust_view(float d_angx, float d_angy, float d_camez)
{
	m_cameraz += d_camez;
}
