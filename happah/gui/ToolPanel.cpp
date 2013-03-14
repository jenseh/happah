#include "happah/gui/ToolPanel.h"

ToolPanel::ToolPanel(GUIManager& guiManager, QWidget* parent)
	: QWidget(parent), 
		m_forms(new QStackedWidget(this)), 
		m_involuteGearForm(new InvoluteGearForm(guiManager, m_forms)),
		m_simpleGearForm(new SimpleGearForm(guiManager, m_forms)),
		m_discForm(new DiscForm(guiManager, m_forms)),
		m_planeForm(new PlaneForm(guiManager, m_forms)),
		m_simulationForm(new SimulationForm(guiManager, m_forms)),
		m_wormForm(new WormForm(guiManager, m_forms)){
	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->setSpacing(2);
	QWidget* buttons = new QWidget(this);
	buttons->setLayout(buttonsLayout);

	add(buttonsLayout, "IG", m_involuteGearForm, 0, 0);
	add(buttonsLayout, "SG", m_simpleGearForm, 0, 1);
	add(buttonsLayout, "P", m_planeForm, 0, 2);
	add(buttonsLayout, "D", m_discForm, 0, 3);
	add(buttonsLayout, "W", m_wormForm, 0, 4);
	add(buttonsLayout, "S", m_simulationForm, 0, 5);

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

void ToolPanel::handleButtonClickedEvent() {
	QPushButton* button = static_cast<QPushButton*>(sender());
	m_forms->setCurrentWidget(m_formsByButton[button]);
}

void ToolPanel::setForm(Form* form) {
	m_forms->setCurrentWidget(form);
	m_buttonsByForm[form]->setChecked(true);
}
