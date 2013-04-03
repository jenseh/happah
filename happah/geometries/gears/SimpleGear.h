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
	BSplineGearCurve* getBSplineToothProfileInXYPlane()const;

	//TODO: leave methods virtual????!!!!
	virtual hpreal getAngularPitch();
	virtual hpreal getBottomRadius();
	virtual hpuint getNumberOfTeeth();
	virtual hpreal getRadius();
	virtual hpreal getHelixAngle();
	virtual hpreal getFacewidth();
	virtual bool   toothProfileIsInClockDirection();

	virtual void setHelixAngle(hpreal angle);
	virtual void setFacewidth(hpreal facewidth);
	virtual void setToothProfile(BSplineGearCurve* curve);
	virtual void setRadius(hpreal radius);

    virtual void getToothSpaceProfile(vector<hpvec2> &profile)const;
	virtual vector<hpvec2>* getToothProfile(hpuint toothSampleSize = 100);

};
typedef shared_ptr<SimpleGear> SimpleGear_ptr;

#endif //SIMPLEGEAR_H
