#ifndef GEAR_H
#define GEAR_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "QglGeometryObject.h"
#include "../../StandardProfile.h"

class QglGear: public QglGeometryObject {
public:
    QglGear(float radius = 1.0f, float length = 0.2f, int toothCount = 10);

	virtual ~QglGear();
	float getRadius();
	glm::vec3 getCenter();
	void createVertexData();
	QRectF boundingRect() const; // DO NOT CHANGE INTO getBoundingRect as bounding Rectangle implements a virtual function of component.
private:
	float radius_;
	float length_;
	int toothCount_;
	float heightFactor_;
	float module_;
	std::vector<glm::vec2> heightProfilePartition_;
	std::vector<glm::vec2> heightProfile_;
	StandardProfile* standardProfile;

	const static int SEGMENT_COUNT = 40; //maximum: 4500
	const static int Z_DETAIL_LEVEL = 4;
	const static float INNER_RADIUS_FACTOR = 0.5f;

	void createSinePartition();
	void createApproximatedPartition();
	void createHeightProfilePartition();
	void createHeightProfile();
};

#endif // GEAR_H
