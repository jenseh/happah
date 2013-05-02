#ifndef FOCALSPLINEFORM_H_
#define FOCALSPLINEFORM_H_
#include <QPushButton>
#include "happah/gui/forms/Form.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/widgets/LabeledIntegerSpinBox.h"
#include "happah/math/Ray.h"


class FocalSplineForm : public Form {
Q_OBJECT
public:
	FocalSplineForm(GUIManager& guiManager,QWidget* parent = NULL);
	virtual ~FocalSplineForm();

	FocalSpline_ptr getFocalSpline() const;
	void reset();
	void setFocalSpline(FocalSpline_ptr);
	void handleSelection();
	void handleSelection(int pointIndex);
	void handleDrag(Ray& ray);
	void handleRay(Ray& ray);
signals:
		void selected(Form* form);
private slots:
	void createFocalSpline();
	void changeDegree(int value);
	void changeDetail(int value);
	void activateControPointCreation();
	void extendSpline();
	void toggleRiesenfeld();
	void changeLRIterations(int value);
	void changeLRDegree(int value);
	void toggleControlPolygon();
	void toggleCircle();
private:
	bool m_createPoints;
	void update();
	int m_currentPointIndex;
	GUIManager& m_guiManager;
	FocalSpline_ptr m_focalSpline;
	Plane_ptr m_plane;
	bool m_focalSplineInserted;
	QSpinBox* m_degreeSpinBox;
	QSpinBox* m_detailSpinBox;
	QPushButton* m_addPointButton;
	QPushButton* m_doRiesenfeldButton;
	QSpinBox* 	 m_riesenfeldIterationsM;
	QSpinBox* 	 m_riesenfeldDegreeN;
	QPushButton* m_showControlPolygon;
	QPushButton* m_showCircleButton;

};

#endif /* FOCALSPLINEFORM_H_ */
