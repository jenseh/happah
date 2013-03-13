#ifndef INVOLUTE_GEAR_FORM_H
#define INVOLUTE_GEAR_FORM_H

#include "happah/geometries/InvoluteGear.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/InvoluteGearListener.h"

class InvoluteGearForm : public Form {
Q_OBJECT

public:
	InvoluteGearForm(InvoluteGearListener& involuteGearListener, QWidget* parent = 0);
	~InvoluteGearForm();

	InvoluteGear_ptr getInvoluteGear() const;
	void reset();
	void setInvoluteGear(InvoluteGear_ptr involuteGear);

private:
	Slider* m_bottomClearanceSlider;
	Slider* m_faceWidthSlider;
	Slider* m_filletRadiusSlider;
	InvoluteGear_ptr m_involuteGear;
	bool m_involuteGearInserted;
	InvoluteGearListener& m_involuteGearListener;
	Slider* m_helixAngleSlider;
	Slider* m_moduleSlider;
	Slider* m_pressureAngleSlider;
	Slider* m_toothCountSlider;

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
