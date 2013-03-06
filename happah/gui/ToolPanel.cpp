#include "happah/gui/ToolPanel.h"

ToolPanel::ToolPanel(GUIManager& guiManager, QWidget* parent)
	: QWidget(parent), 
		m_forms(new QStackedWidget(this)), 
		m_involuteGearForm(new InvoluteGearForm(guiManager, m_forms)),
		m_simpleGearForm(new SimpleGearForm(guiManager, m_forms)),
		m_planeForm(new PlaneForm(m_forms)) {
	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->setSpacing(2);
	QWidget* buttons = new QWidget(this);
	buttons->setLayout(buttonsLayout);

	add(buttonsLayout, "IG", m_involuteGearForm, 0, 0);
	add(buttonsLayout, "SG", m_simpleGearForm, 0, 1);
	add(buttonsLayout, "P", m_planeForm, 0, 2);

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

PlaneForm* ToolPanel::getPlaneForm() {
	return m_planeForm;
}

InvoluteGearForm* ToolPanel::getInvoluteGearForm() {
	return m_involuteGearForm;
}

void ToolPanel::handleButtonClickedEvent() {
	QPushButton* button = static_cast<QPushButton*>(sender());
	m_forms->setCurrentWidget(m_formsByButton[button]);
}

void ToolPanel::setForm(Form* form) {
	m_forms->setCurrentWidget(form);
	m_buttonsByForm[form]->setChecked(true);
}
