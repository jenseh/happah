#ifndef SIMPLEGEAR_H
#define SIMPLEGEAR_H

#include <memory>

using namespace std;

#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/geometries/gears/CylindricalGear.h"

class SimpleGear : public CylindricalGear {

private:
	ToothProfile* m_toothProfile;
	hpreal m_helixAngle;
	hpreal m_faceWidth;

public:
	SimpleGear(ToothProfile* toothProfile, hpreal helixAngle, hpreal faceWidth);
	SimpleGear(const BSplineCurve& toothProfileCurve, hpreal helixAngle, hpreal faceWidth);
	SimpleGear(const SimpleGear& other);
	~SimpleGear();

	void getTraverseProfile(hpreal z, BSplineCurve* gearProfile);
	BSplineCurve* toTransverseToothProfileSystem(hpreal z);
	ToothProfile* getCopyWithBeginOfToothAtTop() const;

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
	void getTraverseProfile(hpreal z, BSplineCurve& gearProfile);

};
typedef shared_ptr<SimpleGear> SimpleGear_ptr;

#endif //SIMPLEGEAR_H
