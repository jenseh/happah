#ifndef BSPLINETOOL_H
#define BSPLINETOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>

//#include "BSplineComponent.h"
#include "../../core/geometries/BSplineCurve.h"
#include "../Drawable2D.h"
//#include "ToolSelector.h"
#include "Tool.h"

class BSplineTool: public Tool {
Q_OBJECT

private:
	int m_mode;
	static const int IDLEMODE = 0;
	static const int EDITMODE = 1;
	QSpinBox* m_degreeChooser;
	QCheckBox* m_chkPeriodic;
	QCheckBox* m_chkUniform;
	QCheckBox* m_chkInterpolateEnds;

	BSplineCurve* m_currentCurve;

public:
	BSplineTool();
	~BSplineTool();

	bool knowsItem(Drawable2D* drawable);
	void reactivate(Drawable2D* drawable);

private slots:
	void generateRndPoint();
	void periodicChanged( int state );
	void uniformChanged( int state );
	void clampedChanged( int state );
	void degreeChanged(int degree);
	void pointAdded( int x, int y );

public slots:
	void finalise();
	void leftClickAt( QPointF point );
	void rightClickAt( QPointF point );
};

#endif
