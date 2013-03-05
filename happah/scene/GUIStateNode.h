#ifndef GUI_STATE_NODE_H
#define GUI_STATE_NODE_H

#include <string>

#include "happah/gui/forms/Form.h"
#include "happah/scene/Node.h"

class GUIStateNode : public Node {
public:
	GUIStateNode(const char* name);
	virtual ~GUIStateNode();

	virtual Form* getForm() = 0;
	const string& getName() const;
	void setName(const char* name);

private:
	string m_name;

};
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

class InvoluteGearForm;
#include "happah/geometries/InvoluteSpurGear.h"

class InvoluteGearGUIStateNode : public GUIStateNode {
public:
	InvoluteGearGUIStateNode(InvoluteGear_ptr involuteGear, InvoluteGearForm* involuteGearForm, const char* name);
	~InvoluteGearGUIStateNode();

	Form* getForm();

private:
	InvoluteGear_ptr m_involuteGear;
	InvoluteGearForm* m_involuteGearForm;

};
typedef shared_ptr<InvoluteGearGUIStateNode> InvoluteGearGUIStateNode_ptr;

#include "happah/gui/forms/InvoluteGearForm.h"

#endif // GUI_STATE_NODE_H
