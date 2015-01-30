#ifndef BP_LOADER_201501261144_H
#define BP_LOADER_201501261144_H

#include "renderable.h"

typedef struct sPOI
{
	char name[100];
	vec2f_t pos;
} poi_t;

class BPLoader : public Renderable
{
public:
	
	typedef std::vector< poi_t > poi_vec_t;

	typedef Renderable::v3_vec_t p3_vec_t;

	bool create_from_file(const char* fname);
	void render();

	bool load_poi_file(const char* fname);
	int transform_poi_to_renderable();

private:

	p3_vec_t m_triangles;
	
	poi_vec_t m_poivec;

};

#endif