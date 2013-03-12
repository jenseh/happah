#include "happah/gui/forms/PlaneForm.h"

PlaneForm::PlaneForm(PlaneListener& planeListener, QWidget* parent)
	: Form(parent), m_planeListener(planeListener)
{
	QPushButton* createButton  = new QPushButton("create plane");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(createButton);
	this->setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createPlane()));
}

PlaneForm::~PlaneForm() {}

void PlaneForm::createPlane() {
	if( m_plane ) {
		m_plane = Plane_ptr(new Plane(hpvec3(0, 1, 0), hpvec3(0, 0, 0)));
	}
	m_planeListener.insert(m_plane);
	m_planeInserted = true;
}

Plane_ptr PlaneForm::getPlane() const {
	return m_plane;
}

void PlaneForm::reset() {
	m_plane = Plane_ptr(new Plane(hpvec3(0, 1, 0), hpvec3(0, 0, 0)));
	m_planeInserted = false;
}

void PlaneForm::setPlane(Plane_ptr plane) {
	m_plane = plane;
	m_planeInserted = true;
}

