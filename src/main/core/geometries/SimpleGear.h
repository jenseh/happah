#ifndef SIMPLEGEAR_H
#define SIMPLEGEAR_H

#include "Gear.h"
#include "BSplineToothProfile.h"

class SimpleGear : public Gear {

private:
	BSplineToothProfile* m_toothProfile;
	hpreal m_helixAngle;
	hpreal m_facewidth;

public:
	SimpleGear(BSplineToothProfile *toothProfile, hpreal helixAngle, hpreal facewidth);
	virtual ~SimpleGear();

	BSplineCurve* toTransverseToothProfileSystem(hpreal z);

	//TODO: leave methods virtual????!!!!
	virtual hpreal getAngularPitch();
	virtual uint   getToothCount();
	virtual hpreal getHelixAngle();
	virtual hpreal getFacewidth();

	virtual void setHelixAngle(hpreal angle);
	virtual void setFacewidth(hpreal facewidth);

	virtual std::vector<hpvec2>* getToothProfile();
	virtual std::vector<hpvec2>* getGearProfile(hpreal depth);
};

#endif //SIMPLEGEAR_H
