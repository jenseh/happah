#pragma once

#include <memory>
#include <vector>

#include "happah/HappahTypes.h"

using namespace std;

class Mesh {
public:
	Mesh(vector<hpvec2>* verticesAndNormals, vector<hpuint>* indices);
	Mesh(vector<hpvec3>* verticesAndNormals, vector<hpuint>* indices);
	virtual ~Mesh();


	vector<hpvec3>* getVerticesAndNormals();
	vector<hpuint>* getIndices();

private:
	vector<hpvec3>* m_verticesAndNormals;
	vector<hpuint>* m_indices;
};
typedef shared_ptr<Mesh> Mesh_ptr;

