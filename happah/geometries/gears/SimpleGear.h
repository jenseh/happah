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
	virtual ~SimpleGear();

	BSplineCurve* toTransverseToothProfileSystem(hpreal z);
	BSplineGearCurve* getBSplineToothProfileInXYPlane() const;

	//TODO: leave methods virtual????!!!!
	virtual hpreal getAngularPitch();
	virtual hpreal getBottomRadius();
	virtual hpuint getNumberOfTeeth();
	virtual hpreal getRadius();
	virtual hpreal getHelixAngle();
	virtual hpreal getFaceWidth();
	virtual BSplineGearCurve getToothProfile();

	virtual void setHelixAngle(hpreal angle);
	virtual void setFaceWidth(hpreal faceWidth);
	virtual void setToothProfile(BSplineGearCurve* curve);
	virtual void setRadius(hpreal radius);

	void getToothSpaceProfile(vector<hpvec2>& profile) const;
	void getToothProfile(vector<hpvec2>& points);

	void printToothprofile(); //TODO: delete line!!!

};
typedef shared_ptr<SimpleGear> SimpleGear_ptr;

#endif //SIMPLEGEAR_H
