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

	BSplineCurve_ptr getCurve() const;
	void handleRay(Ray& ray);
	void reset();
	void setCurve(BSplineCurve_ptr curve);
	void setPlane(Plane_ptr plane);

private slots:
	void addPoint();
	void changePeriodic(int state);
	void changeUniform(int state);
	void changeClamped(int state);
	void changeDegree(int value);
	void createCurve();

private:
	GUIManager& m_guiManager;
	VectorInput* m_controlPointInput;
	BSplineCurve_ptr m_curve;
	bool m_curveInserted;
	Plane_ptr m_plane;
	QCheckBox* m_periodicCheckBox;
	QCheckBox* m_uniformCheckBox;
	QCheckBox* m_clampedCheckBox;
	QSpinBox* m_degreeSpinBox;

};

#endif // B_SPLINE_CURVE_FORM_H
