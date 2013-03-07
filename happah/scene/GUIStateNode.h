#ifndef GUI_STATE_NODE_H
#define GUI_STATE_NODE_H

#include <memory>
#include <string>

using namespace std;

class GUIStateNode;
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

class InvoluteGearGUIStateNode;
typedef shared_ptr<InvoluteGearGUIStateNode> InvoluteGearGUIStateNode_ptr;

class PlaneGUIStateNode;
typedef shared_ptr<PlaneGUIStateNode> PlaneGUIStateNode_ptr;

class SimpleGearGUIStateNode;
typedef shared_ptr<SimpleGearGUIStateNode> SimpleGearGUIStateNode_ptr;

#include "happah/geometries/Mesh.h"
#include "happah/gui/forms/Form.h"
#include "happah/scene/Node.h"

class GUIStateNode : public Node {
public:
	GUIStateNode(string name);
	virtual ~GUIStateNode();

	void accept(GUIVisitor& guiVisitor);
	virtual shared_ptr<void> getData() const = 0;
	virtual Form* getForm() = 0;
	const string& getName() const;
	GUIStateNode_ptr getptr();
	TriangleMesh_ptr getTriangleMesh() const;
	void setName(const char* name);
	void setTriangleMesh(TriangleMesh_ptr triangleMesh);

private:
	string m_name;
	TriangleMesh_ptr m_triangleMesh;

};

#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/forms/InvoluteGearForm.h"

class InvoluteGearGUIStateNode : public GUIStateNode {
public:
	InvoluteGearGUIStateNode(InvoluteGear_ptr involuteGear, InvoluteGearForm* involuteGearForm, string name);
	~InvoluteGearGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();

private:
	InvoluteGear_ptr m_involuteGear;
	InvoluteGearForm* m_involuteGearForm;

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

#include "happah/geometries/SimpleGear.h"
#include "happah/gui/forms/SimpleGearForm.h"

class SimpleGearGUIStateNode : public GUIStateNode {
public:
	SimpleGearGUIStateNode(SimpleGear_ptr simpleGear, SimpleGearForm* simpleGearForm, string name);
	~SimpleGearGUIStateNode();

	shared_ptr<void> getData() const;
	Form* getForm();

private:
	SimpleGear_ptr m_simpleGear;
	SimpleGearForm* m_simpleGearForm;

};

#endif // GUI_STATE_NODE_H

