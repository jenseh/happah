#ifndef SIMPLE_GEAR_FORM_H
#define SIMPLE_GEAR_FORM_H

#include "happah/geometries/gears/SimpleGear.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"

class SimpleGearForm : public Form {
Q_OBJECT

public:
	SimpleGearForm(GUIManager& guiManager, QWidget* parent = 0);
	~SimpleGearForm();

	SimpleGear_ptr getSimpleGear() const;
	void reset();
	void setSimpleGear(SimpleGear_ptr simpleGear);

private:
	Slider* m_faceWidthSlider;
	GUIManager& m_guiManager;
	Slider* m_helixAngleSlider;
	Slider* m_radiusSlider;
	SimpleGear_ptr m_simpleGear;
	bool m_simpleGearInserted;

	void updateRanges();
	void updateSimpleGear();

private slots:
	void changeFaceWidth(hpreal);
	void changeHelixAngle(hpreal);
	void changeRadius(hpreal);
	void createSimpleGear();

};


#endif // SIMPLE_GEAR_FORM_H
