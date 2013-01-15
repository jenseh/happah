/*
 * SpurGear.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef SPURGEAR_H_
#define SPURGEAR_H_

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "../../HappahTypes.h"
#include "StandardProfile.h"
#include "NonDrawable.h"
#include "../models/QuadMesh.h"
#include "../models/CircleCloud.h"
#include "../models/ZCircleCloud.h"

using namespace std;


class SpurGear : public NonDrawable {
public:
    SpurGear(hpreal radius = 1.0f, hpreal length = 0.2f, int toothCount = 10);
    ~SpurGear();

    hpreal getRadius();
    glm::vec3 getCenter();
    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();
    CircleCloud* toCircleCloud();
    ZCircleCloud* toZCircleCloud();
private:
    hpreal radius_;
    hpreal length_;
    int toothCount_;
    hpreal heightFactor_;
    hpreal module_;
    std::vector<glm::vec2> heightProfilePartition_;
    std::vector<glm::vec2> heightProfile_;
    StandardProfile* standardProfile;

    const static int SEGMENT_COUNT = 40; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 40;
    const static float INNER_RADIUS_FACTOR = 0.5f;

    void createSinePartition();
    void createApproximatedPartition();
    void createHeightProfilePartition();
    void createHeightProfile();
};

#endif /* GEAR_H_ */
