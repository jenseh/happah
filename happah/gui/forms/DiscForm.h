#ifndef DISCFORM_H_
#define DISCFORM_H_

#include "happah/geometries/DiscGenerator.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/widgets/LabeledRealValuedSlider.h"
#include "happah/gui/forms/Form.h"

class DiscForm : public Form {
Q_OBJECT

public:
	DiscForm(GUIManager& guiManager, QWidget* parent = 0);
	~DiscForm();

	SurfaceOfRevolution_ptr getDisc() const;
	void reset();
	void setDisc(SurfaceOfRevolution_ptr disc);
	void handleSelection(){emit selected(this);}
signals:
	void selected(Form* form);
private:
	SurfaceOfRevolution_ptr m_disc;
	bool m_discInserted;
	GUIManager& m_guiManager;
	hpreal m_pressureAngle;
	LabeledRealValuedSlider* m_pressureAngleSlider;
	hpreal m_radius;
	LabeledRealValuedSlider* m_radiusSlider;

	void updateDisc();
	void updateRanges();

private slots:
	void changeRadius(hpreal);
	void changePressureAngle(hpreal);
	void createDisc();

};

#endif
