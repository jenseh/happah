#ifndef SIMULATIONFORM_H_
#define SIMULATIONFORM_H_

#include "happah/geometries/Disc.h"
#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"
#include "happah/scene/GeometryFindVisitor.h"
#include "happah/simulations/DiscGearGrind.h"
#include "happah/simulations/Simulation.h"
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

class SimulationForm : public Form {
Q_OBJECT

public:
	SimulationForm(GUIManager& guiManager, QWidget* parent = 0);
	~SimulationForm();

	DiscGearGrind_ptr getSimulation() const;
	void reset();
	void setSimulation(DiscGearGrind_ptr simulation);

private:
	GUIManager& m_guiManager;
	DiscGearGrind_ptr m_simulation;
	bool m_simulationInserted;
	Slider* m_timeSlider;
	QComboBox* m_discSelector;
	QComboBox* m_gearSelector;

	void updateRanges();
	void updateSelectors();
	void updateSimulation();

private slots:
	void createSimulation();
	void changeTime(hpreal);

};

#endif /* SIMULATIONFORM_H_ */



