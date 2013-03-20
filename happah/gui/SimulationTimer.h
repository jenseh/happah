#ifndef SIMULATIONTIMER_H_
#define SIMULATIONTIMER_H_
#include <QPushButton>
#include "happah/HappahTypes.h"
#include <glm/glm.hpp>
#include "happah/gui/Slider.h"
#include <QTimer>
#include <QLayout>

class SimulationTimerListener {
	public:
	virtual void updateSimulation(hpreal time)= 0;
};

class SimulationTimer: public QGroupBox {
	Q_OBJECT
	SimulationTimerListener& m_listener;
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
	SimulationTimer(SimulationTimerListener& listener, hpreal minTime, hpreal maxTime, int ticksPerSimulation, hpreal tickTime);
	virtual ~SimulationTimer();

	private slots:
		void changeTime(hpreal);
		void startStopTimer();
		void timerTick();

};

#endif /* SIMULATIONTIMER_H_ */
