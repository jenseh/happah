#include "happah/gui/forms/FocalSplineForm.h"

#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

FocalSplineForm::FocalSplineForm(GUIManager& guiManager,QWidget* parent)
	: Form(parent),m_guiManager(guiManager), m_focalSplineInserted(false),m_currentPointIndex(-1) {
	QPushButton* createButton = new QPushButton("Create Focal Spline");
	m_addPointButton = new QPushButton("Add ControlPoints");
	m_degreeSpinBox = new LabeledIntegerSpinBox("Degree");
	m_degreeSpinBox->setValue(2);
	m_detailSpinBox = new LabeledIntegerSpinBox("Detail");
	m_detailSpinBox->setValue(20);
	QPushButton* extendButton = new QPushButton("Extend Spline");
	connect(createButton,SIGNAL(clicked()),this,SLOT(createFocalSpline()));
	connect(m_degreeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeDegree(int)));
	connect(m_detailSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeDetail(int)));
	connect(extendButton,SIGNAL(clicked()),this,SLOT(extendSpline()));
	m_addPointButton->setCheckable(true);
	QVBoxLayout* layout = new QVBoxLayout();
	layout->setSpacing(0);

	layout->addWidget(m_degreeSpinBox);
	layout->addWidget(m_detailSpinBox);
	layout->addWidget(m_addPointButton);
	layout->addWidget(createButton);
	layout->addWidget(extendButton);

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
		for(int i = 0 ; i < m_degreeSpinBox->getValue();i++){
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
		std::cout << "Handling Ray" << endl;
		hpvec3 intersecPoint;
		if( m_plane->intersect( ray, intersecPoint ) ) {
			m_focalSpline->addControlPoint(intersecPoint);
		}
		m_degreeSpinBox->setValue(m_degreeSpinBox->getValue()+1);
	update();
	}
}

void FocalSplineForm::extendSpline(){
	m_focalSpline->extendSpline();
	update();
}





