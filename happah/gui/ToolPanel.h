#ifndef TOOL_PANEL_H
#define TOOL_PANEL_H

#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <unordered_map>

using namespace std;

#include "happah/gui/GUIManager.h"
#include "happah/gui/forms/BSplineCurveForm.h"
#include "happah/gui/forms/DiscForm.h"
#include "happah/gui/forms/InvoluteGearForm.h"
#include "happah/gui/forms/PlaneForm.h"
#include "happah/gui/forms/SimpleGearForm.h"
#include "happah/gui/forms/SimpleGearForm.h"
#include "happah/gui/forms/SimulationForm.h"
#include "happah/gui/forms/SpherePatchForm.h"
#include "happah/gui/forms/WormForm.h"

class ToolPanel : public QWidget {
Q_OBJECT

public:
	ToolPanel(GUIManager& guiManager, QWidget* parent = 0);
	~ToolPanel();

	BSplineCurveForm* getBSplineCurveForm();
	DiscForm* getDiscForm();
	InvoluteGearForm* getInvoluteGearForm();
	PlaneForm* getPlaneForm();
	SimpleGearForm* getSimpleGearForm();
	SimulationForm* getSimulationForm();
	SpherePatchForm* getSpherePatchForm();
	WormForm* getWormForm();

	void setForm(Form* form);	

private:
	unordered_map<Form*,QPushButton*> m_buttonsByForm;
	QStackedWidget* m_forms;
	unordered_map<QPushButton*,Form*> m_formsByButton;

	BSplineCurveForm* m_bSplineCurveForm;
	DiscForm* m_discForm;
	InvoluteGearForm* m_involuteGearForm;
	PlaneForm* m_planeForm;
	SimpleGearForm* m_simpleGearForm;
	SimulationForm* m_simulationForm;
	SpherePatchForm* m_spherePatchForm;
	WormForm* m_wormForm;

	void add(QGridLayout* buttonLayout, const char* text, Form* form, int row, int column);

private slots:
	void handleButtonClickedEvent();

};

#endif //TOOL_PANEL_H
