#ifndef GUI_STATE_NODE_H
#define GUI_STATE_NODE_H

#include <string>

#include "happah/gui/GUIState.h"
#include "happah/scene/Node.h"

class GUIStateNode : public Node {
public:
	GUIStateNode(GUIState_ptr guiState);
	~GUIStateNode();

	GUIState_ptr getGUIState();

private:
	GUIState_ptr m_guiState;

};
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

#endif // GUI_STATE_NODE_H
