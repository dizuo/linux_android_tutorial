#ifndef GL_WORLD_201501231436_H
#define GL_WORLD_201501231436_H

class GLWorld
{
public:

	GLWorld();
	~GLWorld();

	void gl_init(const char* data_dir);

	void gl_reshape(int width, int height);

	void gl_render();
	
	void gl_destroy();

	void gl_adjust_view(float d_angx, float d_angy, float d_camez);

private:

	float m_anglex;
	float m_angley;
	float m_cameraz;
	float m_fovy;

private:

};

#endif
