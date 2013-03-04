#ifndef SPHERE_H_
#define SPHERE_H_

#include <math.h>
#include <glm/glm.hpp>
#include "happah/geometries/NonDrawable.h"
#include "happah/geometries/QuadMesh.h"

using namespace std;

class Sphere: public NonDrawable {

public:
    Sphere(float radius = 1.0f, glm::vec4 center= glm::vec4(0.0f,0.0f,0.0f,1.0f),
           std::string name = "Sphere");
           
    ~Sphere();

    float getRadius();

    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();

private:
    float m_radius;
    glm::vec4 m_center;
    std::vector<glm::vec4> m_vertexData;
};
#endif /* SPHERE_H_ */
