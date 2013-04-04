#ifndef SIMPLEGEAR_H
#define SIMPLEGEAR_H

#include <memory>

using namespace std;

#include "happah/geometries/gears/BSplineGearCurve.h"
#include "happah/geometries/gears/CylindricalGear.h"

class SimpleGear : public CylindricalGear {

private:
	BSplineGearCurve* m_toothProfile;
	hpreal m_helixAngle;
	hpreal m_faceWidth;

public:
	SimpleGear(BSplineGearCurve *toothProfile, hpreal helixAngle, hpreal faceWidth);
	SimpleGear(const SimpleGear& other);
	~SimpleGear();

	BSplineCurve* toTransverseToothProfileSystem(hpreal z);
	BSplineGearCurve* getCopyWithBeginOfToothAtTop() const;

	hpreal getAngularPitch();
	hpreal getRootRadius();
	hpuint getNumberOfTeeth();
	hpreal getRadius();
	hpreal getHelixAngle();
	hpreal getFaceWidth();
	BSplineGearCurve getToothProfile();

	void setHelixAngle(hpreal angle);
	void setFaceWidth(hpreal faceWidth);
	void setToothProfile(BSplineGearCurve* curve);
	void setRadius(hpreal radius);

	void getToothSpaceProfile(vector<hpvec2>& toothSpaceProfile) const;
	void getToothProfile(vector<hpvec2>& toothProfile);

};
typedef shared_ptr<SimpleGear> SimpleGear_ptr;

#endif //SIMPLEGEAR_H
