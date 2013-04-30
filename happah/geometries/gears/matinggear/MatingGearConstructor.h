#ifndef MATINGGEARCONSTRUCTOR_H
#define MATINGGEARCONSTRUCTOR_H

#include <list>
#include <vector>

#include "happah/HappahTypes.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformationPart.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/geometries/BSplineCurve.h"

enum class ErrorCode {
	NO_ERROR,
	NO_CUT_WITH_REFERENCE_RADIUS,
	NO_THICKNESS
};

// enum class MatingGearPart {
// 	MATING_NORMAL,
// 	ORIGIN_NORMAL,
// 	MATING_REFERENCE_CIRCLE,
// 	ORIGIN_REFERENCE_CIRCLE,
// 	MATING_TOOTH_PROFILE,
// 	ORIGIN_TOOTH_PROFILE
// };

struct MatingPoint {
	hpvec2 point;
	hpvec2 normal; //must be normalized!
	hpvec2 originPoint;
	hpvec2 originNormal; //must be normalized!
	hpreal intersectionRefRadiusAngle;
	hpreal forbiddenAreaLength;
	hpvec2 forbiddenAreaEndPoint;
	ErrorCode error;
};

// class MatingGearInformationPart {
// public:
// 	MatingGearInformationPart(BSplineCurve2D_ptr curve, MatingGearPart part, char* name, ErrorCode error = ErrorCode::NO_ERROR) : m_curve(curve), m_error(error), m_name(name), m_part(part) {}
// 	MatingGearInformationPart(BSplineCurve<hpvec2>* curve, MatingGearPart part, char* name, ErrorCode error = ErrorCode::NO_ERROR) : m_error(error), m_name(name), m_part(part) {
// 		m_curve = BSplineCurve2D_ptr(curve);
// 	}
// 	~MatingGearInformationPart() { delete m_name; }
// 	BSplineCurve2D_ptr getCurve() { return m_curve; }
// 	ErrorCode getError() {return m_error; }
// 	char* getName() { return m_name; }
// 	MatingGearPart getPart() { return m_part; }
// private:
// 	BSplineCurve2D_ptr m_curve;
// 	ErrorCode m_error;
// 	char* m_name;
// 	MatingGearPart m_part;
// };

class MatingGearConstructionInformation;

class MatingGearConstructor {
public:
	MatingGearConstructor(
		const ToothProfile& originalGearToothProfile,
		hpreal originalGearRadius,
		hpuint matingGearNTeeth,
		hpreal maxAngle,
		hpuint samplingRate
		);
	~MatingGearConstructor();

	MatingGearConstructionInformation* getInformation();

	std::list< MatingPoint >* getMatingPointList();
	hpreal getMatingGearReferenceRadius();
	hpreal getOriginalGearReferenceRadius();

	//delete following lines for printing:
	void print(hpvec2 point) {
		cerr << "[" << point.x << ",	" << point.y << "]";
	}

	static hpreal getMinRadiusForOriginGear(const ToothProfile& toothProfile, hpuint matingNTeeth);
	static hpuint getMinNumberOfTeethForMatingGear(const ToothProfile& toothProfile, hpreal originRadius);

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