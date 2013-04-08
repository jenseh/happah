#include "happah/geometries/Gear.h"
#include "glm/gtx/rotate_vector.hpp"
#include <iostream>

Gear::Gear() : Geometry() {}
Gear::~Gear() {}

std::vector<hpvec2>* Gear::getGearProfile(hpreal depth) {
	hpreal rotation = glm::tan(getHelixAngle()) * depth;

	std::vector<hpvec2>* toothProfile = getToothProfile();
	std::vector<hpvec2>* gearProfile = new std::vector<hpvec2>();
	int rotDirection = 1;
	hpuint toothCount = getToothCount();
	if (toothProfileIsInClockDirection())
		rotDirection = -1;
	for(hpuint i = 0; i < toothCount; ++i) {
		hpreal degreeRotation = (float) (rotDirection * (M_PI * 2.0f * i / toothCount + rotation) * 180.0f / M_PI);
		for(hpuint j = 0; j < toothProfile->size() - 1; ++j) {
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

LineMesh* Gear::toLineMesh() {
	vector<Ray>* rays = toTriangleMesh()->toRays();
	vector<hpvec3>* vertexData = new vector<hpvec3>;
	vector<uint>* indices = new vector<uint>;
	vertexData->reserve(rays->size()*2);
	indices->reserve(rays->size());
	for( vector<Ray>::iterator it = rays->begin(); it != rays->end(); ++it) {
		indices->push_back(vertexData->size()/2);
		vertexData->push_back(it->getOrigin());
		vertexData->push_back(it->getOrigin());
		it->moveOrigin(0.05);
		indices->push_back(vertexData->size()/2);
		vertexData->push_back(it->getOrigin());
		vertexData->push_back(it->getOrigin());
	}
	delete rays;
	return new LineMesh(vertexData, indices);
}

TriangleMesh* Gear::toTriangleMesh() {
	// Create vector for the result
	std::vector<hpvec3>* vertexData = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;
	std::vector<hpvec2>* profile;
	hpvec3 wildcardNormal = hpvec3(0.0f, 0.0f, 0.0f);

	hpreal dz = getFacewidth() / WIDTH_SAMPLE_SIZE;

	for (hpuint i = 0; i <= WIDTH_SAMPLE_SIZE; ++i) {
		profile = getGearProfile(i * dz);
		for (hpuint j = 0; j < profile->size(); ++j) {
			vertexData->push_back(hpvec3(profile->at(j).x, profile->at(j).y, i * dz));
			vertexData->push_back(wildcardNormal);

			if(i != WIDTH_SAMPLE_SIZE) {
				hpuint jNext = (j == profile->size() - 1) ? 0 : (j + 1);

				indices->push_back(i * profile->size() + jNext);		//0
				indices->push_back(i * profile->size() + j);			//1
				indices->push_back((i + 1) * profile->size() + j);	//2
				
				indices->push_back(i * profile->size() + jNext);		//0
				indices->push_back((i + 1) * profile->size() + j);	//2
				indices->push_back((i + 1) * profile->size() + jNext);//3
			}
		}
		delete profile;
	}

	//insert correct smoothed normals:

	//6 entries per two triangles in indices
	hpuint indicesInRow = indices->size() / WIDTH_SAMPLE_SIZE;
	hpuint trianglePairsInRow  = indicesInRow / 6;

	//array steps is necessary to walk in the vertexData array to the right places
	int steps[] = {0, 3, 4, -(indicesInRow - 3), -2, -3};

	// go one step further in width direction to reach all points
	for(hpuint i = 0; i <= WIDTH_SAMPLE_SIZE; ++i) {
		for (hpuint j = 0; j < trianglePairsInRow; ++j) {
			//calculate not normalized normals of the 6
			//surrounding triangles and sum their area
			//for every point of the gear profile
			hpvec3 normal = hpvec3(0.0f);
			int n = i * indicesInRow + j * 6;
			for (hpuint k = 0; k < 6; ++k) {
				int da, db; //distances in vertexData array to other two triangle points
				if(k < 2) {
					da = 2; db = 1;
				} else if (k < 4) {
					da = -1; db = 1;
				} else {
					da = -1; db = -2;
				}

				//TODO: n ist int und wird mit hpuint verglichen! => static_cast???
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
			// TODO Something is still worng with the normals
			n = i * indicesInRow + j * 6;
			for (hpuint k = 0; k < 6; ++k) {
				n += steps[k];
				if (k == 2 && j == trianglePairsInRow - 1)
					n -= indicesInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < indices->size())
					vertexData->at(2 * indices->at(n) + 1) = -glm::normalize(normal); //insert the normal in the cell after the vertex
			}
		}
	}

	return new TriangleMesh(vertexData, indices);
}
