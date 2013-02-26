#include "happah/gui/qt/BSplineTool.h"

#include <QGroupBox>
#include "happah/geometries/BSplineGearCurve.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/models/TriangleMesh.h"
#include "happah/gui/RenderItem3D.h"

BSplineTool::BSplineTool() {
	m_mode = this->IDLEMODE;

	getToolButton()->setText("B");

	QVBoxLayout* vbox = new QVBoxLayout();
	QGroupBox* gbox = new QGroupBox("B-Spline Curve");
	vbox->addWidget(gbox);
	getToolSettings()->setLayout(vbox);

	vbox = new QVBoxLayout();
	gbox->setLayout(vbox);

	m_chkPeriodic = new QCheckBox("Periodic");
	m_chkPeriodic->setCheckState(Qt::Unchecked);
	vbox->addWidget(m_chkPeriodic);
	connect(m_chkPeriodic, SIGNAL(stateChanged(int)), this, SLOT(periodicChanged(int)) );

	m_chkUniform = new QCheckBox("Uniform");
	m_chkUniform->setCheckState(Qt::Checked);
	vbox->addWidget(m_chkUniform);
	connect(m_chkUniform, SIGNAL(stateChanged(int)), this, SLOT(uniformChanged(int)) );

	m_chkInterpolateEnds = new QCheckBox("Clamped");
	m_chkInterpolateEnds->setCheckState(Qt::Unchecked);
	vbox->addWidget(m_chkInterpolateEnds);
	connect(m_chkInterpolateEnds, SIGNAL(stateChanged(int)), this, SLOT(clampedChanged(int)) );

	m_degreeChooser = new QSpinBox();
	m_degreeChooser->setMinimum(1);
	vbox->addWidget(m_degreeChooser);
	connect(m_degreeChooser, SIGNAL(valueChanged(int)), this, SLOT(degreeChanged(int)) );

	QPushButton* genBtn = new QPushButton("Random Pt");
	connect(genBtn, SIGNAL(clicked()), this, SLOT(generateRndPoint()));
	vbox->addWidget(genBtn);

	genBtn = new QPushButton("End curve");
	connect(genBtn, SIGNAL(clicked()), this, SLOT(finalise()));
	vbox->addWidget(genBtn);

	QWidget* optionWidget = new QWidget();
	m_options = new QVBoxLayout();
	optionWidget->setLayout(m_options);
	vbox->addWidget(optionWidget);
}

BSplineTool::~BSplineTool() {
}

void BSplineTool::generateRndPoint() {
	pointAdded(qrand() % 400, qrand() % 400); //TODO: used these values as scene area changed. global settings maybe better
	//pointAdded(qrand() % 1024, qrand() % 768 );
}

void BSplineTool::periodicChanged( int state ) {
	if( m_mode == this->EDITMODE ) {
		m_currentCurve->setPeriodic( state==Qt::Checked );
		emit changed();
	}
}

void BSplineTool::uniformChanged( int state ) {
	if( m_mode == this->EDITMODE ) {
		m_currentCurve->setUniform( state==Qt::Checked );
		emit changed();
	}
}

void BSplineTool::clampedChanged( int state ) {
	if( m_mode == this->EDITMODE ) {
		m_currentCurve->setClamped( state==Qt::Checked );
		emit changed();
	}
}

void BSplineTool::degreeChanged( int degree ) {
	if( m_mode == this->EDITMODE ) {
		m_currentCurve->setDegree(degree);
		emit changed();
	}
}

void BSplineTool::pointAdded( int x, int y ) {
	if( m_mode == this->EDITMODE ) {
		m_currentCurve->addControlPoint( x, y, 0 );
		emit changed();
	}
	else {
		m_mode = this->EDITMODE;
		m_currentCurve = new BSplineCurve();
		m_currentCurve->setName("BSplineCurve");
		m_currentCurve->setDegree(m_degreeChooser->value());
		m_currentCurve->setPeriodic( m_chkPeriodic->checkState()==Qt::Checked );
		m_currentCurve->setUniform( m_chkUniform->checkState()==Qt::Checked );
		m_currentCurve->setClamped( m_chkInterpolateEnds->checkState()==Qt::Checked );
		m_currentCurve->addControlPoint( x, y, 0 );
		emit emitComponent(m_currentCurve);
	}
}

void BSplineTool::finalise() {
	if( m_mode == this->EDITMODE ) {
		m_mode = this->IDLEMODE;
		m_currentCurve = NULL;
		emit changed();
	}
	deleteOptions();
}

bool BSplineTool::knowsItem(Drawable2D* drawable) {
	return (dynamic_cast<BSplineCurve*>(drawable) != NULL);
}
void BSplineTool::reactivate(Drawable2D* drawable) {
	m_mode = this->EDITMODE;
	if ( m_currentCurve = dynamic_cast<BSplineGearCurve*>( drawable )) {
		addGearOptions();
		emit changed();
	} else if ( m_currentCurve = dynamic_cast<BSplineCurve*>(drawable) ) {
		addCurveOptions();
		emit changed();
	}
}
void BSplineTool::addCurveOptions() {
	QPushButton* toGear = new QPushButton("Take as tooth of a gear");
	connect(toGear, SIGNAL(clicked()), this, SLOT(toGearCurve()));
	m_options->addWidget(toGear);
}
void BSplineTool::toGearCurve() {
	BSplineGearCurve* gearCurve = new BSplineGearCurve(*m_currentCurve);
	deleteCurrentAndEmitNew(gearCurve);
	m_currentCurve = gearCurve;
	emit changed();
}
void BSplineTool::addGearOptions() {
	QPushButton* show3dGear = new QPushButton("Show gear in 3D");
	connect(show3dGear, SIGNAL(clicked()), this, SLOT(toSimpleGear()));
	m_options->addWidget(show3dGear);
}
void BSplineTool::toSimpleGear() {
	SimpleGear* gear = new SimpleGear(new BSplineGearCurve(*m_currentCurve), 0.0f, 0.2f);
	TriangleMesh* gearMesh = gear->toTriangleMesh();
	gearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f); //ka, kd, ks, phong
	RenderItem3D* item3d = new RenderItem3D(gear, gearMesh, m_currentCurve->getName());
	deleteCurrentAndEmitNew(item3d);
}

void BSplineTool::deleteOptions() {
	for(uint i = 0; i < m_options->count(); ++i) {
		QLayoutItem* item = m_options->itemAt(i);
		m_options->removeItem(item);
		delete item->widget();
		delete item;
	}
}

void BSplineTool::leftClickAt( QPointF point ) {
	this->pointAdded( point.x(), point.y() );
}

void BSplineTool::rightClickAt( QPointF point ) {
	this->finalise();
}


