#include "happah/gui/forms/FocalSplineForm.h"

#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

FocalSplineForm::FocalSplineForm(GUIManager& guiManager,QWidget* parent)
	: Form(parent),m_guiManager(guiManager), m_focalSplineInserted(false),m_currentPointIndex(-1) {
	QPushButton* createButton = new QPushButton("Create Focal Spline");
	m_addPointButton = new QPushButton("Add ControlPoints");
	m_degreeSpinBox = new QSpinBox;
	m_degreeSpinBox->setValue(2);
	m_detailSpinBox = new QSpinBox();
	m_detailSpinBox->setValue(20);
	m_showControlPolygon = new QPushButton("Hide Control Polygon");
	m_showControlPolygon->setCheckable(true);
	m_showCircleButton = new QPushButton("Hide Unit Circle");
	m_showCircleButton->setCheckable(true);
	QPushButton* extendButton = new QPushButton("Extend Spline");
	connect(createButton,SIGNAL(clicked()),this,SLOT(createFocalSpline()));
	connect(m_degreeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeDegree(int)));
	connect(m_detailSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeDetail(int)));
	connect(extendButton,SIGNAL(clicked()),this,SLOT(extendSpline()));
	connect(m_showControlPolygon,SIGNAL(clicked()),this,SLOT(toggleControlPolygon()));
	connect(m_showCircleButton,SIGNAL(clicked()),this,SLOT(toggleCircle()));
	m_addPointButton->setCheckable(true);
	QLabel* detailLabel = new QLabel("Detail");
	QGroupBox* focalSplineGroupBox = new QGroupBox(tr("Focal Spline"));
	QGridLayout* focalSplineGrid = new QGridLayout;
	focalSplineGrid->addWidget(createButton,0,0);
	focalSplineGrid->addWidget(extendButton,1,0);
	focalSplineGrid->addWidget(m_addPointButton,2,0);
	focalSplineGrid->addWidget(detailLabel,0,1);
	focalSplineGrid->addWidget(m_detailSpinBox,0,2);
	focalSplineGrid->addWidget(m_showControlPolygon,3,0);
	focalSplineGrid->addWidget(m_showCircleButton,3,1);
	focalSplineGroupBox->setLayout(focalSplineGrid);
	QGroupBox* focalBezierCurveBox = new QGroupBox(tr("Focal Bezier Curve"));
	QGridLayout* focalBezierCurveGrid = new QGridLayout;
	QLabel* degreeLabel = new QLabel("Degree");
	focalBezierCurveGrid->addWidget(degreeLabel,0,0);
	focalBezierCurveGrid->addWidget(m_degreeSpinBox,0,1);
	focalBezierCurveBox->setLayout(focalBezierCurveGrid);	QVBoxLayout* layout = new QVBoxLayout();
	QGroupBox* laneRiesenfeldBox = new QGroupBox(tr("Evaluate Lane Riesenfeld"));
	QGridLayout* laneRiesenfeldGrid = new QGridLayout();
	m_doRiesenfeldButton = new QPushButton("Show Lane Riesenfeld Evaluation");
	connect(m_doRiesenfeldButton,SIGNAL(clicked()),this,SLOT(toggleRiesenfeld()));
	m_doRiesenfeldButton->setCheckable(true);
	m_riesenfeldIterationsM = new QSpinBox();
	m_riesenfeldDegreeN = new QSpinBox();
	connect(m_riesenfeldIterationsM,SIGNAL(valueChanged(int)),this,SLOT(changeLRIterations(int)));
	connect(m_riesenfeldDegreeN,SIGNAL(valueChanged(int)),this,SLOT(changeLRDegree(int)));
	QLabel* LRIterationsLabel = new QLabel("Iterations");
	QLabel* LRDegreeLabel = new QLabel("Degree");
	laneRiesenfeldGrid->addWidget(m_doRiesenfeldButton,0,0);
	laneRiesenfeldGrid->addWidget(LRIterationsLabel,1,0);
	laneRiesenfeldGrid->addWidget(LRDegreeLabel,2,0);
	laneRiesenfeldGrid->addWidget(m_riesenfeldIterationsM,1,1);
	laneRiesenfeldGrid->addWidget(m_riesenfeldDegreeN,2,1);
	laneRiesenfeldBox->setLayout(laneRiesenfeldGrid);
	layout->setSpacing(0);
	layout->addWidget(focalSplineGroupBox);
	layout->addWidget(focalBezierCurveBox);
	layout->addWidget(laneRiesenfeldBox);





	this->setLayout(layout);
	m_plane = Plane_ptr( new Plane( hpvec3(0.0f, 0.0f, 0.0f), hpvec3(0.0f, 0.0f, 1.0f) ));



}

FocalSplineForm::~FocalSplineForm() {

}

void FocalSplineForm::createFocalSpline(){
		m_currentPointIndex=-1;
		m_focalSpline =  FocalSpline_ptr(new FocalSpline());
		m_focalSpline->init(0);
		m_guiManager.insert(m_focalSpline,HP_LINE_MESH|HP_POINT_CLOUD);
		cout << " Creating Spline CAME HERE !!" << endl;
		m_focalSpline->addControlPoint(m_currentPointIndex);
		for(int i = 0 ; i < m_degreeSpinBox->value();i++){
			m_focalSpline->addControlPoint(m_currentPointIndex);
		}
		update();
		m_focalSplineInserted = true;

}

FocalSpline_ptr FocalSplineForm::getFocalSpline() const {
	return m_focalSpline;
}

void FocalSplineForm::setFocalSpline(FocalSpline_ptr focalSpline){
	m_focalSpline = focalSpline;
	m_focalSplineInserted = true;
}
void FocalSplineForm::reset(){
	m_focalSplineInserted = false;
	m_currentPointIndex = -1;
}

void FocalSplineForm::update(){
	m_guiManager.update(m_focalSpline);
}

void FocalSplineForm::handleSelection(){
	emit selected(this);
	m_currentPointIndex = -1;
}

void FocalSplineForm::handleSelection(int pointIndex){
	emit selected(this);
	m_currentPointIndex = pointIndex;
	m_degreeSpinBox->setValue(m_focalSpline->getDegree(pointIndex));
	std::cout <<"Selected Something Selection Indes Is: "<< m_currentPointIndex << endl;
}


void FocalSplineForm::handleDrag(Ray& ray){
	if(m_currentPointIndex >= 0){
		hpvec3 intersecPoint;
		if( m_plane->intersect( ray, intersecPoint ) ) {
			m_focalSpline->setControlPoint( m_currentPointIndex, intersecPoint );
			update();
		}
	}
}

void FocalSplineForm::changeDegree(int value){
  if(m_focalSpline && !m_addPointButton->isChecked()){
  int degree =m_focalSpline->getDegree(m_currentPointIndex);
  if (value > degree){
	  std::cout << "Increasing Degree.. selectionIndex is: " << m_currentPointIndex << endl;
	  m_focalSpline->addControlPoint(m_currentPointIndex);
	  update();
  }
  if (value < degree){
	  m_focalSpline->removeControlPoint(m_currentPointIndex,degree);
	  update();
  }
  }
}

void FocalSplineForm::changeDetail(int value){
	if(m_focalSpline){
		m_focalSpline->setDetail(value);
		update();
	}
}

void FocalSplineForm::activateControPointCreation(){

}


void FocalSplineForm::handleRay(Ray& ray){
	if (m_addPointButton->isChecked() && m_focalSpline){
		hpvec3 intersecPoint;
		if( m_plane->intersect( ray, intersecPoint ) ) {
			m_focalSpline->addControlPoint(intersecPoint);
		}
		m_degreeSpinBox->setValue(m_degreeSpinBox->value()+1);
	update();
	}
}

void FocalSplineForm::extendSpline(){
	m_focalSpline->extendSpline();
	update();
}

void FocalSplineForm::toggleRiesenfeld(){
		if(m_focalSpline){
	if (m_doRiesenfeldButton->isChecked())
		m_focalSpline->doLaneRiesenfeld(true);
		}
	if (!m_doRiesenfeldButton->isChecked()){
		m_focalSpline->doLaneRiesenfeld(false);
	}
	update();
}

void FocalSplineForm::changeLRIterations(int value){
	if(m_focalSpline){
		m_focalSpline->setLRIterations(value);
		update();
	}
}

void FocalSplineForm::changeLRDegree(int value){
	if(m_focalSpline){
		m_focalSpline->setLRDegree(value);
		update();
	}
}

void FocalSplineForm::toggleControlPolygon(){
		if(m_focalSpline){
	if (m_showControlPolygon->isChecked())
		m_focalSpline->showControlPolygon(false);

	if (!m_showControlPolygon->isChecked()){
		m_focalSpline->showControlPolygon(true);
		}
	update();
	}
}

void FocalSplineForm::toggleCircle(){
		if(m_focalSpline){
	if (m_showCircleButton->isChecked())
		m_focalSpline->showCircle(false);

	if (!m_showCircleButton->isChecked()){
		m_focalSpline->showCircle(true);
		}
	update();
	}
}



