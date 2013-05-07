#ifndef TOOTHPROFILE_H
#define TOOTHPROFILE_H

#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/Plane.h"
#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"

class MatingGearConstructor;

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
	MatingGearConstructor* getMatingGearConstructor() const;
	hpuint getNumberOfPoints() const;
	hpuint getNumberOfTeeth() const;
	Plane* getPlaneToothProfileLiesIn() const;
	hpreal getRootRadius() const;
	hpreal getTipRadius() const;
	bool   hasMatingGear() const;
	bool   liesInXYPlane() const;
	bool   pointsSavedInClockDirection() const;
	void   rotate(hpreal degree);
	//TODO: following ĺine can be removed when moving is done by the transformation matrices
	void   setCenter(hpvec2 center);
	bool   setMatingGearConstructor(MatingGearConstructor* constructor);
	void   setPointOfGear(hpuint gearIndex, hpvec2 newValue);
	void   setPointOfGear(hpuint gearIndex, hpvec3 newValue);
	void   setPointOfToothProfile(hpuint toothProfileIndex, hpvec2 newValue);
	void   setPointOfToothProfile(hpuint toothProfileIndex, hpvec3 newValue);
	PointCloud* toPointCloud();
	LineMesh*   toLineMesh();
	void    updateMatingGearConstructor();
private:
	MatingGearConstructor* m_matingGearConstructor;
	BSplineCurve<hpvec3>   m_toothProfileCurve;
	void getFirstAndLastPoint(hpvec3& first, hpvec3& last) const ;
	void ensureClamping();
	//TODO: following two lines can be removed when moving is done by the transformation matrices
	void moveCurve(hpvec2 direction, BSplineCurve<hpvec3>& curve) const;
	hpvec2 m_center;
};

typedef std::shared_ptr<ToothProfile> ToothProfile_ptr;

#endif //TOOTHPROFILE_H
