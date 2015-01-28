#ifndef GL_WORLD_201501231436_H
#define GL_WORLD_201501231436_H

#include <pthread.h>
#include "trackball.h"

class UnderPark;

class GLWorld
{
public:

	GLWorld();
	~GLWorld();

	int gl_load_data(const char* data_dir);

	void gl_reshape(int width, int height);

	void gl_render();
	
	void gl_destroy();

	void gl_begin_track(int x, int y);

	void gl_tracking(int x, int y);

	void gl_adjust_view(float d_angx, float d_angy, float d_camez);

private:

	void _render_board();

	pthread_mutex_t dataMutex;
	pthread_mutex_t eventMutex;	// trackball.

	Trackball m_arcball;

	float m_cameraz;
	float m_fovy;

	UnderPark* m_park;

};

#endif
