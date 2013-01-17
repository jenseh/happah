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
    SpurGear(hpreal radius = 1.0f, hpreal length = 0.2f, int toothCount = 10, int segmentCount = 40, int zDetailLevel = 40);
    ~SpurGear();

    hpreal getRadius();
    glm::vec3 getCenter();
    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();
    CircleCloud* toCircleCloud();
    ZCircleCloud* toZCircleCloud();
//    ZCircleCloud* toZCircleCloudNEW();
private:
    hpreal m_radius;
    hpreal m_length;
    int m_toothCount;
    int m_segmentCount;
    int m_zDetailLevel;
    hpreal m_heightFactor;
    hpreal m_module;
    std::vector<glm::vec2> m_heightProfilePartition;
    std::vector<glm::vec2> m_heightProfile;
    StandardProfile* m_standardProfile;

    const static float INNER_RADIUS_FACTOR = 0.5f;

    void createSinePartition();
    void createApproximatedPartition();
    void createHeightProfilePartition();
    void createHeightProfile();
};

#endif /* GEAR_H_ */
