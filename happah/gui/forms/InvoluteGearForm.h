#ifndef INVOLUTE_GEAR_FORM_H
#define INVOLUTE_GEAR_FORM_H

#include <QWidget>

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/gui/GearSlider.h"
#include "happah/scene/SceneManager.h"

class InvoluteGearForm : public QWidget {
Q_OBJECT

public:
	InvoluteGearForm(SceneManager& sceneManager, QWidget* parent = 0);
	~InvoluteGearForm();

private:
	SceneManager& m_sceneManager;

	GearSlider* m_toothCountSlider;
	GearSlider* m_moduleSlider;
	GearSlider* m_facewidthSlider;
	GearSlider* m_pressureAngleSlider;
	GearSlider* m_bottomClearanceSlider;
	GearSlider* m_filletRadiusSlider;
	GearSlider* m_helixAngleSlider;

	InvoluteGear_ptr m_gear;
	TriangleMesh_ptr m_gearMesh;

	void updateGear();
	void setNewGearValues();

private slots:
	void changeBottomClearance(hpreal bottomClearance);
	void changeFacewidth(hpreal facewidth);
	void changeFilletRadius(hpreal radius);
	void changeHelixAngle(hpreal angle);
	void changeModule(hpreal module);
	void changePressureAngle(hpreal angle);
	void changeToothCount(hpreal toothCount);
	void createGear();
	void updateRanges();

};

#endif //INVOLUTE_GEAR_FORM_H
