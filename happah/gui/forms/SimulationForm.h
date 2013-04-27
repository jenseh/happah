#ifndef SIMULATIONFORM_H_
#define SIMULATIONFORM_H_

#include "happah/gui/forms/Form.h"
#include "happah/simulations/Simulation.h"
#include "happah/gui/SimulationTimer.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

class SimulationTimer;

class SimulationForm : public Form {
Q_OBJECT

public:
	SimulationForm(GUIManager& guiManager, QWidget* parent = 0);
	~SimulationForm();

	void reset() {};
	void handleSelection() {emit selected(this);}
signals:
		void selected(Form* form);
private:
	GUIManager& m_guiManager;
	bool m_simulationInserted;
	SimulationTimer* m_simulationTimer;

};

#endif /* SIMULATIONFORM_H_ */



