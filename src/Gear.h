#ifndef GEAR_H
#define GEAR_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "GeometryObject.h"

class Gear: public GeometryObject {
public:
    Gear(float radius = 1.0f, float length = 0.2f, int toothCount = 10,
            float heightFactor = 0.2f, QMatrix4x4* projectionMatrix = 0,
            QMatrix4x4* viewMatrix = 0, QVector3D* camPos = 0);
	virtual ~Gear();
	float getRadius();
	glm::vec3 getCenter();
	void createVertexData();
private:
    float radius_;
    float length_;
    int toothCount_;
    float heightFactor_;
    std::vector<glm::vec2> heightProfilePartition_;
    std::vector<glm::vec2> heightProfile_;

	const static int SEGMENT_COUNT = 40; //maximum: 4500
	const static int Z_DETAIL_LEVEL = 4;
	const static float INNER_RADIUS_FACTOR = 0.5f;

	void createSinePartition();
	void createApproximatedPartition();
	void createHeightProfilePartition();
	void createHeightProfile();
};

#endif // GEAR_H
