#include "happah/gui/GUIState.h"

GUIState::GUIState(const char* name)
	: m_name(name) {}

GUIState::~GUIState() {}

const string& GUIState::getName() {
	return m_name;
}

