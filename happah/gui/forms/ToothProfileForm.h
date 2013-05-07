#ifndef TOOTHPROFILEFORM_H
#define TOOTHPROFILEFORM_H

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QSpinBox>

#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformation.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformationPart.h"
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
	void insertGearInformation(BothGearInformation* gearPart);
	void setAllMatingWidgetsEnabled(bool enable);
	void setMatingWidgetsEnabled(bool enable);
	void updateFormExistingMatingGear();
	void updateFormNoExistingMatingGear();
	void updateGearInformation(BothGearInformation* gearPart);
	void updateNormals();

	int                   m_currentPointIndex;
	GUIManager&           m_guiManager;
	QDoubleSpinBox*       m_matingConstrMaxAngleBox;
	QSpinBox*             m_matingConstrSamplRateBox;
	QCheckBox*            m_matingDarkenNormalsBox;
	std::vector<QWidget*> m_matingGearAvailableWidgetList;
	MatingGearConstructionInformation* m_matingGearInformation;
	QPushButton*          m_matingGearButton;
	QSpinBox*             m_matingNTeethSpinBox;
	QDoubleSpinBox*       m_matingNormalsLengthBox;
	QDoubleSpinBox*       m_matingRadiusSpinBox;
	std::vector<QWidget*> m_matingStartWidgetList;
	Plane_ptr             m_plane;
	QPushButton*          m_showNextNormalButton;
	QPushButton*          m_showAllNormalsButton;
	QPushButton*          m_showAngularPitchButton;
	QPushButton*          m_showMatingGearButton;
	QPushButton*          m_showReferenceCirclesButton;
	ToothProfile_ptr      m_toothProfile;
	QPushButton*          m_toSimpleGearButton;
	QCheckBox*            m_useGearWidthForNormalsBox;

private slots:
	void changeNormalsLengths(double length);
	void changeNormalsVisiblity(int state);
	void constructMatingGear();
	void showAllNormals();
	void showAngularPitches();
	void showMatingGear();
	void showNextNormal();
	void showReferenceCircles();
	void toSimpleGear();
	void updateMatingGearConstructor(ToothProfile_ptr);
	void useGearWidthForNormals(int state);

signals:
	void selected(Form* form);
	void toothProfileChanged(ToothProfile_ptr toothProfile);

};

#endif // TOOTHPROFILEFORM_H
