#include "SimulationForm.h"
#include "happah-test/simulations/WormGearGrindTest.h" //TODO:remove

SimulationForm::SimulationForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
	  m_guiManager(guiManager),
	  m_simulationInserted(false) {

	m_simulationTimer = new SimulationTimer(m_guiManager, 0.0f, 1.0, 100, 50);

	QPushButton* createButton = new QPushButton("create simulation");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_simulationTimer);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createSimulation()));
	m_discGearGrind = NULL;
}

SimulationForm::~SimulationForm() {}



void SimulationForm::createSimulation() {
//	if( m_discGearGrind == NULL ){
//		m_discGearGrind = DiscGearGrind_ptr(new DiscGearGrind(m_disc, m_discMesh, m_gear, m_gearMesh));
//	}
//	if(!m_simulationInserted){
//		m_discGearGrind->runSimulation();
//        m_guiManager.insert(m_discGearGrind);
//        //m_guiManager.update(m_simulation->getSimulationResult(0.0f));
//		m_simulationInserted = true;
//	}


	//TODO: this is just Holger's playground to test the WormGearGrind simulation, the actual code is above.
	// Don't tell the boss..

	//WormGearGrindTest();
}

DiscGearGrind_ptr SimulationForm::getDiscGearGrind() const {
	return m_discGearGrind;
}

void SimulationForm::reset() {

}

void SimulationForm::setDisc(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh){
	m_disc = disc;
	m_discMesh = discMesh;
}
void SimulationForm::setGear(SimpleGear_ptr gear, TriangleMesh_ptr gearMesh){
	m_gear = gear;
	m_gearMesh = gearMesh;
    m_disc = DiscGenerator::generateDiscFrom(*m_gear);
	m_discMesh = TriangleMesh_ptr(m_disc->toTriangleMesh());
}

void SimulationForm::setDiscGearGrind(DiscGearGrind_ptr discGearGrind) {
	m_discGearGrind = discGearGrind;
}


void SimulationForm::updateSimulation(hpreal time) {
    //if(m_simulationInserted)
        //m_guiManager.update(m_simulation->getSimulationResult(time));
}
