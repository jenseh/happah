#ifndef BSPLINEGEARCURVE_H
#define BSPLINEGEARCURVE_H

#include "happah/geometries/BSplineCurve.h"
#include "happah/HappahTypes.h"

class BSplineGearCurve : public BSplineCurve {
public:
	BSplineGearCurve();
	BSplineGearCurve(const BSplineCurve& bspline);
	~BSplineGearCurve();

	BSplineCurve* getEntireGear() const;
	hpreal getAngularPitch() const;
	hpuint getNumberOfTeeth() const;
	hpreal getMiddleLength() const;
	hpreal getMinLength() const;
	hpreal getMaxLength() const;
	void scale(hpreal scaleFactor);
	void getBoundingBox(hpvec2* min, hpvec2* max) const;

};

#endif //BSPLINEGEARCURVE_H
