/*
 * SpurGear.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "SpurGear.h"

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
SpurGear::SpurGear(hpreal radius, hpreal length, int toothCount) {
    radius_ = radius;
    length_ = length;
    toothCount_ = toothCount;
    module_ = radius_ * 2.0f / toothCount_;
}

SpurGear::~SpurGear() {}

hpreal SpurGear::getRadius() {
    return radius_;
}

void SpurGear::createSinePartition() {
    // Use this to draw a sinus surface
    for (int i = 0; i < SEGMENT_COUNT; i++) {
        hpreal position = (hpreal) i / (hpreal) SEGMENT_COUNT;
        hpreal height = exp2f(sinf(position * 2.0f * M_PI));
        heightProfilePartition_.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
    }
}

void SpurGear::createApproximatedPartition() {
    const int segmentsPerLine = SEGMENT_COUNT / 4;

    hpreal horizX = 0.35f; //check whether 2*horiz + 2*flankX = 1.0
    hpreal flankX = 0.15f;

    // Use this to draw a gear with straight flanks and a quadratic bottom
    // horizontal teeth part
    for (int i = 0; i < segmentsPerLine; i++) {
        hpreal x = (hpreal) i / segmentsPerLine;
        heightProfilePartition_.push_back(glm::vec2(0.0f + x * horizX, 1.0f));
    }

    // right flank
    for (int i = 0; i < segmentsPerLine; i++) {
        hpreal x = (hpreal) i / segmentsPerLine;
        heightProfilePartition_.push_back(
                glm::vec2(horizX + x * flankX, 1.0f - x * 0.8f));
    }

    // lower teeth part
    // fit a quadratic function for the bottom part of a teeth hole
    for (int i = 0; i < segmentsPerLine; i++) {
        hpreal x = (hpreal) i / segmentsPerLine;
        hpreal position = horizX + flankX + x * horizX;
        hpreal height = 0.2f * pow(2.0f * x - 1.0f, 2.0f);
        heightProfilePartition_.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
    }

    //left flank
    for (int i = 0; i < segmentsPerLine; i++) {
        hpreal x = (hpreal) i / segmentsPerLine;
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
            hpreal position = heightProfilePartition_[j].x + i * module_ * M_PI;
            hpreal height = heightProfilePartition_[j].y;
            heightProfile_.push_back(glm::vec2(position, height));
        }
    }
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
QuadMesh* SpurGear::toQuadMesh() {
    const hpreal dz = length_ / Z_DETAIL_LEVEL;
    const hpreal innerRadius = radius_ * INNER_RADIUS_FACTOR;

    // Create the height profile given the current gear settings
    createHeightProfile();
    const unsigned int profSize = heightProfile_.size();

    // Create vector for the result
    std::vector<glm::vec4> vertexData;

    // precompute sin and cos of angles
    hpreal cosSegment[profSize + 2];
    hpreal sinSegment[profSize + 2];
    hpreal height[profSize + 2];
    hpreal cosHeight[profSize + 2];
    hpreal sinHeight[profSize + 2];

    for (unsigned int segmentNum = 0; segmentNum < profSize + 2;
            segmentNum++) {
        hpreal phi = heightProfile_[segmentNum % profSize].x / radius_; //in radians
        cosSegment[segmentNum] = cos(phi);
        sinSegment[segmentNum] = sin(phi);
        height[segmentNum] = radius_ + heightProfile_[segmentNum % profSize].y;
        cosHeight[segmentNum] = cosSegment[segmentNum] * height[segmentNum];
        sinHeight[segmentNum] = sinSegment[segmentNum] * height[segmentNum];
    }

    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        hpreal z = i * dz;
        for (unsigned int segmentNum = 0; segmentNum < profSize;
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

            vertexData.push_back(a);
            vertexData.push_back(normNext);
            vertexData.push_back(b);
            vertexData.push_back(norm);
            vertexData.push_back(c);
            vertexData.push_back(norm);
            vertexData.push_back(d);
            vertexData.push_back(normNext);
        }
    }

    // draw the front and back of the gear
    // this part is very straightforward. now alle quads have the
    // circle's center as a common point. for nicer highlights it
    // might be better to chose vertices in a more clever way.
    int i = 0;
    for (hpreal z = 0.0f; i < 2; i++, z += length_) {
        for (unsigned int segmentNum = 0; segmentNum < profSize;
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

            vertexData.push_back(a);
            vertexData.push_back(norm);
            vertexData.push_back(b);
            vertexData.push_back(norm);
            vertexData.push_back(c);
            vertexData.push_back(norm);
            vertexData.push_back(d);
            vertexData.push_back(norm);
        }
    }
    QuadMesh* result = new QuadMesh(vertexData);
    result->setModelMatrix(modelMatrix_);
    result->setName(name_ + " - Instance 1");
    return result;
}

// This creates the triangle mesh representation of a gear. The gear axis is the model's z-axis.
TriangleMesh* SpurGear::toTriangleMesh() {
    hpreal dz = length_ / Z_DETAIL_LEVEL;
    hpreal innerRadius = radius_ * INNER_RADIUS_FACTOR;

    // Create the height profile given the current gear settings
    createHeightProfile();
    unsigned int profSize = heightProfile_.size();

    // Create vector for the result
    std::vector<glm::vec4> vertexData;

    // precompute sin and cos of angles
    hpreal cosSegment[profSize + 2];
    hpreal sinSegment[profSize + 2];
    hpreal height[profSize + 2];
    hpreal cosHeight[profSize + 2];
    hpreal sinHeight[profSize + 2];

    for (unsigned int segmentNum = 0; segmentNum < profSize + 2;
            segmentNum++) {
        hpreal phi = heightProfile_[segmentNum % profSize].x / radius_; //in radians
        cosSegment[segmentNum] = cos(phi);
        sinSegment[segmentNum] = sin(phi);
        height[segmentNum] = radius_ + heightProfile_[segmentNum % profSize].y;
        cosHeight[segmentNum] = cosSegment[segmentNum] * height[segmentNum];
        sinHeight[segmentNum] = sinSegment[segmentNum] * height[segmentNum];
    }

    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        hpreal z = i * dz;
        for (unsigned int segmentNum = 0; segmentNum < profSize; segmentNum++) {

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

            // compute the 2 normals (each used twice)
            normNext = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, dz),
                                    glm::vec3(cosHeight[segmentNum + 2] - cosHeight[segmentNum + 1],
                                              sinHeight[segmentNum + 2] - sinHeight[segmentNum + 1],
                                              0.0f))),
                    1.0f);
            norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, dz),
                                    glm::vec3(cosHeight[segmentNum + 1] - cosHeight[segmentNum],
                                              sinHeight[segmentNum + 1] - sinHeight[segmentNum],
                                              0.0f))),
                    1.0f);

            vertexData.push_back(a);
            vertexData.push_back(normNext);
            vertexData.push_back(b);
            vertexData.push_back(norm);
            vertexData.push_back(c);
            vertexData.push_back(norm);

            vertexData.push_back(a);
            vertexData.push_back(normNext);
            vertexData.push_back(c);
            vertexData.push_back(norm);
            vertexData.push_back(d);
            vertexData.push_back(normNext);
        }
    }

    // draw the front and back of the gear
    int i = 0;
    for (hpreal z = 0.0f; i < 2; i++, z += length_) {
        for (unsigned int segmentNum = 0; segmentNum < profSize;
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
                    glm::vec4(0.0f, 0.0f, -1.0f, 1.0f) :
                    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            vertexData.push_back(a);
            vertexData.push_back(norm);
            vertexData.push_back(b);
            vertexData.push_back(norm);
            vertexData.push_back(c);
            vertexData.push_back(norm);

            vertexData.push_back(c);
            vertexData.push_back(norm);
            vertexData.push_back(d);
            vertexData.push_back(norm);
            vertexData.push_back(a);
            vertexData.push_back(norm);
        }
    }
    TriangleMesh* result = new TriangleMesh(vertexData);
    result->setModelMatrix(modelMatrix_);
    result->setName(name_ + " - Instance 1");
    return result;
}

// This method converts a SpurGear to a Circle cloud representation.
// Note that this is not more than a set of circles centered around
// the gear center with various radii ranging from the minimum radius
// to the maximum radius.
CircleCloud* SpurGear::toCircleCloud() {
  // Determine accuracy level of the simulation
  const hpreal epsilon = 0.000001f;

    // Determine radius constraints
  const hpreal minRadius = radius_ * INNER_RADIUS_FACTOR - epsilon;
  const hpreal maxRadius = radius_ + epsilon;

  // Determine resolution (important for following simulations)
  const int resolutionXY = 1000;
  const int resolutionZ = 1000;

  std::vector<Circle*> circles(resolutionXY * resolutionZ);

  const hpreal diffRadius = maxRadius - minRadius;
  const hpreal diffRadiusStep = diffRadius / resolutionXY;

  for (int stepZ = 0; stepZ < resolutionZ; stepZ++) {
    hpreal z = stepZ / resolutionZ * length_;
    for (int stepXY = 0; stepXY < resolutionXY; stepXY++) {
        hpreal radius = minRadius + diffRadiusStep * stepXY;
        glm::vec3 center = glm::vec3(0.0f, 0.0f, z);
        circles[stepZ * resolutionZ + stepXY] = new Circle(center, glm::vec3(0.0f, 0.0f, 1.0f), radius);
    }
  }
  return new CircleCloud(circles, resolutionXY, resolutionZ);
}


ZCircleCloud* SpurGear::toZCircleCloud() {
  // Determine accuracy level of the simulation
  const float epsilon = 0.000001f;

    // Determine radius constraints
  const float minRadius = radius_ * INNER_RADIUS_FACTOR - epsilon;
  const float maxRadius = radius_ + epsilon;

  // Determine resolution (important for following simulations)
  const int resolutionXY = 1000;
  const int resolutionZ = 1000;

  const float diffRadius = maxRadius - minRadius;
  const float diffRadiusStep = diffRadius / resolutionXY;

  std::vector<float>* radii = new std::vector<float>(resolutionXY);
  std::vector<float>* posZ = new std::vector<float>(resolutionZ);

  for (int stepZ = 0; stepZ < resolutionZ; stepZ++) {
      float posZvalue = stepZ * length_ / resolutionZ;
      (*posZ)[stepZ] = posZvalue;
  }

  for (int stepXY = 0; stepXY < resolutionXY; stepXY++) {
      float radius = minRadius + diffRadiusStep * stepXY;
      (*radii)[stepXY] = radius;
  }

  ZCircleCloud* result = new ZCircleCloud(radii, posZ, resolutionXY, resolutionZ);
  result->setModelMatrix(modelMatrix_);
  return result;
}
