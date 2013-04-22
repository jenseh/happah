#include "happah/gui/ToolPanel.h"
#include <iostream>

ToolPanel::ToolPanel(GUIManager& guiManager, QWidget* parent)
	: QWidget(parent), 
		m_forms(new QStackedWidget(this)),
		m_bSplineCurveForm(new BSplineCurveForm(guiManager, m_forms)),
		m_discForm(new DiscForm(guiManager, m_forms)),
		m_focalSplineForm(new FocalSplineForm(guiManager,m_forms)),
		m_involuteGearForm(new InvoluteGearForm(guiManager, m_forms)),
		m_planeForm(new PlaneForm(guiManager, m_forms)),
		m_simpleGearForm(new SimpleGearForm(guiManager, m_forms)),
		m_simulationForm(new SimulationForm(guiManager, m_forms)),
		m_spherePatchForm(new SpherePatchForm(guiManager,m_forms)),
		m_toothProfileForm(new ToothProfileForm(guiManager, m_forms)),
		m_wormForm(new WormForm(guiManager, m_forms)) {
	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->setSpacing(2);
	QWidget* buttons = new QWidget(this);
	buttons->setLayout(buttonsLayout);

	add(buttonsLayout, "IG", m_involuteGearForm, 0, 0);
	connect(m_involuteGearForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "SG", m_simpleGearForm, 0, 1);
	connect(m_simpleGearForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "P", m_planeForm, 0, 2);
	connect(m_planeForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "D", m_discForm, 0, 3);
	connect(m_discForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "W", m_wormForm, 0, 4);
	connect(m_wormForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "S", m_simulationForm, 0, 5);
	connect(m_simulationForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "SP", m_spherePatchForm,1,0);
	connect(m_spherePatchForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "FS", m_focalSplineForm,1,1);
	connect(m_focalSplineForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "BSC", m_bSplineCurveForm,1,2);
	connect(m_bSplineCurveForm,SIGNAL(selected(Form*)),this,SLOT(handleFormSelectedEvent(Form*)));
	add(buttonsLayout, "TP", m_toothProfileForm, 1, 3);
	connect(m_toothProfileForm, SIGNAL(selected(Form*)), this, SLOT(handleFormSelectedEvent(Form*)));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(buttons);
	layout->addWidget(m_forms);
	setLayout(layout);

	setForm(m_involuteGearForm);

}

ToolPanel::~ToolPanel() {}

void ToolPanel::add(QGridLayout* buttonsLayout, const char* text, Form* form, int row, int column) {
	QPushButton* button = new QPushButton(tr(text), this);
	button->setFixedSize(40, 40);
	button->setCheckable(true);
	button->setAutoExclusive(true);
	buttonsLayout->addWidget(button, row, column);
	m_forms->addWidget(form);
	m_buttonsByForm[form] = button;
	m_formsByButton[button] = form;
	connect(button, SIGNAL(clicked()), this, SLOT(handleButtonClickedEvent()));

}

BSplineCurveForm* ToolPanel::getBSplineCurveForm() {
	return m_bSplineCurveForm;
}

InvoluteGearForm* ToolPanel::getInvoluteGearForm() {
	return m_involuteGearForm;
}

PlaneForm* ToolPanel::getPlaneForm() {
	return m_planeForm;
}

SimpleGearForm* ToolPanel::getSimpleGearForm() {
	return m_simpleGearForm;
}

DiscForm* ToolPanel::getDiscForm() {
	return m_discForm;
}

WormForm* ToolPanel::getWormForm() {
	return m_wormForm;
}
SimulationForm* ToolPanel::getSimulationForm() {
	return m_simulationForm;
}

SpherePatchForm* ToolPanel::getSpherePatchForm() {
	return m_spherePatchForm;
}

ToothProfileForm* ToolPanel::getToothProfileForm() {
	return m_toothProfileForm;
}

FocalSplineForm* ToolPanel::getFocalSplineForm() {
	return m_focalSplineForm;
}

void ToolPanel::handleButtonClickedEvent() {
	QPushButton* button = static_cast<QPushButton*>(sender());
	m_forms->setCurrentWidget(m_formsByButton[button]);
}

void ToolPanel::handleMouseClickEvent(Ray& ray) {
	Form* form = dynamic_cast<Form*>(m_forms->currentWidget());
	form->handleRay(ray);

}
void ToolPanel::handleDragEvent(Ray& ray){
	Form* form = dynamic_cast<Form*>(m_forms->currentWidget());
	form->handleDrag(ray);
}

void ToolPanel::setForm(Form* form) {
	m_forms->setCurrentWidget(form);

	m_buttonsByForm[form]->setChecked(true);
}

void ToolPanel::handleFormSelectedEvent(Form* form){
	setForm(form);
}


