#ifndef TOOTHPROFILE_H
#define TOOTHPROFILE_H

#include "happah/geometries/BSplineCurve.h"
#include "happah/HappahTypes.h"

class ToothProfile {
public:
	ToothProfile(const BSplineCurve& toothProfile);
	~ToothProfile();

	BSplineCurve* getEntireGear() const;
	BSplineCurve getCurve() const;
	hpreal getAngularPitch() const;
	hpuint getNumberOfTeeth() const;
	hpreal getRootRadius() const;
	hpreal getTipRadius() const;
private:
	BSplineCurve m_toothProfileCurve;
};

#endif //TOOTHPROFILE_H
