#ifndef SIMPLEGEARTOOL_H
#define SIMPLEGEARTOOL_H

#include "Tool.h"
#include "GearSlider.h"
#include "../../HappahTypes.h"
#include "../../core/geometries/SimpleGear.h"
#include "../../core/models/TriangleMesh.h"

class SimpleGearTool : public Tool {
Q_OBJECT

private:
	int m_mode;
	static const int IDLEMODE = 0;
	static const int EDITMODE = 1;

	GearSlider* m_helixAngleSlider;
	GearSlider* m_facewidthSlider;
	QPushButton* m_changeOutlineButton;

	SimpleGear* m_gear;
	TriangleMesh* m_gearMesh;

	void updateGear();
	void updateRanges();

public:
	SimpleGearTool();
	~SimpleGearTool();

	bool knowsItem(RenderItem3D* renderItem);
	void reactivate(RenderItem3D* renderItem);

private slots:
	void createGear();
	void changeHelixAngle(hpreal);
	void changeFacewidth(hpreal);
	void toBSpline();

public slots:
	void finalise();
};

#endif //SIMPLEGEARTOOL_H