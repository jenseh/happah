#ifndef INVOLUTE_GEAR_FORM_H
#define INVOLUTE_GEAR_FORM_H

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"

class InvoluteGearForm : public Form {
Q_OBJECT

public:
	InvoluteGearForm(GUIManager& guiManager, QWidget* parent = 0);
	~InvoluteGearForm();

	InvoluteGear_ptr getInvoluteGear() const;
	void reset();
	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	Slider* m_boreRadiusSlider;
	Slider* m_bottomClearanceSlider;
	Slider* m_faceWidthSlider;
	Slider* m_filletRadiusSlider;
	GUIManager& m_guiManager;
	InvoluteGear_ptr m_involuteGear;
	bool m_involuteGearInserted;
	Slider* m_helixAngleSlider;
	Slider* m_moduleSlider;
	Slider* m_pressureAngleSlider;
	Slider* m_nTeethSlider;

	void updateInvoluteGear();

private slots:
	void changeBoreRadius(hpreal boreRadius);
	void changeBottomClearance(hpreal bottomClearance);
	void changeFaceWidth(hpreal faceWidth);
	void changeFilletRadius(hpreal radius);
	void changeHelixAngle(hpreal angle);
	void changeModule(hpreal module);
	void changePressureAngle(hpreal angle);
	void changeNumberOfTeeth(hpreal nTeeth);
	void createInvoluteGear();
	void updateRanges();

};

#endif //INVOLUTE_GEAR_FORM_H
