#ifndef UNDER_PARK_201501231118_H
#define UNDER_PARK_201501231118_H

// #include "line_loader.h"
#include "bp_loader.h"

class UnderPark
{
public:

	UnderPark();
	~UnderPark();

	int load_data(const char* data_dir);

	void render();

	float get_cameraz(float fovy);
	
	// LineLoader m_track1;
	BPLoader m_bp;
	
private:

	char data_dir_[1024];
};

#endif
