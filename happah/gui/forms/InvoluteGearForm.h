#ifndef INVOLUTE_GEAR_FORM_H
#define INVOLUTE_GEAR_FORM_H

#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/widgets/LabeledIntegerSlider.h"
#include "happah/gui/widgets/LabeledRealValuedSlider.h"

class InvoluteGearForm : public Form {
Q_OBJECT

public:
	InvoluteGearForm(GUIManager& guiManager, QWidget* parent = 0);
	~InvoluteGearForm();

	InvoluteGear_ptr getInvoluteGear() const;
	void reset();
	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	LabeledRealValuedSlider* m_boreRadiusSlider;
	LabeledRealValuedSlider* m_bottomClearanceSlider;
	LabeledRealValuedSlider* m_faceWidthSlider;
	LabeledRealValuedSlider* m_filletRadiusSlider;
	GUIManager& m_guiManager;
	InvoluteGear_ptr m_involuteGear;
	bool m_involuteGearInserted;
	LabeledRealValuedSlider* m_helixAngleSlider;
	LabeledRealValuedSlider* m_moduleSlider;
	LabeledRealValuedSlider* m_pressureAngleSlider;
	LabeledIntegerSlider* m_nTeethSlider;

	void updateInvoluteGear();
	void setSliderValues();

private slots:
	void changeBoreRadius(hpreal boreRadius);
	void changeBottomClearance(hpreal bottomClearance);
	void changeFaceWidth(hpreal faceWidth);
	void changeFilletRadius(hpreal radius);
	void changeHelixAngle(hpreal angle);
	void changeModule(hpreal module);
	void changePressureAngle(hpreal angle);
	void changeNumberOfTeeth(int nTeeth);
	void createInvoluteGear();
	void updateRanges();

};

#endif //INVOLUTE_GEAR_FORM_H
