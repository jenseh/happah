#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

using namespace std;

class TriangleMesh;
typedef shared_ptr<TriangleMesh> TriangleMesh_ptr;

class TriangleMesh {
public:
    TriangleMesh(vector<hpvec3>* vertexData, vector<hpuint>* indices);
    ~TriangleMesh();

   vector<hpvec3>* getVertexData();
   vector<hpuint>* getIndices();

private:
    vector<hpvec3>* m_vertexData;
    vector<hpuint>* m_indices;

};

#endif // TRIANGLE_MESH_H
