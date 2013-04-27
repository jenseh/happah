#include <cstdlib>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/BSplineCurveForm.h"

BSplineCurveForm::BSplineCurveForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent), m_guiManager(guiManager), m_currentPointIndex(-1) {

	QVBoxLayout* layout = new QVBoxLayout();
	this->setLayout(layout);

	m_controlPointInput = new VectorInput( "Next Point", false, true, false, this );
	m_controlPointInput->setValue( hpvec3(0.f, 0.f, 0.f) );
	layout->addWidget(m_controlPointInput);

	QPushButton* addPointButton  = new QPushButton("add control point");
	connect(addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));
	layout->addWidget(addPointButton);

	QPushButton* deletePointButton  = new QPushButton("delete current point");
	connect(deletePointButton, SIGNAL(clicked()), this, SLOT(deletePoint()));
	layout->addWidget(deletePointButton);

	QPushButton* interpolateButton  = new QPushButton("interpolate control points");
	connect(interpolateButton, SIGNAL(clicked()), this, SLOT(interpolate()));
	layout->addWidget(interpolateButton);

	m_periodicCheckBox = new QCheckBox("Periodic", this);
	m_periodicCheckBox->setCheckState(Qt::Unchecked);
	connect( m_periodicCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changePeriodic(int)) );
	layout->addWidget(m_periodicCheckBox);

	m_uniformCheckBox = new QCheckBox("Uniform", this);
	m_uniformCheckBox->setCheckState(Qt::Unchecked);
	connect( m_uniformCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeUniform(int)) );
	layout->addWidget(m_uniformCheckBox);

	m_clampedCheckBox = new QCheckBox("Clamped", this);
	m_clampedCheckBox->setCheckState(Qt::Unchecked);
	connect( m_clampedCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeClamped(int)) );
	layout->addWidget(m_clampedCheckBox);

	QWidget* degreeWidget = new QWidget(this);
	m_degreeSpinBox = new QSpinBox(degreeWidget);
	m_degreeSpinBox->setMinimum(1);
	QGridLayout* degreeLayout = new QGridLayout();
	degreeLayout->addWidget( new QLabel("Degree: ", degreeWidget), 0,0 );
	degreeLayout->addWidget( m_degreeSpinBox, 0,1 );
	degreeWidget->setLayout(degreeLayout);
	connect( m_degreeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeDegree(int)) );
	layout->addWidget(degreeWidget);

	QWidget* planeWidget = new QWidget(this);
	layout->addWidget(planeWidget);
	QGridLayout* planeLayout = new QGridLayout();
	planeWidget->setLayout( planeLayout );
	m_planeLabel = new QLabel("Using standard plane", planeWidget);
	planeLayout->addWidget( m_planeLabel, 0,0 );
	/*
	QPushButton* planeButton = new QPushButton("reset", planeWidget);
	planeLayout->addWidget( planeButton, 0,1 );
	connect( planeButton, SIGNAL(clicked()), this, SLOT(resetPlane()) );
	*/
	// TODO connect to resetPlane() instead of reset()

	QPushButton* createButton  = new QPushButton("create curve");
	connect(createButton, SIGNAL(clicked()), this, SLOT(createCurve()));
	layout->addWidget(createButton);

	QPushButton* resetButton = new QPushButton("reset", this);
	layout->addWidget(resetButton);
	connect( resetButton, SIGNAL(clicked()), this, SLOT(reset()) );

	QWidget* empty = new QWidget();
	empty->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Expanding);
	layout->addWidget(empty);
	
	reset();
}

BSplineCurveForm::~BSplineCurveForm() {}

void BSplineCurveForm::addPoint() {
	if( m_curveInserted ) {
		hpvec3 normal = m_plane->getNormal();
		hpvec3 point = m_controlPointInput->getValue();
		Ray ray( point, normal );
		hpvec2 planePoint;
		m_plane->intersect( ray, planePoint );
		m_curve->addControlPoint( planePoint );
		m_guiManager.update(m_curve);
	}
	projectPointOntoPlane();
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
		m_curve = BSplineCurve2D_ptr(new BSplineCurve<hpvec2>());
		m_curve->setPeriodic(m_periodicCheckBox->checkState() == Qt::Checked);
		m_curve->setUniform(m_uniformCheckBox->checkState() == Qt::Checked);
		m_curve->setClamped(m_clampedCheckBox->checkState() == Qt::Checked);
		m_curve->setDegree(m_degreeSpinBox->value());
	}
	if( !m_useStandardPlane ) {
		m_guiManager.insert(m_plane, m_curve);
	}
	m_guiManager.insert(m_curve,HP_LINE_MESH|HP_POINT_CLOUD); // TODO use findContaining instead of findChildContaining
	m_curveInserted = true;
}

void BSplineCurveForm::deletePoint() {
	if( m_curveInserted ) {
		if( m_currentPointIndex > -1 ) {
			m_curve->removeControlPoint( m_currentPointIndex );
			m_currentPointIndex = -1;
		}
		else {
			m_curve->removeControlPoint( m_curve->getNumberOfControlPoints() - 1);
		}
		m_guiManager.update( m_curve );
	}
}

BSplineCurve2D_ptr BSplineCurveForm::getCurve() const {
	return m_curve;
}

void BSplineCurveForm::handleDrag(Ray& ray) {
	/*
	if(m_pointMoving < 0) {
		hpreal minDistance = 1000000.0f;
		int nearestPointIndex = -1;
		for(hpuint i = 0; i < m_curve->getNumberOfControlPoints(); ++i) {
			hpvec3 controlPoint = m_curve->getControlPoint( i );
			hpreal distance = ray.distanceToPoint( controlPoint );
			if( distance < minDistance ) {
				minDistance = distance;
				nearestPointIndex = i;
			}
		}
		m_pointMoving = nearestPointIndex;
	}
	if( m_pointMoving >= 0 ) {
	*/
		hpvec2 intersecPoint;
		if( m_plane->intersect( ray, intersecPoint ) ) {
			m_curve->setControlPoint( m_currentPointIndex, intersecPoint );
			m_guiManager.update( m_curve );
		}
	//}
}

void BSplineCurveForm::handleRay(Ray& ray) {
	hpvec2 planePoint;
	if( m_curveInserted && m_plane->intersect( ray, planePoint ) ) {
		m_curve->addControlPoint( planePoint );
		m_guiManager.update(m_curve);
	}
}

void BSplineCurveForm::handleSelection(){
	emit selected(this);
	m_currentPointIndex = -1;
}

void BSplineCurveForm::handleSelection(int pointIndex){
	emit selected(this);
	m_currentPointIndex = pointIndex;
}

void BSplineCurveForm::interpolate() {
	m_curve->interpolateControlPoints( );
	m_guiManager.update(m_curve);

	m_degreeSpinBox->setValue( m_curve->getDegree() );
	m_clampedCheckBox->setCheckState( m_curve->isClamped() ? Qt::Checked : Qt::Unchecked );
	m_periodicCheckBox->setCheckState( m_curve->isPeriodic() ? Qt::Checked : Qt::Unchecked );
	m_uniformCheckBox->setCheckState( m_curve->isUniform() ? Qt::Checked : Qt::Unchecked );
}

void BSplineCurveForm::projectPointOntoPlane() {
	hpvec3 normal = m_plane->getNormal();
	hpvec3 origin = m_plane->getOrigin();
	hpvec3 point = m_controlPointInput->getValue();
	point = point + ( glm::dot(normal, origin-point ) )*normal;
	m_controlPointInput->setValue(point);
}

void BSplineCurveForm::reset() {
	m_curve = BSplineCurve2D_ptr(new BSplineCurve<hpvec2>());
	m_curve->setPeriodic(m_periodicCheckBox->checkState() == Qt::Checked);
	m_curve->setUniform(m_uniformCheckBox->checkState() == Qt::Checked);
	m_curve->setClamped(m_clampedCheckBox->checkState() == Qt::Checked);
	m_curve->setDegree(m_degreeSpinBox->value());
	m_curveInserted = false;
	resetPlane();
}

void BSplineCurveForm::resetPlane() {
	// TODO change scene graph for current curve/plane
	// TODO needs to be reset if current plane is deleted
	setPlane(Plane_ptr());
}

void BSplineCurveForm::setCurve(BSplineCurve2D_ptr curve) {
	m_curve = curve;
	m_periodicCheckBox->setCheckState( curve->isPeriodic() ? Qt::Checked : Qt::Unchecked );
	m_uniformCheckBox->setCheckState( curve->isUniform() ? Qt::Checked : Qt::Unchecked );
	m_clampedCheckBox->setCheckState( curve->isClamped() ? Qt::Checked : Qt::Unchecked );
	m_degreeSpinBox->setValue( curve->getDegree() );

	setPlane( m_guiManager.getParentPlane(m_curve) );

	m_curveInserted = true;
}

void BSplineCurveForm::setPlane(Plane_ptr plane) {
	if( plane ) {
		m_plane = plane;
		m_useStandardPlane = false;
		m_planeLabel->setText("Using scene plane");
	}
	else {
		m_plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 0.0f, 1.0f) ));
		m_useStandardPlane = true;
		m_planeLabel->setText("Using standard plane");
	}
}
