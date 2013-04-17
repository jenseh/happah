#ifndef TOOTHPROFILE_H
#define TOOTHPROFILE_H

#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
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
	PointCloud* toPointCloud();
	LineMesh* toLineMesh();
private:
	BSplineCurve m_toothProfileCurve;
};

typedef std::shared_ptr<ToothProfile> ToothProfile_ptr;

#endif //TOOTHPROFILE_H
