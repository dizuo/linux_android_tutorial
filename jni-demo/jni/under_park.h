#ifndef UNDER_PARK_201501231118_H
#define UNDER_PARK_201501231118_H

// #include "line_loader.h"
#include "bp_loader.h"

typedef struct LabelRenderable
{
	text_bmp_t bmp;
	vec2f_t screen_pos;
	vec2f_t tex_size;
} label_render_t;


typedef struct sPOI
{
	char name[100];
	vec2f_t pos;
} poi_t;

#define GL_THREAD

#define DATA_THREAD

class UnderPark
{
public:
	typedef std::vector< poi_t > poi_vec_t;

	typedef void (*DrawCallback)(text_bmp_t* textBitmap, const char* text, int fontSize, void* context);

	typedef vec2f_t (*CalcTextSizeCallback)(unsigned short *text, int count, int fontSize, void *context);

	enum
	{
		LABEL_QUE_SIZE = 5
	};

	UnderPark();
	~UnderPark();

	int DATA_THREAD load_data(const char* data_dir);

	int DATA_THREAD transform_poi_to_renderable();	// DT

	float DATA_THREAD get_cameraz(float fovy);

	void GL_THREAD render();
	
	void GL_THREAD render_2d_poi();

	void set_callback(DrawCallback draw_func, void* context) { context_ = context; draw_func_ = draw_func; }

	void gl_destroy();

	BPLoader m_bp;
	
private:

	void filter_text(float factor);

	bool load_poi_file(const char* fname);

	unsigned int texName_;

	label_render_t label_que_[LABEL_QUE_SIZE];
	int count_;

	void* context_;
	DrawCallback draw_func_;

	GLint viewport_[4];
	GLfloat mv_matrix_[16];
	GLfloat proj_matrix_[16];

	poi_vec_t poivec_;

	char data_dir_[1024];
};

#endif
