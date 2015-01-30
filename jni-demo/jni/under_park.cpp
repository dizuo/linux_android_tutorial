#include "under_park.h"

typedef GLfloat GLdouble;

/*
Transform a point(column vector) by a 4x4 matrix. Then, out = m * in
Input: m ----- the 4x4 matrix, in ---- the 4x1 vector
Output: out ---- the resulting 4x1 vector
*/
static void transform_point(GLdouble out[4], const GLdouble m[16], const GLdouble in[4])
{
#define M(row,col) m[col*4+row]
	out[0] =
		M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * in[3];
	out[1] =
		M(1, 0) * in[0] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * in[3];
	out[2] =
		M(2, 0) * in[0] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * in[3];
	out[3] =
		M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * in[3];
#undef M
}
// gluProject source code (refer OpenGL API documents)
GLint gluProjectx(GLdouble objx, GLdouble objy, GLdouble objz, const GLdouble  modelMatrix[16], const GLdouble projMatrix[16], const GLint viewport[4], GLdouble *winx, GLdouble *winy, GLdouble *winz)
{
	// matrice transformation
	GLdouble in[4], out[4];
	//initialize matrice and column vector as a transformer
	in[0] = objx;
	in[1] = objy;
	in[2] = objz;
	in[3] = 1.0;
	transform_point(out, modelMatrix, in);
	transform_point(in, projMatrix, out);

	if (in[3] == 0.0)
		return GL_FALSE;

	in[0] /= in[3];
	in[1] /= in[3];
	in[2] /= in[3];

	*winx = viewport[0] + (1 + in[0]) * viewport[2] / 2;
	*winy = viewport[1] + (1 + in[1]) * viewport[3] / 2;
	*winz = (1 + in[2]) / 2;
	return GL_TRUE;
}

UnderPark::UnderPark()
: context_(0), draw_func_(0)
{}

UnderPark::~UnderPark()
{}

void print_matrix16(float* m)
{
	for (int i=0; i<4; i++)
		__android_log_print(ANDROID_LOG_INFO, NTAG, "%d: [%f, %f, %f, %f]", i, m[4*i+0], m[4*i+1], m[4*i+2], m[4*i+3]);
}

void UnderPark::render()
{
	//
	glGetIntegerv(GL_VIEWPORT, viewport_);
	glGetFloatv(GL_MODELVIEW_MATRIX, mv_matrix_);
	glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix_);

	//__android_log_print(ANDROID_LOG_INFO, NTAG, "viewport[%d, %d, %d, %d]", viewport_[0], viewport_[1], viewport_[2], viewport_[3]);
	// print_matrix16(mv_matrix_);

	// m_track1.render();
	m_bp.render();

}

label_render_t label;

inline unsigned int nextPOI(unsigned int x)
{
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x + 1;
}

void UnderPark::gl_destroy()
{
	if (texName_ != 0)
	{
		glDeleteTextures(1, &texName_);
		texName_ = 0;
	}
}

void UnderPark::render_2d_poi()
{
	__android_log_print(ANDROID_LOG_INFO, NTAG, "render_poi %d", poivec_.size());

	if (!context_ || !draw_func_ || poivec_.size() == 0)
	{
		return;
	}

	float mx = 0;
	float my = 0;
	float mz = 0;

	float screen_pos[3];
	gluProjectx(poivec_[0].pos.x, poivec_[0].pos.y, 0, mv_matrix_, proj_matrix_, viewport_, &screen_pos[0], &screen_pos[1], &screen_pos[2]);
	label.screen_pos.x = screen_pos[0];
	label.screen_pos.y = screen_pos[1];

	__android_log_print(ANDROID_LOG_INFO, NTAG, "(%f, %f)", screen_pos[0], screen_pos[1]);

	if (texName_ == 0)
	{
		glGenTextures(1, &texName_);

		__android_log_print(ANDROID_LOG_INFO, NTAG, "make_label");

		draw_func_(&label.bmp, poivec_[0].name, 14, context_);

		__android_log_print(ANDROID_LOG_INFO, NTAG, "label (%d, %d, %d, %s)", label.bmp.width, label.bmp.height, label.bmp.format, poivec_[0].name);

		glBindTexture(GL_TEXTURE_2D, texName_);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		int newW = nextPOI(label.bmp.width);
		int newH = nextPOI(label.bmp.height);
		// if (label.bmp.format == BITMAP_FORMAT_ALPHA)
		if (label.bmp.format == BITMAP_FORMAT_RGBA)
		{
			int type = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, type, newW, newH, 0, type, GL_UNSIGNED_BYTE, 0);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, label.bmp.width, label.bmp.height, type, GL_UNSIGNED_BYTE, label.bmp.buffer);
		}

		label.tex_size.x = (float)label.bmp.width / (float)newW;
		label.tex_size.y = (float)label.bmp.height / (float)newH;

		// __android_log_print(ANDROID_LOG_INFO, NTAG, "texName = %d, (%f,%f)", texName, label.tex_size.x, label.tex_size.y);
	}

	float fontH = label.bmp.height;
	float fontL = label.bmp.width;
	float vertices[] = {0,fontH, fontL,fontH, fontL,0, 0,0};

	float texV = label.tex_size.y;
	float texU = label.tex_size.x;
	// float texcoords[] = {0,texV, texU,texV, texU,0, 0,0};
	float texcoords[] = {0,0, texU,0, texU,texV, 0,texV};
	// unsigned short indices[] = {3,2,0, 2,1,0};

	glBindTexture(GL_TEXTURE_2D, texName_);

	glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();
	float offx = label.screen_pos.x - fontL/2;
	float offy = label.screen_pos.y - fontH/2;
	glTranslatef(offx, offy, 0.0f);

	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glPopMatrix();

	// glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	__android_log_print(ANDROID_LOG_INFO, NTAG, "render poi =>[texname = %d]", texName_);

//	glDisable(GL_BLEND);
//	glDisable(GL_TEXTURE_2D);

}

float UnderPark::get_cameraz(float fovy)
{
	float a1 = m_bp.get_cameraz(fovy);
	return a1;
}

int UnderPark::load_data(const char* data_dir)
{
	strncpy(data_dir_, data_dir, 1024);

	char fname[1024];
	strcpy(fname, data_dir_);
	strcat(fname, "/bp.asc");
	if (!m_bp.create_from_file(fname))
	{
		return SYS_ERROR;
	}

	memset(fname, 0, 1024);
	strcpy(fname, data_dir_);
	strcat(fname, "/poi.asc");
	if (!load_poi_file(fname))
	{
		return SYS_ERROR;
	}

	return SYS_OK;
}

void UnderPark::filter_text(float factor)
{
	// text size : 14 * strlen(text)*14
	int maxPixelSize = 1024;
	factor = m_bp.get_maxsize() / (float)maxPixelSize;

	// meter to pixelpos,


}

bool UnderPark::load_poi_file(const char* fname)
{
	if (poivec_.size() > 0)
	{
		return true;
	}

	FILE* fp = fopen(fname, "r");
	if (!fp)
	{
		printf("failed to open file [ %s ]\n", fname);
		return false;
	}

	const char* token = " ,\r\n";
	char buffer[1024];
	while (fgets(buffer, 1024, fp))
	{
		char* pch = strtok(buffer, token);
		poi_t item;
		memset(&item, 0, sizeof(poi_t));

		if (pch)
		{
			item.pos.x = atof(pch);
			pch = strtok(NULL, token);
			if (pch)
			{
				item.pos.y = atof(pch);
				pch = strtok(NULL, token);
				if (pch)
				{
					strcpy(item.name, pch);
				}
			}

			poivec_.push_back(item);
		}

	}
	fclose(fp);

	return true;
}

int UnderPark::transform_poi_to_renderable()
{

	return SYS_OK;
}
