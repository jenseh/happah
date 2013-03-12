#ifndef WORMFORM_H_
#define WORMFORM_H_

#include "happah/gui/GearSlider.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/WormListener.h"

class WormForm : public Form {
Q_OBJECT

public:
	WormForm(WormListener& wormListener, QWidget* parent = 0);
	~WormForm();

	Worm_ptr getWorm() const;
	void reset();
	void setWorm(Worm_ptr worm);

private:
	GearSlider* m_toothCountSlider;
	GearSlider* m_moduleSlider;
	GearSlider* m_pressureAngleSlider;
	Worm_ptr m_worm;
	bool m_wormInserted;
	WormListener& m_wormListener;

	void updateRanges();
	void updateWorm();

private slots:
	void changeToothCount(hpreal); //TODO: Change to hpuint
	void changeModule(hpreal);
	void changePressureAngle(hpreal);
	void createWorm();

};

#endif /* WORMFORM_H_ */
