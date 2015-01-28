#ifndef RENDERABLE_201501281220_H
#define RENDERABLE_201501281220_H

#include "common.h"
#include <vector>

class Renderable
{
public:
	
	typedef std::vector< vec3f_t > v3_vec_t;
	typedef std::vector< vec2f_t > v2_vec_t;

	Renderable();
	virtual ~Renderable();

	virtual bool create_from_file(const char* fname);
	virtual void render();

	void set_dirty(bool f) { dirty_ = f; }
	bool dirty() const { return dirty_; }

	void set_init(bool i) { init_ = i; }
	bool init() const { return init_; }

	float get_cameraz(float fovy);

protected:

	void update_bbox(const vec2f_t& pnt);
	void update_bbox(const vec3f_t& pnt);

private:

	bool dirty_;
	bool init_;

	vec2f_t maxp_;
	vec2f_t minp_;

};

#endif