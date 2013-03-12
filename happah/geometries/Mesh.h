#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "happah/HappahTypes.h"
using namespace std;

class Mesh {
public:
	Mesh(vector<hpvec3>* vertexData, vector<hpuint>* indices);
	virtual ~Mesh();

	   vector<hpvec3>* getVertexData();
	   vector<hpuint>* getIndices();

	private:
	    vector<hpvec3>* m_vertexData;
	    vector<hpuint>* m_indices;
};
typedef shared_ptr<Mesh> Mesh_ptr;

class TriangleMesh : public Mesh {
public:
    TriangleMesh(vector<hpvec3>* vertexData, vector<hpuint>* indices);
    ~TriangleMesh();
};
typedef shared_ptr<TriangleMesh> TriangleMesh_ptr;

class LineMesh : public Mesh {
public:
    LineMesh(vector<hpvec3>* vertexData, vector<hpuint>* indices);
    ~LineMesh();
};
typedef shared_ptr<LineMesh> LineMesh_ptr;


#endif /* MESH_H_ */
