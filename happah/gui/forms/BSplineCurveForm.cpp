#include <QPushButton>
#include <QVBoxLayout>
#include <cstdlib>

#include "happah/gui/forms/BSplineCurveForm.h"

BSplineCurveForm::BSplineCurveForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_guiManager(guiManager) {
	
	m_controlPointInput = new VectorInput( "Next Point", true, true, this );
	m_controlPointInput->setValue( hpvec3(0.f, 0.f, 0.f) );
	//connect(m_controlPointInput, SIGNAL(valueChanged()), this, SLOT(updateBSplineCurveOrigin()));

	QPushButton* addPointButton  = new QPushButton("add control point");
	connect(addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));

	QPushButton* createButton  = new QPushButton("create curve");
	connect(createButton, SIGNAL(clicked()), this, SLOT(createCurve()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_controlPointInput);
	layout->addWidget(addPointButton);
	layout->addWidget(createButton);
	this->setLayout(layout);
	
	m_curve = BSplineCurve_ptr(new BSplineCurve());
	m_curveInserted = false;
}

BSplineCurveForm::~BSplineCurveForm() {}

void BSplineCurveForm::addPoint() {
	m_curve->addControlPoint( m_controlPointInput->getValue() );
	if( m_curveInserted ) {
		m_guiManager.update(m_curve);
	}
	m_controlPointInput->setValue( hpvec3( 20.0f/(200-rand()%400), 20.0f/(200-rand()%400), 20.0f/(200-rand()%400) ));
}

void BSplineCurveForm::createCurve() {
	if( m_curveInserted ) {
		m_curve = BSplineCurve_ptr(new BSplineCurve());
	}
	m_guiManager.insert(m_curve,HP_POINT_CLOUD);
	m_curveInserted = true;
}

BSplineCurve_ptr BSplineCurveForm::getCurve() const {
	return m_curve;
}

void BSplineCurveForm::reset() {
	m_curve = BSplineCurve_ptr(new BSplineCurve());
	m_curveInserted = false;
}

void BSplineCurveForm::setCurve(BSplineCurve_ptr curve) {
	m_curve = curve;
	m_curveInserted = true;
}
