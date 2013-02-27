#include "happah/transformations/RigidAffineTransformation.h"

RigidAffineTransformation::RigidAffineTransformation() {}

RigidAffineTransformation::RigidAffineTransformation(const hpmat3x3& matrix, const hpvec3& translation) 
	: m_matrix(matrix), m_translation(translation) {}

RigidAffineTransformation::~RigidAffineTransformation() {}


void RigidAffineTransformation::setMatrix(const hpmat3x3& matrix) {
	m_matrix = matrix;
}

void RigidAffineTransformation::setTranslation(const hpvec3& translation) {
	m_translation = translation;
}
