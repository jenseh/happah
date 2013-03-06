#include "happah/gui/forms/PlaneForm.h"

PlaneForm::PlaneForm( QWidget* parent ) : Form(parent) {}

PlaneForm::~PlaneForm() {}

void PlaneForm::reset() {
	m_plane = Plane_ptr( new Plane( hpvec3(0,1,0), hpvec3(0,0,0) ) );
	m_planeInserted = false;

}

Plane_ptr PlaneForm::getPlane() const {
	return m_plane;
}

void PlaneForm::setPlane( Plane_ptr plane ) {
	m_plane = plane;
	m_planeInserted = true;
}
	
