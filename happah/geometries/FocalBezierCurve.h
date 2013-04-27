#ifndef FOCAL_BEZIER_CURVE_H_
#define FOCAL_BEZIER_CURVE_H_

#include <vector>
#include "happah/HappahTypes.h"

using namespace std;

class FocalBezierCurve {
public:
	FocalBezierCurve(hpreal phi,vector<hpvec3>* controlPoints);
	virtual ~FocalBezierCurve();
	void update(hpreal phi,vector<hpvec3>* controlPoints);
	hpvec3 evaluate(hpreal delta);
	hpreal getPhi();

private:
	void generateNewControlPoints(hpreal delta);
	hpvec3 calcPointOnLine(hpvec3 a, hpvec3 b, hpreal deltaPhi);
	hpreal m_phi;
	hpvec3 m_center;
	vector<hpvec3>*m_controlPoints;
	vector<hpvec3>*m_currentControlPoints;
	int	m_currentDegree;
};

#endif /* FOCALBEZIERCURVE_H_ */
