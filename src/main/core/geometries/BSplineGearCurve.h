#ifndef BSPLINEGEARCURVE_H
#define BSPLINEGEARCURVE_H

#include <iostream>
#include "../../HappahTypes.h"
#include "BSplineCurve.h"

class BSplineGearCurve : public BSplineCurve {
public:
	BSplineGearCurve();
	~BSplineGearCurve();

	BSplineCurve* getEntireGear() const;
	hpreal getAngularPitch() const;
	uint getToothCount() const;
	void draw(Painter2D* painter);
	void getBounds(hpvec2* min, hpvec2* max) const;

};

#endif //BSPLINEGEARCURVE_H