#ifndef SIMULATIONFORM_H_
#define SIMULATIONFORM_H_

#include "happah/geometries/Disc.h"
#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/GearSlider.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/SimulationListener.h"
#include "happah/simulations/DiscGearGrind.h"
#include "happah/simulations/Simulation.h"

class SimulationForm : public Form {
	Q_OBJECT
	public:
		SimulationForm(SimulationListener& simulationListener, QWidget* parent = 0);
		~SimulationForm();

		DiscGearGrind_ptr getSimulation() const;
		void reset();
		void setSimulation(DiscGearGrind_ptr simulation);

	private:
		GearSlider* m_timeSlider;
		DiscGearGrind_ptr m_simulation;
		bool m_simulationInserted;
		SimulationListener& m_simulationListener;

		void updateRanges();
		void updateSimulation();

	private slots:
		void changeTime(hpreal);
		void createSimulation();

};

#endif /* SIMULATIONFORM_H_ */



