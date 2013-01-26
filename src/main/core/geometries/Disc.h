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
    Disc(hpreal radius = 1.0f);

    ~Disc();
    hpreal getRadius();
    glm::vec3 getCenter();
    QuadMesh* toQuadMesh();
private:
    hpreal m_radius;// Radius der Scheibe ( y-achse und z-achse )
    hpreal m_length;// Länge/Breite der Scheibe ( x-achse )
    hpreal m_module; // Modul des höhenprofils
    std::vector<glm::vec2> m_heightProfile;
    StandardProfile* m_standardProfile;
    std::vector<glm::vec4> m_vertexData;

    const static int SEGMENT_COUNT = 50; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 100; // Wie viele samples auf dem rotationskörper gemacht werden

    void createVertexData();
    void createHeightProfile();
};
#endif // DISC_H
