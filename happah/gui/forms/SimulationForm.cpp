#include "SimulationForm.h"


SimulationForm::SimulationForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
	  m_guiManager(guiManager),
	  m_simulationInserted(false) {

	m_simulationTimer = new SimulationTimer(*this,0.0f, 1.0f, 20, 200);

	QPushButton* createButton = new QPushButton("create simulation");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_simulationTimer);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createSimulation()));
	m_simulation = NULL;
}

SimulationForm::~SimulationForm() {}


void SimulationForm::createSimulation() {
	if( m_simulation == NULL ){
		m_simulation = DiscGearGrind_ptr(new DiscGearGrind(m_disc, m_discMesh, m_gear, m_gearMesh));
	}
	if(!m_simulationInserted){
		m_simulation->runSimulation();
		m_guiManager.update(m_simulation->getSimulationResult(0.0f));
		m_simulationInserted = true;
	}
}

DiscGearGrind_ptr SimulationForm::getSimulation() const {
	return m_simulation;
}

void SimulationForm::reset() {

}

void SimulationForm::setDisc(Disc_ptr disc, TriangleMesh_ptr discMesh){
	m_disc = disc;
	m_discMesh = discMesh;
}
void SimulationForm::setGear(SimpleGear_ptr gear, TriangleMesh_ptr gearMesh){
	m_gear = gear;
	m_gearMesh = gearMesh;
	m_disc = Disc_ptr(new GearProfileDisc(*m_gear));
	m_discMesh = TriangleMesh_ptr(m_disc->toTriangleMesh());
}


void SimulationForm::setSimulation(DiscGearGrind_ptr simulation) {
	m_simulation = simulation;
	m_simulationInserted = true;
}

void SimulationForm::updateSimulation(hpreal time) {
	if(m_simulationInserted)
		m_guiManager.update(m_simulation->getSimulationResult(time));
}
