#ifndef GUI_STATE_H
#define GUI_STATE_H

#include <memory>
#include <string>

using namespace std;

class GUIState {
public:
	GUIState(const char* name);
	~GUIState();

	const string& getName();

private:
	string m_name;

};
typedef shared_ptr<GUIState> GUIState_ptr;

#endif // GUI_STATE_H
