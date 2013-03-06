#ifndef TOOL_PANEL_H
#define TOOL_PANEL_H

#include <QStackedWidget>
#include <QWidget>

#include "happah/gui/GUIManager.h"
#include "happah/gui/forms/InvoluteGearForm.h"

class ToolPanel : public QWidget {

public:
	ToolPanel(GUIManager& guiManager, QWidget* parent = 0);
	~ToolPanel();

	InvoluteGearForm* getInvoluteGearForm();
	void setForm(Form* form);	

private:
	QStackedWidget* m_forms;
	InvoluteGearForm* m_involuteGearForm;

};

#endif //TOOL_PANEL_H
