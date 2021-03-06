#ifndef WORM_FORM_H
#define WORM_FORM_H

#include "happah/gui/GUIManager.h"
#include "happah/gui/widgets/LabeledRealValuedSlider.h"
#include "happah/gui/forms/Form.h"

class WormForm : public Form {
Q_OBJECT

public:
	WormForm(GUIManager& guiManager, QWidget* parent = 0);
	~WormForm();

	Worm_ptr getWorm() const;
	void reset();
	void setWorm(Worm_ptr worm);
	void handleSelection(){emit selected(this);}
signals:
	void selected(Form* form);
private:
	GUIManager& m_guiManager;
	LabeledRealValuedSlider* m_baseRadiusSlider;
	LabeledRealValuedSlider* m_moduleSlider;
	LabeledRealValuedSlider* m_pressureAngleSlider;
	LabeledRealValuedSlider* m_toothCountSlider;
	LabeledRealValuedSlider* m_rotationsSlider;
	Worm_ptr m_worm;
	bool m_wormInserted;

	void updateRanges();
	void updateWorm();

private slots:
	void changeBaseRadius(hpreal);
	void changeModule(hpreal);
	void changePressureAngle(hpreal);
	void changeToothCount(hpreal);
	void changeRotations(hpreal);
	void createWorm();

};

#endif // WORM_FORM_H
