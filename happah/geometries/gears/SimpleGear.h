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
	hpreal m_facewidth;

public:
	SimpleGear(BSplineGearCurve *toothProfile, hpreal helixAngle, hpreal facewidth);
	SimpleGear(const SimpleGear& other);
	virtual ~SimpleGear();

	BSplineCurve* toTransverseToothProfileSystem(hpreal depth);
	BSplineGearCurve* getBSplineToothProfileInXYPlane() const;

	//TODO: leave methods virtual????!!!!
	virtual hpreal getAngularPitch();
	virtual hpreal getBottomRadius();
	virtual hpuint getNumberOfTeeth();
	virtual hpreal getRadius();
	virtual hpreal getHelixAngle();
	virtual hpreal getFacewidth();
	virtual BSplineGearCurve getToothProfile();

	virtual void setHelixAngle(hpreal angle);
	virtual void setFacewidth(hpreal facewidth);
	virtual void setToothProfile(BSplineGearCurve* curve);
	virtual void setRadius(hpreal radius);

	void getToothSpaceProfile(vector<hpvec2>& profile) const;
	void getToothProfile(vector<hpvec2>& points);

	void printToothprofile(); //TODO: delete line!!!

};
typedef shared_ptr<SimpleGear> SimpleGear_ptr;

#endif //SIMPLEGEAR_H
