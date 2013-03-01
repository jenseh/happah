#include "happah/transformations/RigidAffineTransformation.h"

RigidAffineTransformation::RigidAffineTransformation()
	: m_matrix(1.0f), m_translation(0.0f, 0.0f, 0.0f) {}

RigidAffineTransformation::RigidAffineTransformation(const hpmat3x3& matrix, const hpvec3& translation) 
	: m_matrix(matrix), m_translation(translation) {}

RigidAffineTransformation::~RigidAffineTransformation() {}

void RigidAffineTransformation::compose(RigidAffineTransformation& rigidAffineTransformation, RigidAffineTransformation& out) {
	hpmat3x3 matrix = rigidAffineTransformation.getMatrix();
	out.setMatrix(m_matrix * matrix);
	hpvec3 translation = rigidAffineTransformation.getTranslation();
	out.setTranslation(m_matrix * translation + m_translation);
}

hpmat3x3 RigidAffineTransformation::getMatrix() const {
	return m_matrix;
}

hpvec3 RigidAffineTransformation::getTranslation() const {
	return m_translation;
}

void RigidAffineTransformation::setMatrix(const hpmat3x3& matrix) {
	m_matrix = matrix;
}

void RigidAffineTransformation::setTranslation(const hpvec3& translation) {
	m_translation = translation;
}

hpmat4x4 RigidAffineTransformation::toMatrix4x4() const{
	return glm::mat4(1.0f);
}
