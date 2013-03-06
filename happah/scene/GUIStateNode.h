#ifndef GUI_STATE_NODE_H
#define GUI_STATE_NODE_H

#include <memory>
#include <string>

using namespace std;

class GUIStateNode;
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

class InvoluteGearGUIStateNode;
typedef shared_ptr<InvoluteGearGUIStateNode> InvoluteGearGUIStateNode_ptr;

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

class InvoluteGearGUIStateNode : public GUIStateNode, public enable_shared_from_this<InvoluteGearGUIStateNode> {
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

#endif // GUI_STATE_NODE_H
