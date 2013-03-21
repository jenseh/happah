#include "happah/geometries/Disc.h"


// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
Disc::Disc(): Geometry(){

}

Disc::~Disc() {
}



TriangleMesh* Disc::toTriangleMesh(){
	// This creates the quads for a gear. The gear axis is the model's z-axis.
	std::vector<hpvec3> *vertexData = new std::vector<hpvec3>;
	std::vector<hpuint> *indices = new std::vector<hpuint>;
	hpvec3 wildcardNormal = hpvec3(0.0f, 0.0f, 0.0f);

	float dalpha = 2 * M_PI / ANGLE_DETAIL_LEVEL;

	// Create the height profile given the current disc settings
	createHeightProfile();

	vertexData->reserve(ANGLE_DETAIL_LEVEL * m_heightProfile.size() *2);
	for (int i = 0; i <= ANGLE_DETAIL_LEVEL; i++) {
		for (unsigned int j = 0; j < m_heightProfile.size();j++) {
			vertexData->push_back(hpvec3(m_heightProfile[j].x,
										sin(i * dalpha) * m_heightProfile[j].y,
										cos(i * dalpha) * m_heightProfile[j].y));
			vertexData->push_back(wildcardNormal);

			if(i != ANGLE_DETAIL_LEVEL) {
				hpuint jNext = (j == m_heightProfile.size() - 1) ? 0 : (j + 1);

				indices->push_back(i * m_heightProfile.size() + jNext);		//0
				indices->push_back(i * m_heightProfile.size() + j);			//1
				indices->push_back((i + 1) * m_heightProfile.size() + j);	//2

				indices->push_back(i * m_heightProfile.size() + jNext);		//0
				indices->push_back((i + 1) * m_heightProfile.size() + j);	//2
				indices->push_back((i + 1) * m_heightProfile.size() + jNext);//3
			}
		}
	}

	//insert correct smoothed normals:

	//6 entries per two triangles in indices
	uint indicesInRow = indices->size() / ANGLE_DETAIL_LEVEL;
	uint trianglePairsInRow  = indicesInRow / 6;

	//array steps is necessary to walk in the vertexData array to the right places
	int steps[] = {0, 3, 4, -(indicesInRow - 3), -2, -3};

	// go one step further in width direction to reach all points
	for(uint i = 0; i <= ANGLE_DETAIL_LEVEL; ++i) {
		for (uint j = 0; j < trianglePairsInRow; ++j) {
			//calculate not normalized normals of the 6
			//surrounding triangles and sum their area
			//for every point of the gear profile
			hpvec3 normal = hpvec3(0.0f);
			int n = i * indicesInRow + j * 6;
			for (uint k = 0; k < 6; ++k) {
				int da, db; //distances in vertexData array to other two triangle points
				if(k < 2) {
					da = 2; db = 1;
				} else if (k < 4) {
					da = -1; db = 1;
				} else {
					da = -1; db = -2;
				}
				n += steps[k];
				if (k == 2 && j == trianglePairsInRow - 1)
					n -= indicesInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < indices->size()) {
					hpvec3 a = vertexData->at(2 * indices->at(n + da)) - vertexData->at(2 * indices->at(n));
					hpvec3 b = vertexData->at(2 * indices->at(n + db)) - vertexData->at(2 * indices->at(n));
					normal = normal + (hpvec3(glm::cross(a, b)));
				}
			}
			n = i * indicesInRow + j * 6;
			for (uint k = 0; k < 6; ++k) {
				n += steps[k];
				if (k == 2 && j == trianglePairsInRow - 1)
					n -= indicesInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < indices->size())
					vertexData->at(2 * indices->at(n) + 1) = glm::normalize(normal); //insert the normal in the cell after the vertex
			}
		}
	}
	return new TriangleMesh(vertexData, indices);
}



