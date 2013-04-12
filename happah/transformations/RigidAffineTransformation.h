#ifndef RIGID_AFFINE_TRANSFORMATION_H
#define RIGID_AFFINE_TRANSFORMATION_H

#include <memory>

#include "happah/HappahTypes.h"

using namespace std;

class RigidAffineTransformation;
typedef shared_ptr<RigidAffineTransformation> RigidAffineTransformation_ptr;

/**
 * @brief The RigidAffineTransformation class represents a riggid affine transformation in 3d space
 *          represented by a rotation matrix and a translation vector.
 */
class RigidAffineTransformation {

public:
    /**
     * @brief RigidAffineTransformation constructor setting rotation matrix to 1 and translation vector to 0.
     */
	RigidAffineTransformation();
    /**
     * @brief RigidAffineTransformation contructor setting rotation matrix to matrix and translation vector to translation.
     * @param matrix rotation matrix.
     * @param translation translation vector.
     */
	RigidAffineTransformation(const hpmat3x3& matrix, const hpvec3& translation);
    /**
     * Desctructor doing nothing.
     */
	~RigidAffineTransformation();
    /**
     * @brief compose Composing this transformation with rigidAffineTransformation and storing the result in out.
     * @param rigidAffineTransformation The transformation with which this transformation is composed.
     * @param out The transformation in which the result is stored.
     */
    void compose(RigidAffineTransformation& rigidAffineTransformation, RigidAffineTransformation& out);
    /**
     * @brief getMatrix gets the rotation matrix.
     * @return the rotation matrix.
     */
	hpmat3x3 getMatrix() const;
    /**
     * @brief getTranslation gets the translation vector.
     * @return the translation vector.
     */
	hpvec3 getTranslation() const;
    /**
     * @brief inverse gets the inverse transformation to this transformation.
     * @return the inverse transformation.
     */
	RigidAffineTransformation inverse()const;
    /**
     * @brief setMatrix sets the rotation matrix.
     * @param matrix the new rotation matrix.
     */
	void setMatrix(const hpmat3x3& matrix);
    /**
     * @brief setTranslation sets the translation vector.
     * @param translation the new translation vector.
     */
	void setTranslation(const hpvec3& translation);
    /**
     * @brief toMatrix4x4 converts the rigid affine transformation to a 4x4 transformation matrix.
     * @return the transformation matrix.
     */
	hpmat4x4 toMatrix4x4() const;

protected:
	hpmat3x3 m_matrix;
	hpvec3 m_translation;

};

#endif // RIGID_AFFINE_TRANSFORMATION_H
