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

	std::list< BSplineCurve<hpvec2>* >* getInformationSplines();

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