#ifndef TOOTHPROFILE_H
#define TOOTHPROFILE_H

#include "happah/geometries/BSplineCurve.h"
#include "happah/HappahTypes.h"

class ToothProfile {
public:
	ToothProfile(const BSplineCurve& toothProfile);
	~ToothProfile();

	void extendToGearCurve(BSplineCurve& gearProfile) const;
	BSplineCurve getCurve() const;
	hpreal getAngularPitch() const;
	hpuint getNumberOfTeeth() const;
	hpreal getRootRadius() const;
	hpreal getTipRadius() const;
	bool pointsSavedInClockDirection() const;
	void rotate(hpreal degree);
private:
	BSplineCurve m_toothProfileCurve;
};

#endif //TOOTHPROFILE_H
