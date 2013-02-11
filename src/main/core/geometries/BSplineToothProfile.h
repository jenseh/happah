#ifndef BSPLINETOOTHPROFILE_H
#define BSPLINETOOTHPROFILE_H

#include "BSplineCurve.h"
#include "ToothProfile.h"
#include "../../HappahTypes.h"

class BSplineToothProfile : public ToothProfile {
public:
	BSplineToothProfile(BSplineCurve *curve);
	~BSplineToothProfile();

	BSplineCurve* getRepresentation();
	std::vector<hpvec2>* getAs2DPoints();
	std::vector<hpvec2>* getAs2DPoints(hpvec3 removeDirection);
	void rotate(hpreal angle);
	bool isInClockDirection();
	bool isInCounterClockDirection();
	hpreal getAngularPitch();

private:
	BSplineCurve *m_curve;
	uint m_sampleRate;
};

#endif //BSPLINETOOTHPROFILE_H