#ifndef TOOTHPROFILE_H
#define TOOTHPROFILE_H

#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"

class ToothProfile {
public:
	ToothProfile();
	ToothProfile(const BSplineCurve<hpvec2>& toothProfile);
	ToothProfile(const BSplineCurve<hpvec3>& toothProfile);
	~ToothProfile();

	void   extendToGearCurve(BSplineCurve<hpvec2>& gearProfile) const;
	void   extendToGearCurve(BSplineCurve<hpvec3>& gearProfile) const;
	hpreal getAngularPitch() const;
	void   getCurve(BSplineCurve<hpvec2>& curve) const;
	void   getCurve(BSplineCurve<hpvec3>& curve) const;
	hpuint getNumberOfPoints() const;
	hpuint getNumberOfTeeth() const;
	Plane* getPlaneToothProfileLiesIn() const;
	hpreal getRootRadius() const;
	hpreal getTipRadius() const;
	bool   liesInXYPlane() const;
	bool   pointsSavedInClockDirection() const;
	void   rotate(hpreal degree);
	void   setPointOfGear(hpuint gearIndex, hpvec2 newValue);
	void   setPointOfGear(hpuint gearIndex, hpvec3 newValue);
	void   setPointOfToothProfile(hpuint toothProfileIndex, hpvec2 newValue);
	void   setPointOfToothProfile(hpuint toothProfileIndex, hpvec3 newValue);
	PointCloud* toPointCloud();
	LineMesh*   toLineMesh();
private:
	BSplineCurve<hpvec3> m_toothProfileCurve;
	void getFirstAndLastPoint(hpvec3& first, hpvec3& last) const ;
	void ensureClamping();
};

typedef std::shared_ptr<ToothProfile> ToothProfile_ptr;

#endif //TOOTHPROFILE_H
