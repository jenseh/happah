#ifndef TOOL_PANEL_H
#define TOOL_PANEL_H

#include <QStackedWidget>
#include <QWidget>

#include "happah/gui/GUIManager.h"

class ToolPanel : public QWidget {

public:
	ToolPanel(GUIManager& guiManager, QWidget* parent = 0);
	~ToolPanel();

private:
	QStackedWidget* m_forms;

};

#endif //TOOL_PANEL_H
