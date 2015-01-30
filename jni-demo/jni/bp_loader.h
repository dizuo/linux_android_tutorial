#ifndef BP_LOADER_201501261144_H
#define BP_LOADER_201501261144_H

#include "renderable.h"

class BPLoader : public Renderable
{
public:
	typedef Renderable::v3_vec_t p3_vec_t;

	bool create_from_file(const char* fname);
	void render();

private:

	p3_vec_t m_triangles;

};

#endif
