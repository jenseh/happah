#ifndef SPHERE_H_
#define SPHERE_H_

#include <math.h>
#include <glm/glm.hpp>


using namespace std;

class Sphere{

public:
    Sphere(float radius = 1.0f, glm::vec4 center= glm::vec4(0.0f,0.0f,0.0f,1.0f));
           
    ~Sphere();

    float getRadius();

    TriangleMesh* toTriangleMesh();

private:
    float m_radius;
    glm::vec4 m_center;
    std::vector<glm::vec4> m_verticesAndNormals;
};
#endif /* SPHERE_H_ */
