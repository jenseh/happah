#ifndef SIMPLEGEAR_H
#define SIMPLEGEAR_H

#include "Gear.h"
#include "BSplineGearCurve.h"

class SimpleGear : public Gear {

private:
	BSplineGearCurve* m_toothProfile;
	hpreal m_helixAngle;
	hpreal m_facewidth;

public:
	SimpleGear(BSplineGearCurve *toothProfile, hpreal helixAngle, hpreal facewidth);
	virtual ~SimpleGear();

	BSplineCurve* toTransverseToothProfileSystem(hpreal depth);
	BSplineGearCurve* getBSplineToothProfileInXYPlane();

	//TODO: leave methods virtual????!!!!
	virtual hpreal getAngularPitch();
	virtual uint   getToothCount();
	virtual hpreal getRadius();
	virtual hpreal getHelixAngle();
	virtual hpreal getFacewidth();
	virtual bool   toothProfileIsInClockDirection();

	virtual void setHelixAngle(hpreal angle);
	virtual void setFacewidth(hpreal facewidth);
	virtual void setToothProfile(BSplineGearCurve* curve);
	virtual void setRadius(hpreal radius);

	virtual std::vector<hpvec2>* getToothProfile();

};

#endif //SIMPLEGEAR_H
