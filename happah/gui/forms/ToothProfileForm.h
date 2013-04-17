#ifndef TOOTHPROFILEFORM_H
#define TOOTHPROFILEFORM_H

#include "happah/geometries/gears/ToothProfile.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/forms/Form.h"
#include "happah/math/Ray.h"

class ToothProfileForm : public Form {
Q_OBJECT

public:
	ToothProfileForm(GUIManager& guiManager, QWidget* parent = NULL);
	~ToothProfileForm();

	ToothProfile_ptr getToothProfile();
	void handleRay(Ray& ray);
	void handleMove(Ray& ray);
	void handleMoveStop();
	void handleSelection() { emit selected(this); }
	void reset();
	void setToothProfile(ToothProfile_ptr toothProfile);

private:
	GUIManager& m_guiManager;
	int m_pointMoving;
	ToothProfile_ptr m_toothProfile;

private slots:
	void toSimpleGear();
	void showMatingGear();
	void showNextMatingStep();

signals:
	void selected(Form* form);

};

// class BSplineCurveForm : public Form {
// Q_OBJECT

// public:
// 	BSplineCurveForm(GUIManager& guiManager, QWidget* parent = NULL);
// 	~BSplineCurveForm();

// 	BSplineCurve_ptr getCurve() const;
// 	void handleRay(Ray& ray);
// 	void handleMove(Ray& ray);
// 	void handleMoveStop();
// 	void setCurve(BSplineCurve_ptr curve);
// 	void setPlane(Plane_ptr plane);
// 	void handleSelection(){emit selected(this);}
// signals:
// 		void selected(Form* form);
// private slots:
// 	void addPoint();
// 	void changePeriodic(int state);
// 	void changeUniform(int state);
// 	void changeClamped(int state);
// 	void changeDegree(int value);
// 	void createCurve();
// 	void interpolate();
// 	void projectPointOntoPlane();
// 	void resetPlane();

// public slots:
// 	void reset();

// private:
// 	QCheckBox* m_clampedCheckBox;
// 	VectorInput* m_controlPointInput;
// 	BSplineCurve_ptr m_curve;
// 	bool m_curveInserted;
// 	QSpinBox* m_degreeSpinBox;
// 	GUIManager& m_guiManager;
// 	QCheckBox* m_periodicCheckBox;
// 	Plane_ptr m_plane;
// 	QLabel* m_planeLabel;
// 	int m_pointMoving;
// 	QCheckBox* m_uniformCheckBox;
// 	bool m_useStandardPlane;


// };

#endif // TOOTHPROFILEFORM_H
