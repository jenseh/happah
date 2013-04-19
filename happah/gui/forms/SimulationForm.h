#ifndef SIMULATIONFORM_H_
#define SIMULATIONFORM_H_

#include "happah/geometries/DiscGenerator.h"
#include "happah/geometries/gears/CylindricalGear.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/gui/forms/Form.h"
#include "happah/simulations/DiscGearGrind.h"
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

	DiscGearGrind_ptr getDiscGearGrind() const;
	void reset();
	void setDisc(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh);
	void setGear(SimpleGear_ptr gear, TriangleMesh_ptr gearMesh);
	void setDiscGearGrind(DiscGearGrind_ptr discGearGrind);
	void handleSelection() {emit selected(this);}
signals:
		void selected(Form* form);
private:

	SurfaceOfRevolution_ptr m_disc;
	TriangleMesh_ptr m_discMesh;
	SimpleGear_ptr m_gear;
	TriangleMesh_ptr m_gearMesh;
	GUIManager& m_guiManager;
	DiscGearGrind_ptr m_discGearGrind;
	bool m_simulationInserted;
	SimulationTimer* m_simulationTimer;

	void updateSimulation(hpreal time);

private slots:
	void createSimulation();

};

#endif /* SIMULATIONFORM_H_ */



