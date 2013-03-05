#ifndef INVOLUTE_GEAR_FORM_H
#define INVOLUTE_GEAR_FORM_H

class GUIManager;

#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/GearSlider.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/forms/Form.h"

class InvoluteGearForm : public Form {
Q_OBJECT

public:
	InvoluteGearForm(GUIManager& sceneManager, QWidget* parent = 0);
	~InvoluteGearForm();

	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	GearSlider* m_bottomClearanceSlider;
	GearSlider* m_faceWidthSlider;
	GearSlider* m_filletRadiusSlider;
	InvoluteGear_ptr m_involuteGear;
	bool m_involuteGearInScene;
	GUIManager& m_guiManager;
	GearSlider* m_helixAngleSlider;
	GearSlider* m_moduleSlider;
	GearSlider* m_pressureAngleSlider;
	GearSlider* m_toothCountSlider;

	void updateInvoluteGear();

private slots:
	void changeBottomClearance(hpreal bottomClearance);
	void changeFacewidth(hpreal facewidth);
	void changeFilletRadius(hpreal radius);
	void changeHelixAngle(hpreal angle);
	void changeModule(hpreal module);
	void changePressureAngle(hpreal angle);
	void changeToothCount(hpreal toothCount);
	void createInvoluteGear();
	void updateRanges();

};

#endif //INVOLUTE_GEAR_FORM_H
