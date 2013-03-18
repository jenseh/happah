#include "SimulationForm.h"


SimulationForm::SimulationForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
		m_guiManager(guiManager),
		m_simulationInserted(false),
		m_timeSlider(new Slider(tr("approximated time"))) {
	QPushButton* createButton = new QPushButton("create simulation");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_timeSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createSimulation()));
	connect(m_timeSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeTime(hpreal)));
	m_simulation = NULL;
	updateRanges();
}

SimulationForm::~SimulationForm() {}


void SimulationForm::changeTime(hpreal time) {
	updateRanges();
	updateSimulation();
}

void SimulationForm::createSimulation() {
	if( m_simulation == NULL ){
		m_simulation = DiscGearGrind_ptr(new DiscGearGrind(m_disc, m_gear));
	}
	if(!m_simulationInserted){
		m_simulation->runSimulation();
		m_guiManager.insert(m_simulation->getSimulationResult(m_timeSlider->getValue()));
		m_simulationInserted = true;
	}
}

DiscGearGrind_ptr SimulationForm::getSimulation() const {
	return m_simulation;
}

void SimulationForm::reset() {

}

void SimulationForm::setDisc(Disc_ptr disc){
	m_disc = disc;

}
void SimulationForm::setGear(SimpleGear_ptr gear){
	m_gear = gear;
}


void SimulationForm::setSimulation(DiscGearGrind_ptr simulation) {
	m_simulation = simulation;
	m_simulationInserted = true;

	updateRanges();
}

void SimulationForm::updateSimulation() {
	if(m_simulationInserted)
		m_guiManager.update(m_simulation->getSimulationResult(m_timeSlider->getValue()));
}


void SimulationForm::updateRanges() {
	m_timeSlider->setSliderValues(m_timeSlider->getValue(), 0.0, 1.0);
}
