#include <cstdlib>
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

	m_periodicCheckBox = new QCheckBox("Periodic", this);
	m_periodicCheckBox->setCheckState(Qt::Unchecked);
	connect( m_periodicCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changePeriodic(int)) );

	m_uniformCheckBox = new QCheckBox("Uniform", this);
	m_uniformCheckBox->setCheckState(Qt::Unchecked);
	connect( m_uniformCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeUniform(int)) );

	m_clampedCheckBox = new QCheckBox("Clamped", this);
	m_clampedCheckBox->setCheckState(Qt::Unchecked);
	connect( m_clampedCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeClamped(int)) );

	QWidget* degreeWidget = new QWidget(this);
	m_degreeSpinBox = new QSpinBox(degreeWidget);
	m_degreeSpinBox->setMinimum(1);
	QGridLayout* degreeLayout = new QGridLayout();
	degreeLayout->addWidget( new QLabel("Degree: ", degreeWidget), 0,0 );
	degreeLayout->addWidget( m_degreeSpinBox, 0,1 );
	degreeWidget->setLayout(degreeLayout);
	connect( m_degreeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeDegree(int)) );

	QPushButton* createButton  = new QPushButton("create curve");
	connect(createButton, SIGNAL(clicked()), this, SLOT(createCurve()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_controlPointInput);
	layout->addWidget(addPointButton);
	layout->addWidget(degreeWidget);
	layout->addWidget(m_periodicCheckBox);
	layout->addWidget(m_uniformCheckBox);
	layout->addWidget(m_clampedCheckBox);
	layout->addWidget(createButton);
	this->setLayout(layout);
	
	m_curve = BSplineCurve_ptr(new BSplineCurve());
	m_curve->setPeriodic(m_periodicCheckBox->checkState() == Qt::Checked);
	m_curve->setUniform(m_uniformCheckBox->checkState() == Qt::Checked);
	m_curve->setClamped(m_clampedCheckBox->checkState() == Qt::Checked);
	m_curve->setDegree(m_degreeSpinBox->value());
	m_curveInserted = false;

	m_plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 1.0f, 0.0f) ));
}

BSplineCurveForm::~BSplineCurveForm() {}

void BSplineCurveForm::addPoint() {
	if( m_curveInserted ) {
		m_curve->addControlPoint( m_controlPointInput->getValue() );
		m_guiManager.update(m_curve);
//		m_controlPointInput->setValue( hpvec3( 20.0f/(200-rand()%400), 20.0f/(200-rand()%400), 20.0f/(200-rand()%400) ));
	}
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
		m_curve->setPeriodic(m_periodicCheckBox->checkState() == Qt::Checked);
		m_curve->setUniform(m_uniformCheckBox->checkState() == Qt::Checked);
		m_curve->setClamped(m_clampedCheckBox->checkState() == Qt::Checked);
		m_curve->setDegree(m_degreeSpinBox->value());
	}
	m_guiManager.insert(m_curve,HP_LINE_MESH|HP_POINT_CLOUD);
	m_curveInserted = true;
}

BSplineCurve_ptr BSplineCurveForm::getCurve() const {
	return m_curve;
}

void BSplineCurveForm::handleRay(Ray& ray) {
	hpvec3 intersecPoint;
	if( m_plane->intersect( ray, intersecPoint ) ) {
		m_controlPointInput->setValue(intersecPoint);
		addPoint();
	}
}

void BSplineCurveForm::reset() {
	m_curve = BSplineCurve_ptr(new BSplineCurve());
	m_curve->setPeriodic(m_periodicCheckBox->checkState() == Qt::Checked);
	m_curve->setUniform(m_uniformCheckBox->checkState() == Qt::Checked);
	m_curve->setClamped(m_clampedCheckBox->checkState() == Qt::Checked);
	m_curve->setDegree(m_degreeSpinBox->value());
	m_curveInserted = false;
	m_plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 1.0f, 0.0f) ));
}

void BSplineCurveForm::setCurve(BSplineCurve_ptr curve) {
	m_curve = curve;
	m_periodicCheckBox->setCheckState( curve->getPeriodic() ? Qt::Checked : Qt::Unchecked );
	m_uniformCheckBox->setCheckState( curve->getUniform() ? Qt::Checked : Qt::Unchecked );
	m_clampedCheckBox->setCheckState( curve->getClamped() ? Qt::Checked : Qt::Unchecked );
	m_degreeSpinBox->setValue( curve->getDegree() );

	m_plane = m_guiManager.getParentPlane(m_curve);
	if( !m_plane ) {
		m_plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 1.0f, 0.0f) ));
	}

	m_curveInserted = true;
}

void BSplineCurveForm::setPlane(Plane_ptr plane) {
	if( plane ) m_plane = plane;
	else m_plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 1.0f, 0.0f) ));
}
