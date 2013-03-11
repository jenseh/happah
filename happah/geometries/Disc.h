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
#include "happah/geometries/StandardProfile.h"
#include "happah/geometries/Geometry.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"

using namespace std;


class Disc: public Geometry {
public:
    Disc(hpreal radius = 1.0f);

    ~Disc();
    hpreal getRadius();
    glm::vec3 getCenter();
    void setRadius(hpreal);
    TriangleMesh* toTriangleMesh();
private:
    hpreal m_radius;// Radius der Scheibe ( y-achse und z-achse )
    hpreal m_length;// Länge/Breite der Scheibe ( x-achse )
    hpreal m_module; // Modul des höhenprofils
    std::vector<glm::vec2> m_heightProfile;
    StandardProfile* m_standardProfile;

    const static int SEGMENT_COUNT = 50; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 100; // Wie viele samples auf dem rotationskörper gemacht werden

    std::vector<glm::vec4> createVertexData();
    void createHeightProfile();
    void updateValues();
};

typedef shared_ptr<Disc> Disc_ptr;
#endif // DISC_H
