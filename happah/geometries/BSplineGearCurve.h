#ifndef BSPLINEGEARCURVE_H
#define BSPLINEGEARCURVE_H

#include <iostream>
#include "happah/HappahTypes.h"
#include "happah/geometries/BSplineCurve.h"

class BSplineGearCurve : public BSplineCurve {
public:
	BSplineGearCurve();
	BSplineGearCurve(const BSplineCurve& bspline);
	~BSplineGearCurve();

	BSplineCurve* getEntireGear() const;
	hpreal getAngularPitch() const;
	unsigned int getNumberOfTeeth() const;
	hpreal getMiddleLength() const;
	hpreal getMinLength() const;
	hpreal getMaxLength() const;
	void scale(hpreal scaleFactor);
	void getBounds(hpvec2* min, hpvec2* max) const;

};

#endif //BSPLINEGEARCURVE_H
