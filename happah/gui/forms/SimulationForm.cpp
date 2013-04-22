#include "happah/gui/forms/SimulationForm.h"

SimulationForm::SimulationForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
	  m_guiManager(guiManager),
	  m_simulationInserted(false) {

	m_simulationTimer = new SimulationTimer(m_guiManager, 0.0, 1.0, 100, 40);

	QPushButton* createButton = new QPushButton("create simulation");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_simulationTimer);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createSimulation()));
}

SimulationForm::~SimulationForm() {}



void SimulationForm::createSimulation() {}

void SimulationForm::reset() {
	//TODO: either fill or remove this class
}


void SimulationForm::updateSimulation(hpreal time) {
	//TODO: either fill or remove this class
    //if(m_simulationInserted)
        //m_guiManager.update(m_simulation->getSimulationResult(time));
}
