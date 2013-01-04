/*
 * BasicRack.h
 *
 *  Created on: Dez 5, 2012
 *      Author: julian
 */

#ifndef DISC_H
#define DISC_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "NonDrawable.h"
#include "StandardProfile.h"

using namespace std;


class Disc: public NonDrawable {
public:
    Disc(float radius = 1.0f);

    ~Disc();
    float getRadius();
    glm::vec3 getCenter();
    QuadMesh* toQuadMesh();
private:
    float radius_;// Radius der Scheibe ( y-achse und z-achse )
    float length_;// Länge/Breite der Scheibe ( x-achse )
    float module_; // Modul des höhenprofils
    std::vector<glm::vec2> heightProfile_;
    StandardProfile* standardProfile;
    std::vector<glm::vec4> vertexData_;

    const static int SEGMENT_COUNT = 50; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 100; // Wie viele samples auf dem rotationskörper gemacht werden

    void createVertexData();
    void createHeightProfile();
};
#endif // DISC_H
