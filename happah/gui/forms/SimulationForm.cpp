#include "happah/gui/forms/SimulationForm.h"

SimulationForm::SimulationForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
	  m_guiManager(guiManager),
	  m_simulationInserted(false) {

	m_simulationTimer = new SimulationTimer(m_guiManager, 0.0, 1.0, 20, 200);

	QPushButton* createButton = new QPushButton("create simulation");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_simulationTimer);
	setLayout(layout);
}

SimulationForm::~SimulationForm() {}
