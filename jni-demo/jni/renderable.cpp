#include "renderable.h"
#include <math.h>

Renderable::Renderable() : init_(false), dirty_(false)
{
	minp_.x = minp_.y = 999999;
	maxp_.x = maxp_.y = 0;
}

Renderable::~Renderable()
{}

bool Renderable::create_from_file(const char* fname)
{
	if ( init() ) { return true; }
	
	// do nothing...

	return false;
}

void Renderable::render() { }

void Renderable::update_bbox(const vec3f_t& pnt)
{
	if (minp_.x > pnt.x) { minp_.x = pnt.x; }
	if (minp_.y > pnt.y) { minp_.y = pnt.y; }

	if (maxp_.x < pnt.x) { maxp_.x = pnt.x; }
	if (maxp_.y < pnt.y) { maxp_.y = pnt.y; }
}

#define GET_MAX_A(a, b) if ((a) > (b)) { (b) = (a); }

void Renderable::update_bbox(const vec2f_t& pnt)
{
	vec3f_t v3;
	v3.z = 0; v3.x = pnt.x; v3.y = pnt.y;
	this->update_bbox(v3);
}

float Renderable::get_cameraz(float fovy)
{
	float max_aspect = 0;

	GET_MAX_A(abs(maxp_.x), max_aspect);
	GET_MAX_A(abs(maxp_.y), max_aspect);
	GET_MAX_A(abs(minp_.x), max_aspect);
	GET_MAX_A(abs(minp_.y), max_aspect);

#ifndef PI
#define PI 3.14159265f
#endif

	__android_log_print(ANDROID_LOG_INFO, "dizuo", "%f,%f,%f,%f, %f,%f", minp_.x, minp_.y, maxp_.x, maxp_.y,
			max_aspect, fovy);

	return max_aspect / tan( fovy * PI / 180.0f );
}
