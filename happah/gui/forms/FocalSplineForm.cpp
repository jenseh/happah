#include "happah/gui/forms/FocalSplineForm.h"
#include <QPushButton>
#include <QVBoxLayout>

FocalSplineForm::FocalSplineForm(GUIManager& guiManager,QWidget* parent)
	: Form(parent),m_guiManager(guiManager), m_focalSplineInserted(false) {
	QPushButton* createButton = new QPushButton("create Focal Spline");
	connect(createButton,SIGNAL(clicked()),this,SLOT(createFocalSpline()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(createButton);
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
