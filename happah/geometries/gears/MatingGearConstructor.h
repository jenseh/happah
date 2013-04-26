#ifndef MATINGGEARCONSTRUCTOR_H
#define MATINGGEARCONSTRUCTOR_H

#include <list>
#include <vector>

#include "happah/HappahTypes.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/geometries/BSplineCurve.h"

enum class ErrorCode {
	NO_ERROR,
	NO_CUT_WITH_REFERENCE_RADIUS,
	NO_THICKNESS
};

struct MatingPoint {
	hpvec2 point;
	hpvec2 normal; //must be normalized!
	hpvec2 originPoint;
	hpvec2 originNormal; //must be normalized!
	hpreal intersectionRefRadiusAngle;
	hpreal forbiddenAreaLength;
	hpvec2 forbiddenAreaEndPoint;
	ErrorCode error;
	//enum with type of point (if an origin point exists and so on)
	// bool operator==(MatingCandidate const& other) {
	// 	return (other.angleInGear == angleInGear
	// 		&& other.distanceToCenter == distanceToCenter
	// 		&& other.originPoint == originPoint
	// 		&& other.point == point);
	// }
};

class CurveWithName {
public:
	CurveWithName(BSplineCurve<hpvec2>* curve, char* name) : m_curve(curve), m_name(name) {}
	~CurveWithName() { delete m_curve; delete m_name; }
	BSplineCurve<hpvec2>* getCurve() { return m_curve; }
	char* getName() { return m_name; }
private:
	BSplineCurve<hpvec2>* m_curve;
	char* m_name;
};

class MatingGearConstructor {
public:
	MatingGearConstructor();
	~MatingGearConstructor();
	
	void constructMatingTo(
		const ToothProfile& toothProfile,
		hpreal radius,
		hpuint matingGearNTeeth,
		hpuint samplingRate,
		hpreal maxAngle,
		hpreal infomationNormalLength = 1.0f);

	std::list< CurveWithName* >* getInformationSplines();

	//delete following lines for printing:
	void print(hpvec2 point) {
		cerr << "[" << point.x << ",	" << point.y << "]";
	}

	void print(const MatingPoint& m) {
			cerr << endl << "MatingPoint:";
			cerr << endl << "error:          " << static_cast<int>(m.error);
		if(m.error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS)
			cerr << endl << "point:          "; print(m.point);
			cerr << endl << "original point: "; print(m.originPoint);
		if(m.error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS)
			cerr << endl << "normal:         "; print(m.normal);
			cerr << endl << "original normal:"; print(m.originNormal);
		if(m.error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS)
			cerr << endl << "inters.Ref.rad.:" << m.intersectionRefRadiusAngle;
		if(m.error == ErrorCode::NO_ERROR) {
			cerr << endl << "forbid. length: " << m.forbiddenAreaLength;
			cerr << endl << "forbid. endPoint"; print(m.forbiddenAreaEndPoint);
		}
	}

private:
	void constructListsOfPossibleMatingPoints();
	hpreal referenceRadiusAngle();
	MatingPoint getMatingPointOf(const hpvec2& point, const hpvec2& normal);
	void insertThicknessInMatingPoint(MatingPoint& matingPoint);
	hpvec2 getNormalAt(hpreal t);
	hpvec2 getValueAt(hpreal t);
	BSplineCurve<hpvec2>* normalLine(hpvec2 start, hpvec2 normal);
	BSplineCurve<hpvec2>* circle(hpreal radius, hpvec2 offset);

	std::list<MatingPoint>* m_allMatingPoints;
	ToothProfile* m_originalToothProfile;
	BSplineCurve<hpvec2>* m_originalToothCurve;
	BSplineCurve<hpvec2>* m_originalGearCurve;
	hpreal m_originalRadius;
	hpreal m_module;
	hpuint m_matingNTeeth;
	hpreal m_matingRadius;
	hpreal m_distanceOfCenters;
	ToothProfile* m_matingProfile;
	hpuint m_samplingRate;
	hpreal m_stepSize;
	hpreal m_maxDiffAngle;
	hpreal m_startKnots;
	hpreal m_stopKnots;
	hpreal m_informationNormalLength;
};

#endif //MATINGGEARCONSTRUCTOR_H