#include "BSplineTool.h"

#include <QGroupBox>

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


}

BSplineTool::~BSplineTool() {
}

void BSplineTool::generateRndPoint() {
	pointAdded(qrand() % 1024, qrand() % 768 );
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
}

bool BSplineTool::knowsItem(Drawable2D* drawable) {
	return (dynamic_cast<BSplineCurve*>(drawable) != NULL);
}
void BSplineTool::reactivate(Drawable2D* drawable) {
	m_mode = this->EDITMODE;
	m_currentCurve = dynamic_cast<BSplineCurve*>(drawable);
	emit changed();
}

void BSplineTool::leftClickAt( QPointF point ) {
	this->pointAdded( point.x(), point.y() );
}

void BSplineTool::rightClickAt( QPointF point ) {
	this->finalise();
}


