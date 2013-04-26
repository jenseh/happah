#include <QPushButton>
#include <QVBoxLayout>

#include "happah/HappahConstants.h"
#include "happah/gui/forms/PlaneForm.h"

PlaneForm::PlaneForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_guiManager(guiManager)
{
	QVBoxLayout* layout = new QVBoxLayout();
	this->setLayout(layout);
	
	m_originInput = new VectorInput( "Origin", false, true, false, this );
	m_originInput->setValue( hpvec3(0.f, 0.f, 0.f) );
	connect(m_originInput, SIGNAL(valueChanged()), this, SLOT(updatePlaneOrigin()));
	layout->addWidget(m_originInput);

	m_normalInput = new VectorInput( "Normal", true, false, true, this );
	m_normalInput->setValue( hpvec3(0.f, 1.f, 0.f) );
	connect(m_normalInput, SIGNAL(valueChanged()), this, SLOT(updatePlaneNormal()));
	layout->addWidget(m_normalInput);

	QPushButton* createButton  = new QPushButton("create plane");
	connect(createButton, SIGNAL(clicked()), this, SLOT(createPlane()));
	layout->addWidget(createButton);

	QPushButton* resetButton  = new QPushButton("reset");
	connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
	layout->addWidget(resetButton);

	QWidget* empty = new QWidget();
	empty->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Expanding);
	layout->addWidget(empty);

	m_plane = Plane_ptr(new Plane(m_originInput->getValue(), m_normalInput->getValue()));
	m_planeInserted = false;
}

PlaneForm::~PlaneForm() {}

void PlaneForm::createPlane() {
	if( m_planeInserted ) {
		m_plane = Plane_ptr(new Plane(m_originInput->getValue(), m_normalInput->getValue()));
	}
	m_guiManager.insert(m_plane,HP_TRIANGLE_MESH);
	m_planeInserted = true;
}

Plane_ptr PlaneForm::getPlane() const {
	return m_plane;
}

void PlaneForm::reset() {
	m_plane = Plane_ptr(new Plane(m_originInput->getValue(), m_normalInput->getValue()));
	m_originInput->setValue(hpvec3(0.f, 0.f, 0.f));
	m_normalInput->setValue(hpvec3(0.f, 1.f, 0.f));

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
	m_guiManager.update(m_plane);
}

void PlaneForm::updatePlaneNormal() {
	m_plane->setNormal(m_normalInput->getValue());
	m_guiManager.update(m_plane);
}
