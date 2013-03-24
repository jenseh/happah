#ifndef SIMULATIONFORM_H_
#define SIMULATIONFORM_H_

#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"
#include "happah/scene/GeometryFindVisitor.h"
#include "happah/simulations/DiscGearGrind.h"
#include "happah/simulations/Simulation.h"
#include "happah/gui/SimulationTimer.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

class SimulationForm : public Form, public SimulationTimerListener {
Q_OBJECT

public:
	SimulationForm(GUIManager& guiManager, QWidget* parent = 0);
	~SimulationForm();

	DiscGearGrind_ptr getSimulation() const;
	void reset();
	void setSimulation(DiscGearGrind_ptr simulation);
	void setDisc(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh);
	void setGear(SimpleGear_ptr gear, TriangleMesh_ptr gearMesh);

private:

	SurfaceOfRevolution_ptr m_disc;
	TriangleMesh_ptr m_discMesh;
	SimpleGear_ptr m_gear;
	TriangleMesh_ptr m_gearMesh;
	GUIManager& m_guiManager;
	DiscGearGrind_ptr m_simulation;
	bool m_simulationInserted;
	SimulationTimer* m_simulationTimer;

	void updateSimulation(hpreal time);

private slots:
	void createSimulation();

};

#endif /* SIMULATIONFORM_H_ */



