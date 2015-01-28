#include "bp_loader.h"

#include <cmath>

#ifdef WIN32
	#include <gl/glut.h>
#endif

bool BPLoader::create_from_file(const char* fname)
{
	FILE* fp = fopen(fname, "r");
	if (!fp) { return false; }

	const char* token = ", \n";

	char buffer[1024];
	while (fgets(buffer, 1024, fp))
	{
		if (strstr(buffer, "Triangles"))
		{
			continue;
		}

		// printf("%s\n", buffer);

		char* pch = strtok(buffer, token);		

		for (int m = 0; m < 3; m++)
		{
			vec3f_t pnt;		
			pnt.x =  m==0 ? atof(pch) : atof(strtok(NULL, token));
			pnt.y = atof(strtok(NULL, token));
			pnt.z = 0;

			Renderable::update_bbox(pnt);

			m_triangles.push_back(pnt);
		}

	}

	return true;
}

void BPLoader::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &(m_triangles[0].x));
	glDrawArrays(GL_TRIANGLES, 0, m_triangles.size());

	glDisableClientState(GL_VERTEX_ARRAY);
}
