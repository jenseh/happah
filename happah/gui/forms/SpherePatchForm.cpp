#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/forms/SpherePatchForm.h"

SpherePatchForm::SpherePatchForm(GUIManager& guiManager, QWidget* parent)
	:Form(parent), m_guiManager(guiManager),
	 m_spherePatch(new SpherePatch(2,hpvec3(-1.0f,0.0f,0.0f),hpvec3(1.0f,0.0f,0.0f),hpvec3(0.0f,1.0f,0.0f))),
	 m_spherePatchInserted(false){

	QPushButton* createButton = new QPushButton("Create Spherical Patch");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton,SIGNAL(clicked()),this,SLOT(createSpherePatch()));

}

SpherePatchForm::~SpherePatchForm() {}

void SpherePatchForm::createSpherePatch(){
if(m_spherePatchInserted)
		m_spherePatch = SpherePatch_ptr(new SpherePatch(*m_spherePatch));
	m_guiManager.insert(m_spherePatch);
	m_spherePatchInserted = true;
}

void SpherePatchForm::updateSpherePatch(){
	if(m_spherePatchInserted)
		m_guiManager.update(m_spherePatch);
}

void SpherePatchForm::setSpherePatch(SpherePatch_ptr spherePatch){
	m_spherePatch = spherePatch;
	m_spherePatchInserted = true;
}

void SpherePatchForm::reset(){
	m_spherePatch = SpherePatch_ptr(new SpherePatch(2,hpvec3(-1.0f,0.0f,0.0f),hpvec3(1.0f,0.0f,0.0f),hpvec3(0.0f,1.0f,0.0f)));
	m_spherePatchInserted = false;
}

SpherePatch_ptr SpherePatchForm::getSpherePatch() const{
	return m_spherePatch;
}
