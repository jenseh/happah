#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "happah/geometries/Disc.h"
#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/geometries/SpherePatch.h"
#include "happah/geometries/Worm.h"
#include "happah/simulations/Simulation.h"
#include "happah/simulations/DiscGearGrind.h"
#include "happah/scene/SceneVisitor.h"


class GUIManager {
public:
	virtual void insert(InvoluteGear_ptr involuteGear) = 0;
	virtual void insert(Plane_ptr plane) = 0;
	virtual void insert(SimpleGear_ptr simpleGear) = 0;
	virtual void insert(DiscGearGrindResult simulationResult) = 0;
	virtual void insert(Disc_ptr disc) = 0;
	virtual void insert(Worm_ptr worm) = 0;
	virtual void insert(SpherePatch_ptr SpherePatch)= 0;
	virtual void update(InvoluteGear_ptr involuteGear) = 0;
	virtual void update(Plane_ptr plane) = 0;
	virtual void update(SimpleGear_ptr simpleGear) = 0;
	virtual void update(DiscGearGrindResult simulationResult) = 0;
	virtual void update(Disc_ptr disc) = 0;
	virtual void update(Worm_ptr worm) = 0;
	virtual void update(SpherePatch_ptr SpherePatch)= 0;
	virtual void useInSimulation(Disc_ptr disc, TriangleMesh_ptr discMesh)= 0;
	virtual void useInSimulation(SimpleGear_ptr gear, TriangleMesh_ptr simpleGearMesh)= 0;
	virtual void visitScene(SceneVisitor& visitor)= 0;

};

#endif // GUI_MANAGER_H

