#include "under_park.h"

UnderPark::UnderPark()
{}

UnderPark::~UnderPark()
{}

void UnderPark::render()
{
	// m_track1.render();
	m_bp.render();

}

float UnderPark::get_cameraz(float fovy)
{
	float a1 = m_bp.get_cameraz(fovy);
	return a1;
}

int UnderPark::load_data(const char* data_dir)
{
/*	strncpy(data_dir_, data_dir, 1024);
	char fname[1024];
	strcpy(fname, data_dir);
	strcat(fname, "/down11.asc");
	if (!m_track1.from_file(fname))
	{
		printf("Failed to load track[ %s ]\n", fname);
	}
*/

	strncpy(data_dir_, data_dir, 1024);
	char fname[1024];
	strcpy(fname, data_dir);
	strcat(fname, "/bp.asc");

	if (m_bp.create_from_file(fname))
	{
		return SYS_OK;
	}

	return SYS_ERROR;
}

