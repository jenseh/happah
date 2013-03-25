#ifndef SIMULATIONTIMER_H_
#define SIMULATIONTIMER_H_
#include <QPushButton>
#include "happah/HappahTypes.h"
#include <glm/glm.hpp>
#include "happah/gui/Slider.h"
#include <QTimer>
#include <QLayout>

#include "happah/gui/GUIManager.h"
#include "happah/scene/SimulationNode.h"
#include "happah/scene/SimulationVisitor.h"


class SimulationTimer: public QGroupBox, public SimulationVisitor {
	Q_OBJECT
	GUIManager& m_listener;
	hpreal m_currentTime;
	hpreal m_deltaTick; // delta time passed per tick
	hpreal m_minTime,m_maxTime;
	QPushButton* m_startStopButton;
	hpreal m_tickTime;// how often in ms
	QTimer* m_timer;
	bool m_timerIsRunning;
	Slider* m_timeSlider;

	void updateSlider();

public:
	SimulationTimer(GUIManager& listener, hpreal minTime, hpreal maxTime, int ticksPerSimulation, hpreal tickTime);
	virtual ~SimulationTimer();

	void visit(SimulationNode& simulationNode);

	private slots:
		void changeTime(hpreal);
		void startStopTimer();
		void timerTick();

};

#endif /* SIMULATIONTIMER_H_ */
