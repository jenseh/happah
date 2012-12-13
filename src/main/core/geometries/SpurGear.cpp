/*
 * SpurGear.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "SpurGear.h"

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
SpurGear::SpurGear(float radius, float length, int toothCount) :
        GeometryObject() {
    radius_ = radius;
    length_ = length;
    toothCount_ = toothCount;
    module_ = radius_ * 2.0f / toothCount_;
}

SpurGear::~SpurGear() {
}

float SpurGear::getRadius() {
    return radius_;
}

void SpurGear::createSinePartition() {
    // Use this to draw a sinus surface
    for (int i = 0; i < SEGMENT_COUNT; i++) {
        float position = (float) i / (float) SEGMENT_COUNT;
        float height = exp2f(sinf(position * 2.0f * M_PI));
        heightProfilePartition_.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
    }
}

void SpurGear::createApproximatedPartition() {
    const int segmentsPerLine = SEGMENT_COUNT / 4;

    float horizX = 0.35f; //check whether 2*horiz + 2*flankX = 1.0
    float flankX = 0.15f;

    // Use this to draw a gear with straight flanks and a quadratic bottom
    // horizontal teeth part
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        heightProfilePartition_.push_back(glm::vec2(0.0f + x * horizX, 1.0f));
    }

    // right flank
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        heightProfilePartition_.push_back(
                glm::vec2(horizX + x * flankX, 1.0f - x * 0.8f));
    }

    // lower teeth part
    // fit a quadratic function for the bottom part of a teeth hole
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        float position = horizX + flankX + x * horizX;
        float height = 0.2f * pow(2.0f * x - 1.0f, 2.0f);
        heightProfilePartition_.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
    }

    //left flank
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        heightProfilePartition_.push_back(
                glm::vec2(horizX + flankX + horizX + x * flankX,
                        0.2f + x * 0.8f));
    }
}

// Create a profile of height values for one partition (german: Teilung)
// x-values must be between 0 and p (partition, german: Teilung)
// y-values must be between -p and p (height)
void SpurGear::createHeightProfilePartition() {
    heightProfilePartition_ = std::vector<glm::vec2>();

    standardProfile = new StandardProfile(module_, 10 / 180.0 * M_PI, 0, 0);
    standardProfile->getProfilePartition(heightProfilePartition_,
            SEGMENT_COUNT);
    //createApproximatedPartition();
}

// Create a profile of height values
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void SpurGear::createHeightProfile() {
    createHeightProfilePartition();
    heightProfile_ = std::vector<glm::vec2>();

    for (int i = 0; i < toothCount_; i++) {
        for (unsigned int j = 0; j < heightProfilePartition_.size(); j++) {
            float position = heightProfilePartition_[j].x + i * module_ * M_PI;
            float height = heightProfilePartition_[j].y;
            heightProfile_.push_back(glm::vec2(position, height));
            //cout << position << ": " << height << std::endl;
        }
    }
    // Add the first element again to close the "circle"
    // TODO: Rethink whether this makes sense
    heightProfile_.push_back(heightProfile_[0]);
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
void SpurGear::createVertexData() {
    float dz = length_ / Z_DETAIL_LEVEL;
    const float toRad = M_PI / 180.0f;
    float innerRadius = radius_ * INNER_RADIUS_FACTOR;

    // Create the height profile given the current gear settings
    createHeightProfile();

    // precompute sin and cos of angles
    float cosSegment[heightProfile_.size() + 1];
    float sinSegment[heightProfile_.size() + 1];
    float height[heightProfile_.size() + 1];
    float cosHeight[heightProfile_.size() + 1];
    float sinHeight[heightProfile_.size() + 1];

    for (unsigned int segmentNum = 0; segmentNum < heightProfile_.size();
            segmentNum++) {
        float phi = heightProfile_[segmentNum].x / (2 * M_PI * radius_)
                * 360.0f; //in degrees
        cosSegment[segmentNum] = cos(phi * toRad);
        sinSegment[segmentNum] = sin(phi * toRad);
        height[segmentNum] = radius_ + heightProfile_[segmentNum].y;
        cosHeight[segmentNum] = cosSegment[segmentNum] * height[segmentNum];
        sinHeight[segmentNum] = sinSegment[segmentNum] * height[segmentNum];
    }
    // Insert first value again to close the mesh
    cosSegment[heightProfile_.size()] = cosSegment[0];
    sinSegment[heightProfile_.size()] = sinSegment[0];
    height[heightProfile_.size()] = height[0];
    cosHeight[heightProfile_.size()] = cosHeight[0];
    sinHeight[heightProfile_.size()] = sinHeight[0];

    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        float z = i * dz;
        for (unsigned int segmentNum = 0; segmentNum < heightProfile_.size();
                segmentNum++) {

            glm::vec4 a, b, c, d, normNext, norm;

            a.x = cosHeight[segmentNum + 1];
            a.y = sinHeight[segmentNum + 1];
            a.z = z;
            a.w = 1.0f;

            b.x = cosHeight[segmentNum];
            b.y = sinHeight[segmentNum];
            b.z = z;
            b.w = 1.0f;

            c.x = cosHeight[segmentNum];
            c.y = sinHeight[segmentNum];
            c.z = z + dz;
            c.w = 1.0f;

            d.x = cosHeight[segmentNum + 1];
            d.y = sinHeight[segmentNum + 1];
            d.z = z + dz;
            d.w = 1.0f;

            // compute the 2 normals (each used twice
            normNext = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(cosHeight[segmentNum + 2] - a.x,
                                            sinHeight[segmentNum + 2] - a.y,
                                            0.0f))), 1.0f);
            norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
                    1.0f);

            dataPushback(a);
            dataPushback(normNext);
            dataPushback(b);
            dataPushback(norm);
            dataPushback(c);
            dataPushback(norm);
            dataPushback(d);
            dataPushback(normNext);
        }
    }

    // draw the front and back of the gear
    // this part is very straightforward. now alle quads have the
    // circle's center as a common point. for nicer highlights it
    // might be better to chose vertices in a more clever way.
    int i = 0;
    for (float z = 0.0f; i < 2; i++, z += length_) {
        for (unsigned int segmentNum = 0; segmentNum < heightProfile_.size();
                segmentNum++) {
            glm::vec4 a, b, c, d, norm;

            a.x = cosHeight[segmentNum];
            a.y = sinHeight[segmentNum];
            a.z = z;
            a.w = 1.0f;

            b.x = cosHeight[segmentNum + 1];
            b.y = sinHeight[segmentNum + 1];
            b.z = z;
            b.w = 1.0f;

            c.x = cosSegment[segmentNum + 1] * innerRadius;
            c.y = sinSegment[segmentNum + 1] * innerRadius;
            c.z = z;
            c.w = 1.0f;

            d.x = cosSegment[segmentNum] * innerRadius;
            d.y = sinSegment[segmentNum] * innerRadius;
            d.z = z;
            d.w = 1.0f;
            norm = i == 0 ?
                    glm::vec4(0.0f, 0.0f, 1.0, 1.0) :
                    glm::vec4(0.0f, 0.0f, -1.0, 1.0);

            dataPushback(a);
            dataPushback(norm);
            dataPushback(b);
            dataPushback(norm);
            dataPushback(c);
            dataPushback(norm);
            dataPushback(d);
            dataPushback(norm);
        }
    }
}

//nice formula for the sides            d.y = sin((int)((phi+45) * 4 / 360) * M_PI / 2.0f);

//            cout << normA.x << ", " << normA.y << ", " << normA.z << endl;
//            cout << normB.x << ", " << normB.y << ", " << normB.z << endl;
//            cout << normC.x << ", " << normC.y << ", " << normC.z << endl;
//            cout << normD.x << ", " << normD.y << ", " << normD.z << endl;
//            cout << "-----" << endl;
