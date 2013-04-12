#include "SimulationTimer.h"

SimulationTimer::SimulationTimer(GUIManager& listener,
								hpreal minTime, hpreal maxTime,
								int ticksPerSimulation, hpreal tickTime):
								m_listener(listener),
								m_currentTime(minTime),
								m_minTime(minTime), m_maxTime(maxTime),
								m_deltaTick((maxTime - minTime)/(hpreal)ticksPerSimulation),
								m_startStopButton(new QPushButton("start")),
								m_tickTime(tickTime),
								m_timer(new QTimer(this)),
								m_timerIsRunning(false),
								m_timeSlider(new LabeledRealValuedSlider("Time", this)){

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_timeSlider);
	layout->addWidget(m_startStopButton);
	setLayout(layout);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(timerTick()));
	connect(m_timeSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeTime(hpreal)));
	connect(m_startStopButton, SIGNAL(clicked()), this, SLOT(startStopTimer()));

	updateSlider();
}

SimulationTimer::~SimulationTimer() {

}

void SimulationTimer::changeTime(hpreal time) {
	m_currentTime = time;
	m_listener.visitScene(*this);
}
void SimulationTimer::startStopTimer() {
	if( m_timerIsRunning ){
		m_timer->stop();
		m_timerIsRunning = false;
		m_startStopButton->setText("start");
	} else {
		m_timer->start(m_tickTime);
		m_timerIsRunning = true;
		m_startStopButton->setText("stop");
	}
}

void SimulationTimer::timerTick() {
	m_currentTime += m_deltaTick;
	if( m_currentTime > m_maxTime ){
		m_currentTime = m_minTime;
	}
	updateSlider();
	m_listener.visitScene(*this);
}

void SimulationTimer::updateSlider() {
	m_timeSlider->setSliderValues(m_currentTime, m_minTime, m_maxTime);
}

void SimulationTimer::visit(SimulationNode& simulationNode) {
	simulationNode.update(m_currentTime);
}
