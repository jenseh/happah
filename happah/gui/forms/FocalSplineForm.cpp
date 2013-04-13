#include "happah/gui/forms/FocalSplineForm.h"
#include <QPushButton>
#include <QVBoxLayout>

FocalSplineForm::FocalSplineForm(GUIManager& guiManager,QWidget* parent)
	: Form(parent),m_guiManager(guiManager), m_focalSplineInserted(false),m_currentPointIndex(-1) {
	QPushButton* createButton = new QPushButton("create Focal Spline");
	connect(createButton,SIGNAL(clicked()),this,SLOT(createFocalSpline()));
	QPushButton* updateButton= new QPushButton("update Spline");
	connect(updateButton,SIGNAL(clicked()),this,SLOT(update()));
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(createButton);
	layout->addWidget(updateButton);
	this->setLayout(layout);



}

FocalSplineForm::~FocalSplineForm() {

}

void FocalSplineForm::createFocalSpline(){

		m_focalSpline =  FocalSpline_ptr(new FocalSpline());
		m_guiManager.insert(m_focalSpline,HP_LINE_MESH|HP_POINT_CLOUD);
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
	m_focalSpline->update();
	m_guiManager.update(m_focalSpline);
}

void FocalSplineForm::handleSelection(){
	emit selected(this);
	std::cout << "HANDLED SELECTION "<< endl;
	m_currentPointIndex = -1;
}

void FocalSplineForm::handleSelection(int pointIndex){
	emit selected(this);
	m_currentPointIndex = pointIndex;
	std::cout<< "CURRENT INDEX : "<< pointIndex << endl;
}
void FocalSplineForm::handleDrag(float dx,float dy){
	if(m_currentPointIndex >= 0){
	hpvec3 point = m_focalSpline->getCartesianControlPoint(m_currentPointIndex);
	if (dx < 0)
	point.x = point.x+0.1;
	if (dx > 0)
	point.x = point.x-0.1;
	if (dy > 0)
	point.y = point.y+0.1;
	if (dy < 0)
	point.y = point.y-0.1;
	if (point.y < 0.0f)
	point.y = 0.0f;
	m_focalSpline->setCartesianControlPoint(m_currentPointIndex,point);
	update();
	}
}








