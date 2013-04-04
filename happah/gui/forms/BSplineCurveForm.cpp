#include <cstdlib>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/BSplineCurveForm.h"

BSplineCurveForm::BSplineCurveForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_guiManager(guiManager) {
	
	m_controlPointInput = new VectorInput( "Next Point", true, true, this );
	m_controlPointInput->setValue( hpvec3(0.f, 0.f, 0.f) );
	//connect(m_controlPointInput, SIGNAL(valueChanged()), this, SLOT(updateBSplineCurveOrigin()));

	QPushButton* addPointButton  = new QPushButton("add control point");
	connect(addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));

	QCheckBox* periodicCheckBox = new QCheckBox("Periodic", this);
	periodicCheckBox->setCheckState(Qt::Unchecked);
	connect( periodicCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changePeriodic(int)) );

	QCheckBox* uniformCheckBox = new QCheckBox("Uniform", this);
	uniformCheckBox->setCheckState(Qt::Unchecked);
	connect( uniformCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeUniform(int)) );

	QCheckBox* clampedCheckBox = new QCheckBox("Clamped", this);
	clampedCheckBox->setCheckState(Qt::Unchecked);
	connect( clampedCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeClamped(int)) );

	QWidget* degreeWidget = new QWidget(this);
	QSpinBox* degreeSpinBox = new QSpinBox(degreeWidget);
	degreeSpinBox->setMinimum(1);
	QGridLayout* degreeLayout = new QGridLayout();
	degreeLayout->addWidget( new QLabel("Degree: ", degreeWidget), 0,0 );
	degreeLayout->addWidget( degreeSpinBox, 0,1 );
	degreeWidget->setLayout(degreeLayout);
	connect( degreeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeDegree(int)) );

	QPushButton* createButton  = new QPushButton("create curve");
	connect(createButton, SIGNAL(clicked()), this, SLOT(createCurve()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_controlPointInput);
	layout->addWidget(addPointButton);
	layout->addWidget(degreeWidget);
	layout->addWidget(periodicCheckBox);
	layout->addWidget(uniformCheckBox);
	layout->addWidget(clampedCheckBox);
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

void BSplineCurveForm::changePeriodic(int state) {
	m_curve->setPeriodic( state==Qt::Checked );
	if( m_curveInserted ) m_guiManager.update(m_curve);
}

void BSplineCurveForm::changeUniform(int state) {
	m_curve->setUniform( state==Qt::Checked );
	if( m_curveInserted ) m_guiManager.update(m_curve);
}

void BSplineCurveForm::changeClamped(int state) {
	m_curve->setClamped( state==Qt::Checked );
	if( m_curveInserted ) m_guiManager.update(m_curve);
}

void BSplineCurveForm::changeDegree(int value) {
	m_curve->setDegree( value );
	if( m_curveInserted ) m_guiManager.update(m_curve);
}

void BSplineCurveForm::createCurve() {
	if( m_curveInserted ) {
		m_curve = BSplineCurve_ptr(new BSplineCurve());
	}
	m_guiManager.insert(m_curve,HP_LINE_MESH|HP_POINT_CLOUD);
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
