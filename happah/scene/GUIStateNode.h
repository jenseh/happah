#ifndef GUI_STATE_NODE_H
#define GUI_STATE_NODE_H

#include <memory>
#include <string>

using namespace std;

class GUIStateNode;
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

class BSplineCurveGUIStateNode;
typedef shared_ptr<BSplineCurveGUIStateNode> BSplineCurveGUIStateNode_ptr;

class InvoluteGearGUIStateNode;
typedef shared_ptr<InvoluteGearGUIStateNode> InvoluteGearGUIStateNode_ptr;

class PlaneGUIStateNode;
typedef shared_ptr<PlaneGUIStateNode> PlaneGUIStateNode_ptr;

class SimpleGearGUIStateNode;
typedef shared_ptr<SimpleGearGUIStateNode> SimpleGearGUIStateNode_ptr;

class DiscGUIStateNode;
typedef shared_ptr<DiscGUIStateNode> DiscGUIStateNode_ptr;

class DiscGearGrindGUIStateNode;
typedef shared_ptr<DiscGearGrindGUIStateNode> DiscGearGrindGUIStateNode_ptr;

class WormGUIStateNode;
typedef shared_ptr<WormGUIStateNode> WormGUIStateNode_ptr;

class SpherePatchGUIStateNode;
typedef shared_ptr<SpherePatchGUIStateNode> SpherePatchGUIStateNode_ptr;

#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/forms/Form.h"
#include "happah/scene/Node.h"

class GUIStateNode : public Node {
public:
	GUIStateNode(string& name);
	virtual ~GUIStateNode();

	void accept(GUIVisitor& guiVisitor);
	virtual ContextMenu* getContextMenu() const;
	virtual shared_ptr<void> getData() const = 0;
	virtual Form* getForm() = 0;
	const string& getName() const;
	GUIStateNode_ptr getptr();
	TriangleMesh_ptr getTriangleMesh() const;
	void setName(const char* name);
	void setTriangleMesh(TriangleMesh_ptr triangleMesh);
	void setLineMesh(LineMesh_ptr lineMesh);
	void setPointCloud(PointCloud_ptr pointCloud);


private:
	string m_name;
	TriangleMesh_ptr m_triangleMesh;
	LineMesh_ptr m_lineMesh;
	PointCloud_ptr m_pointCloud;


};

#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/forms/BSplineCurveForm.h"

class BSplineCurveGUIStateNode : public GUIStateNode {
public:
	BSplineCurveGUIStateNode( BSplineCurve_ptr curve, BSplineCurveForm* bSplineCurveForm, string name);
	~BSplineCurveGUIStateNode();
	
	shared_ptr<void> getData() const;
	Form* getForm();
private:
	BSplineCurve_ptr m_curve;
	BSplineCurveForm* m_bSplineCurveForm;
};

#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/context-menus/InvoluteGearContextMenu.h"
#include "happah/gui/forms/InvoluteGearForm.h"

class InvoluteGearGUIStateNode : public GUIStateNode {
public:
	InvoluteGearGUIStateNode(InvoluteGear_ptr involuteGear, InvoluteGearForm* involuteGearForm, InvoluteGearContextMenu* contextMenu, string name);
	~InvoluteGearGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();

private:
	InvoluteGear_ptr m_involuteGear;
	InvoluteGearForm* m_involuteGearForm;
	InvoluteGearContextMenu* m_involuteGearContextMenu;
};

#include "happah/geometries/Plane.h"
#include "happah/gui/forms/PlaneForm.h"

class PlaneGUIStateNode : public GUIStateNode {
public:
	PlaneGUIStateNode(Plane_ptr plane, PlaneForm* planeForm, string name);
	~PlaneGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();

private:
	Plane_ptr m_plane;
	PlaneForm* m_planeForm;
};

#include "happah/gui/context-menus/SimpleGearContextMenu.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/gui/forms/SimpleGearForm.h"

class SimpleGearGUIStateNode : public GUIStateNode {
public:
	SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, SimpleGearContextMenu* simpleGearContextMenu,  string name);
	~SimpleGearGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();

private:
	SimpleGear_ptr m_simpleGear;
	SimpleGearContextMenu* m_simpleGearContextMenu;
	SimpleGearForm* m_simpleGearForm;

};

#include "happah/gui/context-menus/SimulationContextMenu.h"
#include "happah/gui/forms/SimulationForm.h"
#include "happah/simulations/DiscGearGrind.h"


class DiscGearGrindGUIStateNode : public GUIStateNode {
public:
	DiscGearGrindGUIStateNode(DiscGearGrind_ptr discGearGrind, SimulationForm* simulationForm, SimulationContextMenu* simulationContextMenu, string name);
	~DiscGearGrindGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();

private:
	DiscGearGrind_ptr m_discGearGrind;
	SimulationForm* m_simulationForm;
	SimulationContextMenu* m_simulationContextMenu;
};


#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/gui/forms/DiscForm.h"
#include "happah/gui/context-menus/DiscContextMenu.h"

class DiscGUIStateNode : public GUIStateNode {
public:
    DiscGUIStateNode(SurfaceOfRevolution_ptr disc, DiscForm* discForm, DiscContextMenu* discContextMenu, string name);
	~DiscGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();

private:
    SurfaceOfRevolution_ptr m_disc;
	DiscForm* m_discForm;
	DiscContextMenu* m_discContextMenu;

};


#include "happah/geometries/Worm.h"
#include "happah/gui/forms/WormForm.h"

class WormGUIStateNode : public GUIStateNode {
public:
	WormGUIStateNode(Worm_ptr worm, WormForm* wormForm, string name);
	~WormGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();

private:
	Worm_ptr m_worm;
	WormForm* m_wormForm;

};

#include "happah/geometries/SpherePatch.h"
#include "happah/gui/forms/SpherePatchForm.h"

class SpherePatchGUIStateNode : public GUIStateNode {
public:
	SpherePatchGUIStateNode(SpherePatch_ptr spherePatch, SpherePatchForm* spherePatchForm, string name);
	~SpherePatchGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();

private:
	SpherePatch_ptr m_spherePatch;
	SpherePatchForm* m_spherePatchForm;

};



#endif // GUI_STATE_NODE_H

