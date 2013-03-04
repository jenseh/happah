#include "happah/scene/GUIStateNode.h"

GUIStateNode::GUIStateNode(GUIState_ptr guiState)
	: m_guiState(guiState) {}

GUIStateNode::~GUIStateNode() {}

GUIState_ptr GUIStateNode::getGUIState() {
	return m_guiState;
}

