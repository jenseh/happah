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

#include "happah/geometries/Mesh.h"
#include "happah/gui/forms/Form.h"
#include "happah/scene/Node.h"

class GUIStateNode : public Node {
public:
	GUIStateNode(string name);
	virtual ~GUIStateNode();

	virtual Form* getForm() = 0;
	const string& getName() const;
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

	void accept(GUIVisitor& guiVisitor);
	Form* getForm();
	InvoluteGear_ptr getInvoluteGear() const;
	InvoluteGearGUIStateNode_ptr getptr();

private:
	InvoluteGear_ptr m_involuteGear;
	InvoluteGearForm* m_involuteGearForm;

};

#include "happah/geometries/Plane.h"
#include "happah/gui/forms/PlaneForm.h"

class PlaneGUIStateNode : public GUIStateNode {
public:
	PlaneGUIStateNode( Plane_ptr plane, PlaneForm* planeForm, string name );
	~PlaneGUIStateNode();

	void accept( GUIVisitor& guiVisitor );
	Form* getForm();
	Plane_ptr getPlane() const;
	PlaneGUIStateNode_ptr getptr();

private:
	Plane_ptr m_plane;
	PlaneForm* m_planeForm;
};

#endif // GUI_STATE_NODE_H
