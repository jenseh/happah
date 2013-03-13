#ifndef SIMULATIONFORM_H_
#define SIMULATIONFORM_H_

#include "happah/simulations/Simulation.h"
#include "happah/gui/GearSlider.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/SimulationListener.h"

class SimulationForm : public Form {
	Q_OBJECT
	public:
		SimulationForm(SimulationListener& simulationListener, QWidget* parent = 0);
		~SimulationForm();

		Simulation_ptr getSimulation() const;
		void reset();
		void setSimulation(Simulation_ptr simulation);

	private:
		GearSlider* m_timeSlider;
		Simulation_ptr m_simulation;
		bool m_simulationInserted;
		SimulationListener& m_simulationListener;

		void updateRanges();
		void updateSimulation();

	private slots:
		void changeTime(hpreal);
		void createSimulation();

};

#endif /* SIMULATIONFORM_H_ */



