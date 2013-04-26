#ifndef TOOTHPROFILEFORM_H
#define TOOTHPROFILEFORM_H

#include <QPushButton>

#include "happah/geometries/gears/MatingGearConstructor.h"
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
	void constructMatingGear();

	int m_currentPointIndex;
	GUIManager& m_guiManager;
	Plane_ptr m_plane;
	ToothProfile_ptr m_toothProfile;

	std::vector<hpcolor>* m_splineColors;
	std::list< MatingGearInformationPart* >* m_informationCurves;
	QPushButton* m_matingStepButton;
	hpuint m_stepCounter;
	std::list< MatingGearInformationPart* >::iterator m_stepIterator;
	hpcolor m_errorColor;

private slots:
	void toSimpleGear();
	void createMatingGear();
	void showNextMatingStep();

signals:
	void selected(Form* form);
	void toothProfileChanged(ToothProfile_ptr toothProfile);

};

#endif // TOOTHPROFILEFORM_H
