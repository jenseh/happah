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

    InvoluteSpurGear* m_gear;

    uint m_toothCount;
    hpreal m_module, m_facewidth, m_pressureAngle, m_bottomClrearance, m_filletRadius;

public:
	InvoluteSpurGearTool();
	~InvoluteSpurGearTool();

private slots:
	void createGear();
/*
	void generateRndPoint();
	void periodicChanged( int state );
	void uniformChanged( int state );
	void clampedChanged( int state );
	void degreeChanged(int degree);
	void pointAdded( int x, int y );*/

public slots:
    /*void finalise();
	void leftClickAt( QPointF point );
	void rightClickAt( QPointF point );*/
};

#endif //INVOLUTESPURGEARTOOL_H

