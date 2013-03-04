#include "happah/transformations/RigidAffineTransformation.h"
#include <glm/gtc/matrix_access.hpp>
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

	hpmat4x4 result = hpmat4x4(m_matrix[0][0],m_matrix[0][1],m_matrix[0][2],0.0f,
						m_matrix[1][0],m_matrix[1][1],m_matrix[1][2],0.0f,
						m_matrix[2][0],m_matrix[2][1],m_matrix[2][2],0.0f,
						m_translation.x,m_translation.y,m_translation.z,1.0f);

//	hpmat4x4 result = hpmat4x4(1.0f);
	return result;
}
