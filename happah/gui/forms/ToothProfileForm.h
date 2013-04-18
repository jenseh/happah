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
	void handleDrag(Ray& ray);
	void handleSelection();
	void handleSelection(int pointIndex);
	void reset();
	void setToothProfile(ToothProfile_ptr toothProfile);

private:
	int m_currentPointIndex;
	GUIManager& m_guiManager;
	Plane_ptr m_plane;
	ToothProfile_ptr m_toothProfile;

private slots:
	void toSimpleGear();
	void showMatingGear();
	void showNextMatingStep();

signals:
	void selected(Form* form);
	void toothProfileChanged(ToothProfile_ptr toothProfile);

};

#endif // TOOTHPROFILEFORM_H
