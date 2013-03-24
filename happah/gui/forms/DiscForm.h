#ifndef DISCFORM_H_
#define DISCFORM_H_

#include "happah/geometries/DiscGenerator.h"
#include "happah/geometries/StandardProfile.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"

class DiscForm : public Form {
Q_OBJECT

public:
	DiscForm(GUIManager& guiManager, QWidget* parent = 0);
	~DiscForm();

	SurfaceOfRevolution_ptr getDisc() const;
	void reset();
	void setDisc(SurfaceOfRevolution_ptr disc);

private:
	SurfaceOfRevolution_ptr m_disc;
	bool m_discInserted;
	GUIManager& m_guiManager;
	Slider* m_radiusSlider;

	void updateDisc();
	void updateRanges();

private slots:
	void changeRadius(hpreal);
	void createDisc();

};

#endif
