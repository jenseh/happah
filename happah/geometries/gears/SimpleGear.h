#ifndef SIMPLEGEAR_H
#define SIMPLEGEAR_H

#include <memory>

using namespace std;

#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/geometries/gears/CylindricalGear.h"

class SimpleGear : public CylindricalGear {

public:
	SimpleGear(const ToothProfile& toothProfile, hpreal helixAngle, hpreal faceWidth);
	SimpleGear(const BSplineCurve<hpvec2>& toothProfileCurve, hpreal helixAngle, hpreal faceWidth);
	SimpleGear(const BSplineCurve<hpvec3>& toothProfileCurve, hpreal helixAngle, hpreal faceWidth);
	SimpleGear(const SimpleGear& other);
	~SimpleGear();

	ToothProfile_ptr getCopyWithBeginOfToothAtTop() const;

	hpreal getAngularPitch();
	hpreal getRootRadius();
	hpuint getNumberOfTeeth();
	hpreal getRadius();
	hpreal getHelixAngle();
	hpreal getFaceWidth();
	ToothProfile getToothProfile();

	void setHelixAngle(hpreal angle);
	void setFaceWidth(hpreal faceWidth);
	void setToothProfile(ToothProfile* curve);
	void setRadius(hpreal radius);

	void getToothSpaceProfile(vector<hpvec2>& toothSpaceProfile);
	void getToothProfile(vector<hpvec2>& toothProfile);
	void getTraverseProfile(hpreal z, BSplineCurve<hpvec3>& gearProfile);

private:
	ToothProfile_ptr m_toothProfile;
	hpreal m_helixAngle;
	hpreal m_faceWidth;



};
typedef shared_ptr<SimpleGear> SimpleGear_ptr;

#endif //SIMPLEGEAR_H
