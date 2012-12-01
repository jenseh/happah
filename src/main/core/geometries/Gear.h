/*
 * Gear.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef GEAR_H_
#define GEAR_H_

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "GeometryObject.h"
#include "StandardProfile.h"

using namespace std;


class Gear: public GeometryObject {
public:
    Gear(float radius = 1.0f, float length = 0.2f, int toothCount = 10);

    virtual ~Gear();
    float getRadius();
    glm::vec3 getCenter();
    void createVertexData();
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

#endif /* GEAR_H_ */
