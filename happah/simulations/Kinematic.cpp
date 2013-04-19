#include "happah/simulations/Kinematic.h"

Kinematic::Kinematic(Polynom<double> transX, Polynom<double> transY, Polynom<double> transZ,
                     Polynom<double> rotX, Polynom<double> rotY, Polynom<double> rotZ):
    m_translateX(transX), m_translateY(transY), m_translateZ(transZ),
    m_rotateX(rotX), m_rotateY(rotY), m_rotateZ(rotZ){
}

Kinematic Kinematic::getLinearKinematic(hpvec3 start, hpvec3 end){
    hpvec3 delta = end - start;
    return Kinematic(Polynom<double>(2,start.x, delta.x), Polynom<double>(2,start.y, delta.y), Polynom<double>(2,start.z, delta.z));
}

Kinematic Kinematic::getLinearKinematic(hpvec3 start, hpvec3 end, hpreal rotY){
    hpvec3 delta = end - start;
    return Kinematic(Polynom<double>(2, start.x, delta.x), Polynom<double>(2, start.y, delta.y), Polynom<double>(2, start.z, delta.z),
                     Polynom<double>(0), Polynom<double>(1, rotY), Polynom<double>(0));
}


hpmat4x4 Kinematic::getMatrix(double t){
    hpmat4x4 result(1);
    // Rotation
    result = glm::rotate(result, (float)m_rotateX.evaluateAt(t), hpvec3(1,0,0));
    result = glm::rotate(result, (float)m_rotateY.evaluateAt(t), hpvec3(0,1,0));
    result = glm::rotate(result, (float)m_rotateZ.evaluateAt(t), hpvec3(0,0,1));
    // Translation
    result = glm::translate(result,
                   hpvec3(m_translateX.evaluateAt(t), m_translateY.evaluateAt(t), m_translateZ.evaluateAt(t)) );
    return result;
}

RigidAffineTransformation Kinematic::getRigidAffineTransformation(double t){
	hpmat4x4 matrix(1);
    // Rotation
	matrix = glm::rotate(matrix, (float)m_rotateX.evaluateAt(t), hpvec3(1,0,0));
	matrix = glm::rotate(matrix, (float)m_rotateY.evaluateAt(t), hpvec3(0,1,0));
	matrix = glm::rotate(matrix, (float)m_rotateZ.evaluateAt(t), hpvec3(0,0,1));
    // Translation
    return RigidAffineTransformation( hpmat3x3(matrix), hpvec3(m_translateX.evaluateAt(t), m_translateY.evaluateAt(t), m_translateZ.evaluateAt(t)) );
}
