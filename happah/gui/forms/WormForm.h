#ifndef WORM_FORM_H
#define WORM_FORM_H

#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"

class WormForm : public Form {
Q_OBJECT

public:
	WormForm(GUIManager& guiManager, QWidget* parent = 0);
	~WormForm();

	Worm_ptr getWorm() const;
	void reset();
	void setWorm(Worm_ptr worm);

private:
	GUIManager& m_guiManager;
	Slider* m_moduleSlider;
	Slider* m_pressureAngleSlider;
	Slider* m_toothCountSlider;
	Slider* m_rotationsSlider;
	Worm_ptr m_worm;
	bool m_wormInserted;

	void updateRanges();
	void updateWorm();

private slots:
	void changeModule(hpreal);
	void changePressureAngle(hpreal);
	void changeToothCount(hpreal); //TODO: Change to hpuint
	void changeRotations(hpreal);
	void createWorm();

};

#endif // WORM_FORM_H
