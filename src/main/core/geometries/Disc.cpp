/*
 * BasicRack.h
 *
 *  Created on: Dez 5, 2012
 *      Author: julian
 */

#include "Disc.h"


// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
Disc::Disc(float radius) {
    radius_ = radius; // doppelt so groß wie ein zahn
    module_ = radius_/2.0;
    length_ = module_ * M_PI;
    standardProfile = new StandardProfile(module_, 30 / 180.0 * M_PI, 0, 0);
}

Disc::~Disc() {
    delete standardProfile;
}

float Disc::getRadius() {
    return radius_;
}

// Create a profile of height values
void Disc::createHeightProfile() {
    heightProfile_ = std::vector<glm::vec2>();
    heightProfile_.resize(SEGMENT_COUNT);
    double x = length_/2.0;
    double deltaX = length_/(double)SEGMENT_COUNT;
    for( int i = 0; i < SEGMENT_COUNT; i++){
        heightProfile_[i].x = x;
        heightProfile_[i].y = standardProfile->getHeight(x) + module_;
        x+= deltaX;
    }
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
void Disc::createVertexData() {
    vertexData_.clear();
    float dalpha = 2*M_PI/ Z_DETAIL_LEVEL;

    // Create the height profile given the current gear settings
    createHeightProfile();


    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        double alpha1 = i * dalpha;
        double sinAlpha1 = sin(alpha1);
        double cosAlpha1 = cos(alpha1);
        double alpha2 = alpha1 + dalpha;
        double sinAlpha2 = sin(alpha2);
        double cosAlpha2 = cos(alpha2);
        for (unsigned int segmentNum = 0; segmentNum < heightProfile_.size()-1;
                segmentNum++) {

            glm::vec4 a, b, c, d, normNext, norm;

            a.x = heightProfile_[segmentNum+1].x;
            a.y = sinAlpha1 * heightProfile_[segmentNum+1].y;
            a.z = cosAlpha1 * heightProfile_[segmentNum+1].y;
            a.w = 1.0f;

            b.x = heightProfile_[segmentNum].x;
            b.y = sinAlpha1 * heightProfile_[segmentNum].y;
            b.z = cosAlpha1 * heightProfile_[segmentNum].y;
            b.w = 1.0f;

            c.x = heightProfile_[segmentNum].x;
            c.y = sinAlpha2 * heightProfile_[segmentNum].y;
            c.z = cosAlpha2 * heightProfile_[segmentNum].y;
            c.w = 1.0f;

            d.x = heightProfile_[segmentNum+1].x;
            d.y = sinAlpha2 * heightProfile_[segmentNum+1].y;
            d.z = cosAlpha2 * heightProfile_[segmentNum+1].y;
            d.w = 1.0f;

            /*norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
                    1.0f);*/
            glm::vec3 tempNorm = glm::cross( (glm::vec3)(a - b), (glm::vec3)(c - b));
            norm.x = tempNorm.x;
            norm.y = tempNorm.y;
            norm.z = tempNorm.z;
            norm.w = 1.0f;
            norm = glm::normalize(norm);




            vertexData_.push_back(a);
            //dataPushback(normNext);
            vertexData_.push_back(norm);
            vertexData_.push_back(b);
            vertexData_.push_back(norm);
            vertexData_.push_back(c);
            vertexData_.push_back(norm);
            vertexData_.push_back(d);
            //dataPushback(normNext);
            vertexData_.push_back(norm);
        }
    }
}

QuadMesh* Disc::toQuadMesh(){
    createVertexData();
    QuadMesh* result = new QuadMesh(vertexData_);
    result->setName(name_ + " - Instance 1");
    return result;
}

