#ifndef SIMULATION_H
#define SIMULATION_H

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/Geometry.h"
#include "happah/transformations/RigidAffineTransformation.h"

class SimulationResult {
public:
	Geometry_ptr m_gear;
	vector<hpcolor>* m_gearColor;
	TriangleMesh_ptr m_gearMesh;
	Geometry_ptr m_tool;
	TriangleMesh_ptr m_toolMesh;
	RigidAffineTransformation m_toolTransformation;
	RigidAffineTransformation m_gearTransformation;


	SimulationResult(vector<hpcolor>* gearColor, TriangleMesh_ptr gearMesh, TriangleMesh_ptr toolMesh):
		m_gearMesh(gearMesh),
		m_toolMesh(toolMesh),
		m_gearColor(gearColor){

	}
};

class Simulation
{
public:
	Simulation();
	virtual ~Simulation();

  virtual void runSimulation() = 0;
  virtual SimulationResult getSimulationResult(double time) = 0;
};

typedef std::shared_ptr<Simulation> Simulation_ptr;

#endif // SIMULATION_H
