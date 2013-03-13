#ifndef DISCFORM_H_
#define DISCFORM_H_

#include "happah/geometries/Disc.h"
#include "happah/gui/Slider.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/DiscListener.h"


class DiscForm : public Form{
	Q_OBJECT
	public:
		DiscForm(DiscListener& discListener, QWidget* parent = 0);
		~DiscForm();

		Disc_ptr getDisc() const;
		void reset();
		void setDisc(Disc_ptr Disc);

	private:
		Slider* m_radiusSlider;
		Disc_ptr m_disc;
		bool m_discInserted;
		DiscListener& m_discListener;

		void updateRanges();
		void updateDisc();

	private slots:
		void changeRadius(hpreal);
		void createDisc();

};

#endif
