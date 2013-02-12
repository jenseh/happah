#ifndef INVOLUTESPURGEARTOOL_H
#define INVOLUTESPURGEARTOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "../../HappahTypes.h"
#include "Tool.h"
#include "GearSlider.h"
#include "../../core/geometries/InvoluteSpurGear.h"
#include "../../core/geometries/SimpleGear.h"
#include "../../core/models/TriangleMesh.h"

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

    InvoluteSpurGear* m_gear;
    TriangleMesh* m_gearMesh;

    uint m_toothCount;
    hpreal m_module, m_facewidth, m_pressureAngle, m_bottomClearance, m_filletRadius, m_helixAngle;

    void updateGear();
    void setNewGearValues();
    void setInitialState();

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

