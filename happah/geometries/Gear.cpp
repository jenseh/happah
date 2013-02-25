#include "happah/geometries/Gear.h"
#include "glm/gtx/rotate_vector.hpp"

Gear::Gear(std::string name) : NonDrawable(name) {}
Gear::~Gear() {}

std::vector<hpvec2>* Gear::getGearProfile(hpreal depth) {
	hpreal rotation = glm::tan(getHelixAngle()) * depth;

	std::vector<hpvec2>* toothProfile = getToothProfile();
	std::vector<hpvec2>* gearProfile = new std::vector<hpvec2>();
	int rotDirection = 1;
	uint toothCount = getToothCount();
	if (toothProfileIsInClockDirection())
		rotDirection = -1;
	for(uint i = 0; i < toothCount; ++i) {
		hpreal degreeRotation = (float) (rotDirection * (M_PI * 2.0f * i / toothCount + rotation) * 180.0f / M_PI);
		for(uint j = 0; j < toothProfile->size() - 1; ++j) {
			gearProfile->push_back(glm::rotate(toothProfile->at(j), degreeRotation));
		}
	}
	return gearProfile;
}

bool Gear::toothProfileIsInClockDirection() {
	std::vector<hpvec2>* toothProfile = getToothProfile();
	hpvec2 first = toothProfile->at(0);
	hpvec2 last = toothProfile->back();
	return (first[0] * last[1] - first[1] * last[0]) < 0;
}

TriangleMesh* Gear::toTriangleMesh() {
	std::vector<hpvec4>* vertexData = toMesh(&Gear::putTogetherAsTriangles);
	smoothTriangleMeshNormals(vertexData);
	TriangleMesh* mesh = new TriangleMesh(vertexData, concatStringNumber(m_name + " - Instance ", m_objectIdCounter++));
	mesh->setModelMatrix(m_modelMatrix);
	return mesh;
}

void Gear::putTogetherAsTriangles(const hpvec4 (&points)[4], std::vector<hpvec4> *&vertexData) {
	hpvec4 wildcard = hpvec4(1.0f); //fake normal
	//first triangle
	vertexData->push_back(points[0]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[1]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[2]);
	vertexData->push_back(wildcard);
	//second triangle
	vertexData->push_back(points[0]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[2]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[3]);
	vertexData->push_back(wildcard);
}

QuadMesh* Gear::toQuadMesh() {
	std::vector<hpvec4>* vertexData = toMesh(&Gear::putTogetherAsQuads);
	QuadMesh* mesh = new QuadMesh(*vertexData, concatStringNumber(m_name + " - Instance ", m_objectIdCounter++));
	mesh->setModelMatrix(m_modelMatrix);
	return mesh;
}

void Gear::putTogetherAsQuads(const hpvec4 (&points)[4], std::vector<hpvec4> *&vertexData) {
	hpvec4 wildcard = hpvec4(1.0f); //fake normal
	vertexData->push_back(points[0]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[1]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[2]);
	vertexData->push_back(wildcard);
	vertexData->push_back(points[3]);
	vertexData->push_back(wildcard);
}

std::vector<hpvec4>* Gear::toMesh(void (Gear::*putTogetherAs)(const hpvec4(&)[4], std::vector<hpvec4>*&)) {
	// Create vector for the result
	std::vector<hpvec4> *vertexData = new std::vector<hpvec4>;
	std::vector<hpvec2> *profileA, *profileB;

	hpreal dz = getFacewidth() / WIDTH_SAMPLE_SIZE;

	for (uint i = 0; i < WIDTH_SAMPLE_SIZE; ++i) {
		profileA = getGearProfile(i * dz);
		profileB = getGearProfile((i + 1) * dz);
		for (uint j = 0; j < profileA->size(); ++j) {
			//TODO: why can't I use points[0].xy = ... ?
			uint jNext = (j == profileA->size() - 1) ? 0 : (j + 1);
			hpvec4 points[4];
			points[0].x = profileA->at(jNext).x;
			points[0].y = profileA->at(jNext).y;
			points[0].z = i * dz;
			points[0].w = 1.0f;
			points[1].x = profileA->at(j).x;
			points[1].y = profileA->at(j).y;
			points[1].z = i * dz;
			points[1].w = 1.0f;
			points[2].x = profileB->at(j).x;
			points[2].y = profileB->at(j).y;
			points[2].z = (i + 1) * dz;
			points[2].w = 1.0f;
			points[3].x = profileB->at(jNext).x;
			points[3].y = profileB->at(jNext).y;
			points[3].z = (i + 1) * dz;
			points[3].w = 1.0f;
			
			(this->*putTogetherAs)(points, vertexData);
		}
		delete profileA; //memory is freed as toothProfile isn't needed any longer
		delete profileB;
	}
	return vertexData;
}

void Gear::smoothTriangleMeshNormals(std::vector<hpvec4> *&vertexData) {
	//12 entries per knot of the profile in a triangleMesh (2 * 3 points, each with a normal)
	uint pointsInRow = vertexData->size() / WIDTH_SAMPLE_SIZE;
	uint quadsInRow  = pointsInRow / 12;
	//array steps is necessary to walk in the vertexData array to the right places
	int steps[] = {0, 6, 8, -(pointsInRow - 6), -4, -6};

	// go one step further in width direction to reach all points
	for(uint i = 0; i <= WIDTH_SAMPLE_SIZE; ++i) {
		for (uint j = 0; j < quadsInRow; ++j) {
			//calculate not normalized normals of the 6
			//surrounding triangles and sum their area
			//for every point of the gear profile
			hpvec3 normal = hpvec3(0.0f);
			int n = i * pointsInRow + j * 12;
			for (uint k = 0; k < 6; ++k) {
				int da, db; //distances in vertexData array to other two triangle points
				if(k < 2) {
					da = 4; db = 2;
				} else if (k < 4) {
					da = -2; db = 2;
				} else {
					da = -2; db = -4;
				}

				//TODO: n ist int und wird mit uint verglichen! => static_cast???
				n += steps[k];
				if (k == 2 && j == quadsInRow - 1)
					n-= pointsInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < vertexData->size()) {
					hpvec4 a = vertexData->at(n + da) - vertexData->at(n);
					hpvec4 b = vertexData->at(n + db) - vertexData->at(n);
					normal = normal + (hpvec3(glm::cross(hpvec3(a.x, a.y, a.z), hpvec3(b.x, b.y, b.z))));
				}
			}
			n = i * pointsInRow + j * 12;
			for (uint k = 0; k < 6; ++k) {
				n += steps[k];
				if (k == 2 && j == quadsInRow - 1)
					n-= pointsInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < vertexData->size())
					vertexData->at(n + 1) = hpvec4(glm::normalize(normal), 0.0f); //insert the normal in the cell after the vertex
			}
		}
	}
}
