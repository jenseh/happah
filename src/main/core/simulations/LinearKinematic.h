#ifndef LINEARKINEMATIC_H
#define LINEARKINEMATIC_H
#include "Kinematic.h"

class LinearKinematic: public Kinematic
{
    glm::vec3 m_Delta;// Translation per Iterations
public:
    LinearKinematic(int iterations, glm::vec3 start, glm::vec3 end);
    void calcNextMatrix();
};

#endif // LINEARKINEMATIC_H
