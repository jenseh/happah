#ifndef INVOLUTESPURGEARTOOL_H
#define INVOLUTESPURGEARTOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "happah/HappahTypes.h"
#include "happah/gui/qt/Tool.h"
#include "happah/gui/qt/GearSlider.h"
#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/models/TriangleMesh.h"

class InvoluteSpurGearTool: public Tool {
Q_OBJECT

private:
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
    QPushButton* m_toSimpleGearButton;

    InvoluteSpurGear* m_gear;
    TriangleMesh* m_gearMesh;

    void updateGear();
    void setNewGearValues();

public:
	InvoluteSpurGearTool();
	~InvoluteSpurGearTool();

	bool knowsItem(RenderItem3D* renderItem);
	void reactivate(RenderItem3D* renderItem);

private slots:
	void createGear();
	void setBack();
	void updateRanges();
	void changeToothCount(hpreal toothCount);
	void changeModule(hpreal module);
	void changeFacewidth(hpreal facewidth);
	void changePressureAngle(hpreal angle);
	void changeBottomClearance(hpreal bottomClearance);
	void changeFilletRadius(hpreal radius);
	void changeHelixAngle(hpreal angle);
	void toSimpleGear();

public slots:
    void finalise();
};

#endif //INVOLUTESPURGEARTOOL_H

