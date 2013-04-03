#ifndef DISC_H
#define DISC_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "happah/geometries/StandardProfile.h"
#include "happah/geometries/Geometry.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/gears/InvoluteGear.h"
#include "glm/gtx/rotate_vector.hpp"

using namespace std;


class SurfaceOfRevolution : public Geometry {
public:
    SurfaceOfRevolution(std::vector<hpvec2>& heightProfile);
    ~SurfaceOfRevolution();
    hpreal getRadius();

    TriangleMesh_ptr toTriangleMesh(uint nWedges = 60);
private:
    std::vector<hpvec2> m_heightProfile;
    hpreal m_radius;
};

typedef shared_ptr<SurfaceOfRevolution> SurfaceOfRevolution_ptr;
#endif // DISC_H
