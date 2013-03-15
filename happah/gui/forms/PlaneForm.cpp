#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/PlaneForm.h"

PlaneForm::PlaneForm(PlaneListener& planeListener, QWidget* parent)
	: Form(parent), m_planeListener(planeListener)
{
	m_originInput = new VectorInput( "Origin", true, true, this );
	m_originInput->setValue( hpvec3(0.f, 0.f, 0.f) );
	connect(m_originInput, SIGNAL(valueChanged()), this, SLOT(updatePlaneOrigin()));
	m_normalInput = new VectorInput( "Normal", true, false, this );
	m_normalInput->setValue( hpvec3(0.f, 1.f, 0.f) );
	connect(m_normalInput, SIGNAL(valueChanged()), this, SLOT(updatePlaneNormal()));

	QPushButton* createButton  = new QPushButton("create plane");
	connect(createButton, SIGNAL(clicked()), this, SLOT(createPlane()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_originInput);
	layout->addWidget(m_normalInput);
	layout->addWidget(createButton);
	this->setLayout(layout);
	
	m_plane = Plane_ptr(new Plane(m_originInput->getValue(), m_normalInput->getValue()));
	m_planeInserted = false;
}

PlaneForm::~PlaneForm() {}

void PlaneForm::createPlane() {
	if( m_planeInserted ) {
		m_plane = Plane_ptr(new Plane(m_originInput->getValue(), m_normalInput->getValue()));
	}
	m_planeListener.insert(m_plane);
	m_planeInserted = true;
}

Plane_ptr PlaneForm::getPlane() const {
	return m_plane;
}

void PlaneForm::reset() {
	m_plane = Plane_ptr(new Plane(m_originInput->getValue(), m_normalInput->getValue()));
	m_planeInserted = false;
}

void PlaneForm::setPlane(Plane_ptr plane) {
	m_plane = plane;
	m_originInput->setValue(m_plane->getOrigin());
	m_normalInput->setValue(m_plane->getNormal());
	m_planeInserted = true;
}

void PlaneForm::updatePlaneOrigin() {
	m_plane->setOrigin(m_originInput->getValue());
	m_planeListener.update(m_plane);
}

void PlaneForm::updatePlaneNormal() {
	m_plane->setNormal(m_normalInput->getValue());
	m_planeListener.update(m_plane);
}
