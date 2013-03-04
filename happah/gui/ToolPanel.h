#ifndef TOOL_PANEL_H
#define TOOL_PANEL_H

#include <QStackedWidget>
#include <QWidget>

#include "happah/scene/SceneManager.h"

class ToolPanel : public QWidget {

public:
	ToolPanel(SceneManager& sceneManager, QWidget* parent = 0);
	~ToolPanel();

private:
	QStackedWidget* m_forms;

};

#endif //TOOL_PANEL_H
