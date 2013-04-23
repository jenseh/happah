#ifndef GUI_STATE_NODE_H
#define GUI_STATE_NODE_H

#include <memory>
#include <string>

using namespace std;

class GUIStateNode;
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

class BSplineCurveGUIStateNode;
typedef shared_ptr<BSplineCurveGUIStateNode> BSplineCurveGUIStateNode_ptr;

class DiscGUIStateNode;
typedef shared_ptr<DiscGUIStateNode> DiscGUIStateNode_ptr;

class DiscGearGrindGUIStateNode;
typedef shared_ptr<DiscGearGrindGUIStateNode> DiscGearGrindGUIStateNode_ptr;

class FocalSplineGUIStateNode;
typedef shared_ptr<FocalSplineGUIStateNode> FocalSplineGUIStateNode_ptr;

class InvoluteGearGUIStateNode;
typedef shared_ptr<InvoluteGearGUIStateNode> InvoluteGearGUIStateNode_ptr;

class PlaneGUIStateNode;
typedef shared_ptr<PlaneGUIStateNode> PlaneGUIStateNode_ptr;

class SimpleGearGUIStateNode;
typedef shared_ptr<SimpleGearGUIStateNode> SimpleGearGUIStateNode_ptr;

class SpherePatchGUIStateNode;
typedef shared_ptr<SpherePatchGUIStateNode> SpherePatchGUIStateNode_ptr;

class ToothProfileGUIStateNode;
typedef shared_ptr<ToothProfileGUIStateNode> ToothProfileGUIStateNode_ptr;

class WormGUIStateNode;
typedef shared_ptr<WormGUIStateNode> WormGUIStateNode_ptr;

class WormGearGrindGUIStateNode;
typedef shared_ptr<WormGearGrindGUIStateNode> WormGearGrindGUIStateNode_ptr;

#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include "happah/gui/context-menus/ContextMenu.h"
#include "happah/gui/forms/Form.h"
#include "happah/scene/Node.h"
#include "happah/scene/SelectListener.h"
#include "happah/scene/ConnectListener.h"

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
	LineMesh_ptr getLineMesh() const;
	PointCloud_ptr getPointCloud() const;
	void setName(const char* name);
	void setTriangleMesh(TriangleMesh_ptr triangleMesh);
	void setLineMesh(LineMesh_ptr lineMesh);
	void setPointCloud(PointCloud_ptr pointCloud);
	void 	registerConnectListener(ConnectListener* selectListener);
	void	removeConnectListener(ConnectListener* selectListener);
	void 	triggerConnectionEvent();
	class GUISelectListener : public SelectListener {
	public:
		GUISelectListener(GUIStateNode& guiStateNode) : m_guiStateNode(guiStateNode){}
		~GUISelectListener(){}

		virtual void handleSelectEvent();
		virtual void handleSelectEvent(int pointIndex);
		virtual void handleDeselectEvent();

	private:
		GUIStateNode& m_guiStateNode;
	};

	class GUIConnectListener : public ConnectListener{
	public:
		GUIConnectListener(GUIStateNode& guiStateNode) : m_guiStateNode(guiStateNode){}
		~GUIConnectListener(){}
		virtual void handleConnectionEvent();
	private:
		GUIStateNode& m_guiStateNode;
	};

	virtual GUISelectListener* getSelectListener() { return &m_selectListener; }
	virtual GUIConnectListener* getConnectListener() {return &m_connectListener; }
private:
	GUISelectListener m_selectListener;
	GUIConnectListener m_connectListener;
	list<ConnectListener*> m_connectListeners;
	string m_name;
	TriangleMesh_ptr m_triangleMesh;
	LineMesh_ptr m_lineMesh;
	PointCloud_ptr m_pointCloud;
};

#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/context-menus/BSplineCurveContextMenu.h"
#include "happah/gui/forms/BSplineCurveForm.h"

class BSplineCurveGUIStateNode : public GUIStateNode {
public:
	BSplineCurveGUIStateNode( BSplineCurve_ptr curve, BSplineCurveForm* bSplineCurveForm, BSplineCurveContextMenu* bSplineCurveContextMenu, string name);
	~BSplineCurveGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();
private:
	BSplineCurve_ptr m_curve;
	BSplineCurveContextMenu* m_bSplineCurveContextMenu;
	BSplineCurveForm* m_bSplineCurveForm;
};

#include "happah/geometries/FocalSpline.h"
#include "happah/gui/forms/FocalSplineForm.h"

class FocalSplineGUIStateNode : public GUIStateNode{
public:
	FocalSplineGUIStateNode(FocalSpline_ptr focalSpline, FocalSplineForm* focalSplineForm, string name);
	~FocalSplineGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();
	FocalSpline_ptr getFocalSpline() const;
private:
	FocalSpline_ptr m_focalSpline;
	FocalSplineForm* m_focalSplineForm;
};

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/gui/context-menus/InvoluteGearContextMenu.h"
#include "happah/gui/forms/InvoluteGearForm.h"

class InvoluteGearGUIStateNode : public GUIStateNode {
public:
	InvoluteGearGUIStateNode(InvoluteGear_ptr involuteGear, InvoluteGearForm* involuteGearForm, InvoluteGearContextMenu* contextMenu, string name);
	~InvoluteGearGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();
	InvoluteGear_ptr getInvoluteGear()const;

private:
	InvoluteGear_ptr m_involuteGear;
	InvoluteGearContextMenu* m_involuteGearContextMenu;
	InvoluteGearForm* m_involuteGearForm;
};

#include "happah/geometries/Plane.h"
#include "happah/gui/context-menus/PlaneContextMenu.h"
#include "happah/gui/forms/PlaneForm.h"

class PlaneGUIStateNode : public GUIStateNode {
public:
	PlaneGUIStateNode(Plane_ptr plane, PlaneForm* planeForm, PlaneContextMenu* contextMenu, string name);
	~PlaneGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();

private:
	Plane_ptr m_plane;
	PlaneContextMenu* m_planeContextMenu;
	PlaneForm* m_planeForm;
};

#include "happah/gui/context-menus/SimpleGearContextMenu.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/gui/forms/SimpleGearForm.h"

class SimpleGearGUIStateNode : public GUIStateNode {
public:
	SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, SimpleGearContextMenu* simpleGearContextMenu, string name);
	~SimpleGearGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();
	SimpleGear_ptr getSimpleGear()const;

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
	SurfaceOfRevolution_ptr getSurfaceOfRevolution()const;

private:
	SurfaceOfRevolution_ptr m_surfaceOfRevolution;
	DiscForm* m_discForm;
	DiscContextMenu* m_discContextMenu;

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

#include "happah/geometries/gears/ToothProfile.h"
#include "happah/gui/context-menus/ToothProfileContextMenu.h"
#include "happah/gui/forms/ToothProfileForm.h"

class ToothProfileGUIStateNode : public GUIStateNode {
public:
	ToothProfileGUIStateNode(ToothProfile_ptr toothProfile, ToothProfileForm* toothProfileForm, ToothProfileContextMenu* toothProfileContextMenu, string name);
	~ToothProfileGUIStateNode();
	
	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();
private:
	ToothProfile_ptr m_toothProfile;
	ToothProfileContextMenu* m_toothProfileContextMenu;
	ToothProfileForm* m_toothProfileForm;
};

#include "happah/gui/context-menus/SimulationContextMenu.h"
#include "happah/gui/forms/SimulationForm.h"
#include "happah/simulations/WormGearGrind.h"


class WormGearGrindGUIStateNode : public GUIStateNode {
public:
	WormGearGrindGUIStateNode(WormGearGrind_ptr wormGearGrind, SimulationForm* simulationForm, SimulationContextMenu* simulationContextMenu, string name);
	~WormGearGrindGUIStateNode();

	ContextMenu* getContextMenu() const;
	shared_ptr<void> getData() const;
	Form* getForm();

private:
	WormGearGrind_ptr m_wormGearGrind;
	SimulationForm* m_simulationForm;
	SimulationContextMenu* m_simulationContextMenu;
};

#include "happah/geometries/gears/Worm.h"
#include "happah/gui/forms/WormForm.h"

class WormGUIStateNode : public GUIStateNode {
public:
	WormGUIStateNode(Worm_ptr worm, WormForm* wormForm, string name);
	~WormGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();
	Worm_ptr getWorm()const;

private:
	Worm_ptr m_worm;
	WormForm* m_wormForm;

};

#endif // GUI_STATE_NODE_H

