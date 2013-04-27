#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "happah/transformations/RigidAffineTransformation.h"

#include "happah/math/Polynom.h"

/**
 * @brief The Kinematic class represents movement in 3d space defined through polynoms representing the movement and polynoms representing the rotation.
 */
class Kinematic
{
    Polynom<double> m_translateX, m_translateY, m_translateZ;
    Polynom<double> m_rotateX, m_rotateY, m_rotateZ;

public :
    /**
     * @brief Kinematic contructor for the polynoms with default polynom 0.
     * @param transX translation of the x position.
     * @param transY translation of the y position.
     * @param transZ translation of the z position.
     * @param rotX rotation around the x axis.
     * @param rotY rotation around the y axis.
     * @param rotZ rotation around the z axis.
     */
    Kinematic(Polynom<double> transX = Polynom<double>(0), Polynom<double> transY = Polynom<double>(0), Polynom<double> transZ = Polynom<double>(0),
              Polynom<double> rotX = Polynom<double>(0), Polynom<double> rotY = Polynom<double>(0), Polynom<double> rotZ = Polynom<double>(0));

    /**
     * @brief getLinearKinematic returns a linear kinematic of a transformation from position start to position end.
     * @param start start position of the kinematic.
     * @param end end position of the kinematic.
     * @return A Kinematic with the given parameters.
     */
    static Kinematic getLinearKinematic(hpvec3 start, hpvec3 end);

    /**
     * @brief getLinearKinematic returns a linear kinematic of a transformation from position start to position end with a constant rotation.
     * @param start start position of the kinematic.
     * @param end end position of the kinematic.
     * @param rotY a constant rotation around the y axis.
     * @return A Kinematic with the given parameters.
     */
    static Kinematic getLinearKinematic(hpvec3 start, hpvec3 end, hpreal rotY);

    /**
     * @brief getMatrix gets the transformation matrix to a given time t evaluating the polynoms at position t.
     * @param t the time to which to calculate the transformation matrix.
     * @return the transformation matrix to the given time t.
     */
    hpmat4x4 getMatrix(double t);
    /**
     * @brief getRigidAffineTransformation gets the RigidAffineTransformation to a given time t.
     * @param t the time to which to calculate the RigidAffineTransformation.
     * @return the RigidAffineTransformation to the given time t.
     */
    RigidAffineTransformation getRigidAffineTransformation(double t);
};

#endif // KINEMATIC_H
