#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "happah/HappahTypes.h"
#include "happah/math/Ray.h"
#include "happah/math/Triangle.h"

using namespace std;

class Mesh {
public:
	Mesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices);
	virtual ~Mesh();


	   vector<hpvec3>* getVerticesAndNormals();
	   vector<hpuint>* getIndices();

	private:
	    vector<hpvec3>* m_verticesAndNormals;
	    vector<hpuint>* m_indices;
};
typedef shared_ptr<Mesh> Mesh_ptr;

class TriangleMesh : public Mesh {
public:
    TriangleMesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices);
    ~TriangleMesh();

    hpuint getTriangleCount();
    hpuint getVertexCount();
    vector<Triangle>* toTriangles();
    vector<Ray>* toRays();
};
typedef shared_ptr<TriangleMesh> TriangleMesh_ptr;

class LineMesh : public Mesh {
public:
    LineMesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices);
    ~LineMesh();
};
typedef shared_ptr<LineMesh> LineMesh_ptr;


#endif /* MESH_H_ */
