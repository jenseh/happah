#include <QPushButton>
#include <QVBoxLayout>

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

#include <iostream>
void PlaneForm::createPlane() {
	hpvec3 normal = hpvec3(0.f, 1.f, 0.f);
	hpvec3 origin = hpvec3(0.f, 0.f, 0.f);
	if( !m_plane ) {
		m_plane = Plane_ptr(new Plane(origin,normal));
	}
	m_planeListener.insert(m_plane);
	m_planeInserted = true;
}

Plane_ptr PlaneForm::getPlane() const {
	return m_plane;
}

void PlaneForm::reset() {
	hpvec3 normal = hpvec3(0.f, 1.f, 0.f);
	hpvec3 origin = hpvec3(0.f, 0.f, 0.f);
	m_plane = Plane_ptr(new Plane(origin,normal));
	m_planeInserted = false;
}

void PlaneForm::setPlane(Plane_ptr plane) {
	m_plane = plane;
	m_planeInserted = true;
}

