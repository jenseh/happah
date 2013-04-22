#ifndef DISC_H
#define DISC_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/Geometry.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/gears/InvoluteGear.h"
#include "glm/gtx/rotate_vector.hpp"

/**
 * @brief The SurfaceOfRevolution class represents a surface of revolution in 3d space.
 */
class SurfaceOfRevolution : public Geometry {
public:
    /**
     * @brief SurfaceOfRevolution constructor setting the height profile and calculating the radius.
     * @param heightProfile
     */
    SurfaceOfRevolution(std::vector<hpvec2>& heightProfile);
    /**
     *  @brief ~SurfaceOfRevolution destructor doing nothing.
     */
    ~SurfaceOfRevolution();
    /**
     * @brief getRadius gets the radius ( the maximum y value of the height profile ).
     * @return the radius of the surface of revolution.
     */
    hpreal getRadius();
    /**
     * @brief toTriangleMesh calculates the triangle mesh representing the surface of revolution.
     * @param nWedges count of the wedges with which the triangle mesh is calculated.
     * @return
     */
    TriangleMesh_ptr toTriangleMesh(uint nWedges = 160);

private:
    std::vector<hpvec2> m_heightProfile;
    hpreal m_radius;
};

typedef shared_ptr<SurfaceOfRevolution> SurfaceOfRevolution_ptr;
#endif // DISC_H
