#ifndef FOCALSPLINEFORM_H_
#define FOCALSPLINEFORM_H_

#include "happah/gui/forms/Form.h"
#include "happah/gui/GUIManager.h"

class FocalSplineForm : public Form {
Q_OBJECT
public:
	FocalSplineForm(GUIManager& guiManager,QWidget* parent = NULL);
	virtual ~FocalSplineForm();

	FocalSpline_ptr getFocalSpline() const;
	void reset();
	void setFocalSpline(FocalSpline_ptr);
	void handleSelection();
signals:
		void selected(Form* form);
private slots:
	void createFocalSpline();
	void update();
private:
	GUIManager& m_guiManager;
	FocalSpline_ptr m_focalSpline;
	bool m_focalSplineInserted;

};

#endif /* FOCALSPLINEFORM_H_ */
