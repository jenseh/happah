#ifndef SIMPLEGEARTOOL_H
#define SIMPLEGEARTOOL_H

#include "happah/HappahTypes.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/gui/qt/GearSlider.h"
#include "happah/gui/qt/tools/Tool.h"
#include "happah/models/TriangleMesh.h"

class SimpleGearTool : public Tool {
Q_OBJECT

private:
	int m_mode;
	static const int IDLEMODE = 0;
	static const int EDITMODE = 1;

	GearSlider* m_helixAngleSlider;
	GearSlider* m_facewidthSlider;
	GearSlider* m_radiusSlider;
	QPushButton* m_changeOutlineButton;

	SimpleGear* m_gear;
	TriangleMesh* m_gearMesh;

	void updateGear();
	void updateRanges();

public:
	SimpleGearTool();
	~SimpleGearTool();

private slots:
	void createGear();
	void changeHelixAngle(hpreal);
	void changeFacewidth(hpreal);
	void changeRadius(hpreal);
	void toBSpline();

public slots:
	void finalise();
};

#endif //SIMPLEGEARTOOL_H
