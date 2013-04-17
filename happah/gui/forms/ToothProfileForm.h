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

#endif // TOOTHPROFILEFORM_H
