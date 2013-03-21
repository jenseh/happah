#ifndef DISC_H
#define DISC_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "happah/geometries/StandardProfile.h"
#include "happah/geometries/Geometry.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/InvoluteGear.h"
#include "glm/gtx/rotate_vector.hpp"

using namespace std;


class Disc: public Geometry {
public:
    Disc();
    ~Disc();
    virtual hpreal getRadius()= 0;
    virtual void setRadius(hpreal radius)= 0;
    TriangleMesh* toTriangleMesh();
protected:
    hpreal m_radius;// Radius der Scheibe ( y-achse und z-achse )
    hpreal m_length;// Länge/Breite der Scheibe ( x-achse )
    hpreal m_module; // Modul des höhenprofils
    std::vector<hpvec2> m_heightProfile;

    const static int HEIGHT_PROFILE_DETAIL_LEVEL = 60;
    const static int ANGLE_DETAIL_LEVEL = 100; // Wie viele samples auf dem rotationskörper gemacht werden

    virtual void createHeightProfile()= 0;
    void updateValues();
};

typedef shared_ptr<Disc> Disc_ptr;
#endif // DISC_H
