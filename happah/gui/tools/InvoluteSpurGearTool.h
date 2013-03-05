#ifndef INVOLUTESPURGEARTOOL_H
#define INVOLUTESPURGEARTOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "happah/HappahTypes.h"
#include "happah/geometries/InvoluteGear.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/gui/qt/GearSlider.h"
#include "happah/gui/qt/tools/Tool.h"
#include "happah/models/TriangleMesh.h"
#include "happah/scene/SceneManager.h"

class InvoluteSpurGearTool: public Tool {
Q_OBJECT

private:
	SceneManager& m_sceneManager;
	int m_mode;
	static const int IDLEMODE = 0;
	static const int EDITMODE = 1;

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

public:
	InvoluteSpurGearTool(SceneManager& sceneManager);
	~InvoluteSpurGearTool();

private slots:
	void createGear();
	void updateRanges();
	void changeToothCount(hpreal toothCount);
	void changeModule(hpreal module);
	void changeFacewidth(hpreal facewidth);
	void changePressureAngle(hpreal angle);
	void changeBottomClearance(hpreal bottomClearance);
	void changeFilletRadius(hpreal radius);
	void changeHelixAngle(hpreal angle);

};

#endif //INVOLUTESPURGEARTOOL_H

