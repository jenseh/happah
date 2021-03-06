#ifndef B_SPLINE_CURVE_FORM_H
#define B_SPLINE_CURVE_FORM_H

#include <QCheckBox>
#include <QSpinBox>

#include "happah/geometries/BSplineCurve.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/VectorInput.h"
#include "happah/gui/forms/Form.h"

class BSplineCurveForm : public Form {
Q_OBJECT

public:
	BSplineCurveForm(GUIManager& guiManager, QWidget* parent = NULL);
	~BSplineCurveForm();

	BSplineCurve2D_ptr getCurve() const;
	void handleDrag(Ray& ray);
	void handleRay(Ray& ray);
	void handleSelection();
	void handleSelection(int pointIndex);
	void setCurve(BSplineCurve2D_ptr curve);
	void setPlane(Plane_ptr plane);

signals:
	void selected(Form* form);

private slots:
	void addPoint();
	void changePeriodic(int state);
	void changeUniform(int state);
	void changeClamped(int state);
	void changeDegree(int value);
	void createCurve();
	void deletePoint();
	void interpolate();
	void projectPointOntoPlane();
	void resetPlane();

public slots:
	void reset();

private:
	QCheckBox* m_clampedCheckBox;
	VectorInput* m_controlPointInput;
	BSplineCurve2D_ptr m_curve;
	bool m_curveInserted;
	QSpinBox* m_degreeSpinBox;
	GUIManager& m_guiManager;
	QCheckBox* m_periodicCheckBox;
	Plane_ptr m_plane;
	QLabel* m_planeLabel;
	int m_currentPointIndex;
	QCheckBox* m_uniformCheckBox;
	bool m_useStandardPlane;


};

#endif // B_SPLINE_CURVE_FORM_H
