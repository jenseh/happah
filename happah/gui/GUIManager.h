#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "happah/HappahConstants.h"
#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/FocalSpline.h"
#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/SpherePatch.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/geometries/gears/Worm.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimulationVisitor.h"
#include "happah/simulations/DiscGearGrind.h"


class GUIManager {
public:
	virtual void createDiscGearGrind(SimpleGear_ptr gear)= 0;
	virtual void generateDisc(CylindricalGear_ptr cylindricalGear) = 0;
	virtual void insert(BSplineCurve_ptr bSplineCurve,hpuint drawMode) = 0;
	virtual void insert(SurfaceOfRevolution_ptr disc,hpuint drawMode) = 0;
	//virtual void insert(DiscGearGrindResult simulationResult) = 0;
	virtual void insert(DiscGearGrind_ptr discGearGrind) = 0;
	virtual void insert(FocalSpline_ptr focalSpline,hpuint drawMode)= 0;
	virtual void insert(InvoluteGear_ptr involuteGear,hpuint drawMode) = 0;
	virtual void insert(Plane_ptr plane, BSplineCurve_ptr curve) = 0;
	virtual void insert(Plane_ptr plane, hpuint drawMode) = 0;
	virtual void insert(SimpleGear_ptr simpleGear, hpuint drawMode) = 0;
	virtual void insert(SpherePatch_ptr spherePatch, hpuint drawMode) = 0;
	virtual void insert(Worm_ptr worm, hpuint drawMode) = 0;
	virtual void update(BSplineCurve_ptr bSplineCurve) = 0;
	virtual void update(FocalSpline_ptr focalSpline) = 0;
	//virtual void update(DiscGearGrindResult simulationResult) = 0;
	virtual void update(SurfaceOfRevolution_ptr disc) = 0;
	virtual void update(InvoluteGear_ptr involuteGear) = 0;
	virtual void update(Plane_ptr plane) = 0;
	virtual void update(SimpleGear_ptr simpleGear) = 0;
	virtual void update(SpherePatch_ptr spherePatch) = 0;
	virtual void update(Worm_ptr worm) = 0;
	virtual void useForBSpline(Plane_ptr plane) = 0;
	virtual void useInSimulation(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh)= 0;
	virtual void useInSimulation(SimpleGear_ptr gear, TriangleMesh_ptr simpleGearMesh)= 0;
	virtual void visitScene(SceneVisitor& visitor)= 0;
	virtual void visitScene(SimulationVisitor& visitor)= 0;
	virtual Plane_ptr getParentPlane(BSplineCurve_ptr bSplineCurve) = 0;

};

#endif // GUI_MANAGER_H

