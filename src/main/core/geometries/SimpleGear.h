#ifndef SIMPLEGEAR_H
#define SIMPLEGEAR_H

#include "Gear.h"
#include "BSplineCurve.h"

class SimpleGear : public Gear {

private:
	BSplineCurve* m_toothProfile;
	hpreal m_helixAngle;
	hpreal m_facewidth;
	bool m_scalingActivated; //TODO remove

	hpreal getScaleFactor();

public:
	SimpleGear(BSplineCurve *toothProfile, hpreal helixAngle, hpreal facewidth);
	virtual ~SimpleGear();

	BSplineCurve* toTransverseToothProfileSystem(hpreal depth);
	BSplineCurve* getBSplineToothProfileInXYPlane();

	//TODO: leave methods virtual????!!!!
	virtual hpreal getAngularPitch();
	virtual uint   getToothCount();
	virtual hpreal getHelixAngle();
	virtual hpreal getFacewidth();
	virtual bool   toothProfileIsInClockDirection();

	virtual void setHelixAngle(hpreal angle);
	virtual void setFacewidth(hpreal facewidth);
	virtual void setToothProfile(BSplineCurve* curve);

	void setScalingActivated(bool activate); //TODO remove

	virtual std::vector<hpvec2>* getToothProfile();
	//virtual std::vector<hpvec2>* getGearProfile(hpreal depth);
};

#endif //SIMPLEGEAR_H
