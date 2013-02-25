#include "Kinematic.h"

Kinematic::Kinematic(Polynom<double> transX, Polynom<double> transY, Polynom<double> transZ,
                     Polynom<double> rotX, Polynom<double> rotY, Polynom<double> rotZ):
    m_translateX(transX), m_translateY(transY), m_translateZ(transZ),
    m_rotateX(rotX), m_rotateY(rotY), m_rotateZ(rotZ){
}

// Get Matrix at time t
glm::mat4 Kinematic::getMatrix(double t){
    glm::mat4 result(1);
    // Rotation
    result = glm::rotate(result, (float)m_rotateX.getY(t), glm::vec3(1,0,0));
    result = glm::rotate(result, (float)m_rotateY.getY(t), glm::vec3(0,1,0));
    result = glm::rotate(result, (float)m_rotateZ.getY(t), glm::vec3(0,0,1));
    // Translation
    result = glm::translate(result,
                   glm::vec3(m_translateX.getY(t), m_translateY.getY(t), m_translateZ.getY(t)) );
    return result;
}


Kinematic Kinematic::getLinearKinematic(glm::vec3 start, glm::vec3 end){
    glm::vec3 delta = end - start;
    return Kinematic(Polynom<double>(2,start.x, delta.x), Polynom<double>(2,start.y, delta.y), Polynom<double>(2,start.z, delta.z));
}
