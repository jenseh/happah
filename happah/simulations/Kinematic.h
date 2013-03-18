#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "happah/transformations/RigidAffineTransformation.h"

#include "happah/math/Polynom.h"

class Kinematic
{
    Polynom<double> m_translateX, m_translateY, m_translateZ;
    Polynom<double> m_rotateX, m_rotateY, m_rotateZ;

public :
    Kinematic(Polynom<double> transX = Polynom<double>(0), Polynom<double> transY = Polynom<double>(0), Polynom<double> transZ = Polynom<double>(0),
              Polynom<double> rotX = Polynom<double>(0), Polynom<double> rotY = Polynom<double>(0), Polynom<double> rotZ = Polynom<double>(0));

    // Get Matrix at time t
    glm::mat4 getMatrix(double t);
    RigidAffineTransformation getRigidAffineTransformation(double t);

    static Kinematic getLinearKinematic(glm::vec3 start, glm::vec3 end);

};

#endif // KINEMATIC_H
