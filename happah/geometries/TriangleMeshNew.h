#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <glm/glm.hpp>
#include <vector>

#include "happah/geometries/Drawable.h"
#include "happah/HappahTypes.h"

class TriangleMesh : public Drawable {
public:

	TriangleMesh(std::vector<hpvec3>* vertexData, std::string name);
	TriangleMesh(std::vector<hpvec3>* vertices, std::vector<hpvec3>*normals,
				 std::vector<hpuint>* indices, std::string name);
	~TriangleMesh();


	std::vector<hpvec3>* getVertices();
	std::vector<hpvec3>* getNormals();
	std::vector<hpuint>* getIndices();

	//   RayCloud* toRayCloud();

private:
	std::vector<hpvec3>* m_vertices;
	std::vector<hpvec3>* m_normals;
	std::vector<hpuint>* m_indices;

};

#endif // TRIANGLEMESH_H
