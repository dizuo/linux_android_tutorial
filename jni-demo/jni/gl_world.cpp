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
{
}

GLWorld::~GLWorld()
{
}

int GLWorld::gl_load_data(const char* root_dir)
{
	int ret = 0;
	return ret;
}

void GLWorld::gl_reshape(int width, int height)
{
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fovy, (float)width / (float)height, 0.001, 1000.0);

	m_arcball.SetWnd(width, height);
}

void GLWorld::gl_render()
{
	glClearDepthf(0.0f);
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, m_cameraz);	// set camera position.

	m_arcball.toOpenGL();

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	int old_width = 0;
	glGetIntegerv(GL_LINE_WIDTH, &old_width);
	glLineWidth(2.0f);

	_render_board();

	glLineWidth(old_width);

	int err = glGetError();
	__android_log_print(ANDROID_LOG_INFO, "dizuo", "gl_render, ret = %d", err);
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
{}

void GLWorld::gl_begin_track(int x, int y)
{
	m_arcball.BeginTracking(x, y);
}

void GLWorld::gl_tracking(int x, int y)
{
	m_arcball.Tracking(x, y);
}

void GLWorld::gl_adjust_view(float d_angx, float d_angy, float d_camez)
{
	m_cameraz += d_camez;
}
