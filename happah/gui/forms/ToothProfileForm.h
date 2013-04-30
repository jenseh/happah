#ifndef TOOTHPROFILEFORM_H
#define TOOTHPROFILEFORM_H

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QSpinBox>

#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformation.h"
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
	void handleDrag(Ray& ray);
	void handleRay(Ray& ray);
	void handleSelection();
	void handleSelection(int pointIndex);
	void reset();
	void setToothProfile(ToothProfile_ptr toothProfile);

private:
	void setAllMatingWidgetsEnabled(bool enable);
	void setMatingWidgetsEnabled(bool enable);
	void updateFormWithMatingGearInformation();
	void updateNormals();

	int m_currentPointIndex;
	GUIManager& m_guiManager;
	Plane_ptr m_plane;
	ToothProfile_ptr m_toothProfile;

	// std::vector<hpcolor>* m_splineColors;
	// std::list< MatingGearInformationPart* >* m_informationCurves;
	QPushButton* m_matingGearButton;
	QPushButton* m_showNextMatingStepButton;
	QPushButton* m_toSimpleGearButton;
	QPushButton* m_showMatingGearButton;

	QDoubleSpinBox* m_matingRadiusSpinBox;
	QDoubleSpinBox* m_matingConstrMaxAngleBox;
	QSpinBox* m_matingNTeethSpinBox;
	QSpinBox* m_matingConstrSamplRateBox;
	QDoubleSpinBox* m_matingNormalsLengthBox;

	QCheckBox* m_matingDarkenNormalsBox;

	std::vector<QWidget*> m_matingWidgetList;

	MatingGearConstructionInformation* m_matingGearInformation;

	// hpuint m_stepCounter;
	// std::list< MatingGearInformationPart* >::iterator m_partIterator;
	// hpcolor m_errorColor;

private slots:
	void changeNormalsVisiblity(int state);
	void changeNormalLength(double length);
	void constructMatingGear();
	void darkenNormals();
	void showMatingGear();
	void showNextMatingStep();
	void toSimpleGear();

signals:
	void selected(Form* form);
	void toothProfileChanged(ToothProfile_ptr toothProfile);

};

#endif // TOOTHPROFILEFORM_H
