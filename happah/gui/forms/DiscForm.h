#ifndef DISCFORM_H_
#define DISCFORM_H_

#include "happah/geometries/Disc.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"

class DiscForm : public Form {
Q_OBJECT

public:
	DiscForm(GUIManager& guiManager, QWidget* parent = 0);
	~DiscForm();

	Disc_ptr getDisc() const;
	void reset();
	void setDisc(Disc_ptr disc);

private:
	Disc_ptr m_disc;
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
