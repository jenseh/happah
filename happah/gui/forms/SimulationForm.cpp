#include "SimulationForm.h"

#include <QPushButton>
#include <QVBoxLayout>

SimulationForm::SimulationForm(SimulationListener& simulationListener, QWidget* parent)
	: Form(parent),
		m_timeSlider(new GearSlider(tr("approximated time"))),
		m_simulationInserted(false),
		m_simulationListener(simulationListener) {
	QPushButton* createButton = new QPushButton("create simulation");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_timeSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createSimulation()));
	connect(m_timeSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeTime(hpreal)));

	m_simulation = DiscGearGrind_ptr(new DiscGearGrind(Disc_ptr(new Disc), InvoluteGear_ptr(new InvoluteGear) ));
	updateRanges();
}

SimulationForm::~SimulationForm() {}


void SimulationForm::changeTime(hpreal time) {
	updateRanges();
	updateSimulation();
}

void SimulationForm::createSimulation() {
	if(!m_simulationInserted){
		m_simulation->runSimulation();
		m_simulationListener.insert(m_simulation->getSimulationResult(m_timeSlider->getValue()));
		m_simulationInserted = true;
	}
}

DiscGearGrind_ptr SimulationForm::getSimulation() const {
	return m_simulation;
}

void SimulationForm::reset() {

}


void SimulationForm::setSimulation(DiscGearGrind_ptr simulation) {
	m_simulation = simulation;
	m_simulationInserted = true;

	updateRanges();
}

void SimulationForm::updateSimulation() {
	if(m_simulationInserted)
		m_simulationListener.update(m_simulation->getSimulationResult(m_timeSlider->getValue()));
}

void SimulationForm::updateRanges() {
	m_timeSlider->setSliderValues(m_timeSlider->getValue(), m_timeSlider->getValue() / 2.0f, m_timeSlider->getValue() * 2.0f);
}
