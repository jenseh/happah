#ifndef TOOL_PANEL_H
#define TOOL_PANEL_H

#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <unordered_map>

using namespace std;

#include "happah/gui/GUIManager.h"
#include "happah/gui/forms/InvoluteGearForm.h"
#include "happah/gui/forms/SimpleGearForm.h"
#include "happah/gui/forms/PlaneForm.h"
#include "happah/gui/forms/DiscForm.h"
#include "happah/gui/forms/SimulationForm.h"
#include "happah/gui/forms/SpherePatchForm.h"
#include "happah/gui/forms/WormForm.h"

class ToolPanel : public QWidget {
Q_OBJECT

public:
	ToolPanel(GUIManager& guiManager, QWidget* parent = 0);
	~ToolPanel();

	InvoluteGearForm* getInvoluteGearForm();
	PlaneForm* getPlaneForm();
	SimpleGearForm* getSimpleGearForm();
	DiscForm* getDiscForm();
	WormForm* getWormForm();
	SpherePatchForm* getSpherePatchForm();
	void setForm(Form* form);	

private:
	unordered_map<Form*,QPushButton*> m_buttonsByForm;
	QStackedWidget* m_forms;
	unordered_map<QPushButton*,Form*> m_formsByButton;
	InvoluteGearForm* m_involuteGearForm;
	SimpleGearForm* m_simpleGearForm;
	DiscForm* m_discForm;
	PlaneForm* m_planeForm;
	SimulationForm* m_simulationForm;
	WormForm* m_wormForm;
	SpherePatchForm* m_spherePatchForm;

	void add(QGridLayout* buttonLayout, const char* text, Form* form, int row, int column);

private slots:
	void handleButtonClickedEvent();

};

#endif //TOOL_PANEL_H
