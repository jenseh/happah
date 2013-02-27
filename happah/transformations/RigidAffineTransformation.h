#ifndef RIGID_AFFINE_TRANSFORMATION_H
#define RIGID_AFFINE_TRANSFORMATION_H

#include <memory>

#include "happah/HappahTypes.h"

using namespace std;

class RigidAffineTransformation;

typedef shared_ptr<RigidAffineTransformation> RigidAffineTransformation_ptr;

class RigidAffineTransformation {

public:
	RigidAffineTransformation();
	RigidAffineTransformation(const hpmat3x3& matrix, const hpvec3& translation);
	~RigidAffineTransformation();

	void setMatrix(const hpmat3x3& matrix);
	void setTranslation(const hpvec3& translation);

protected:
	hpmat3x3 m_matrix;
	hpvec3 m_translation;

};

#endif // RIGID_AFFINE_TRANSFORMATION_H
