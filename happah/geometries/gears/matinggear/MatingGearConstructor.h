#ifndef MATINGGEARCONSTRUCTOR_H
#define MATINGGEARCONSTRUCTOR_H

#include <list>
#include <vector>

#include "happah/HappahTypes.h"
#include "happah/geometries/gears/matinggear/MatingGearConstructionInformationPart.h"
#include "happah/geometries/gears/matinggear/MatingPoint.h"
#include "happah/geometries/gears/matinggear/MatingPointSelector.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/geometries/BSplineCurve.h"

class MatingGearConstructionInformation;

class MatingGearConstructor {
public:
	/**
	 * @brief MatingGearConstructor constructs a mating gear to the given gear by constructing a mating ToothProfile.
	 * 
	 * The given ToothProfile_ptr toothProfile is saved (in m_originalToothProfile). More informations on the construction
	 * is saved in the MatingGearConstructionInformation variable m_information, which one can obtain by getInformation().
	 *
	 * @param originalGearRadius
	 *		the reference radius used to construct the mating gear. It must not be smaller than the nearest distance of
	 *		the tooth profile to the center and it must not be bigger than the biggest distance of the tooth profile to
	 *		the center. As the minimal given originalGearRadius also depends on the number of teeth the mating gear should
	 * 		have, one can receive the minimum possible value for originalGearRadius by the static getMinRadiusForOriginGear()
	 * @param matingGearNTeeth
	 *		the number of teeth the mating gear should have. Possible values depend on the originalGearRadius and the tooth
	 *		profile. One can receive the minimal possible number for the number of teeth by calling the static method
	 *		getMinNumberOfTeethForMatingGear().
	 * @param maxAngle
	 * 		the maximal angle in degree used in the construction. The direction of successive normals in the construction
	 * 		differs only by a maximum angle of the given maxAngle.
	 * @param samplingRate
	 * 		the sampling rate used to sample the given toothProfile. It is very likely that more than samplingRate points are
	 * 		used for the construction of the mating gear, because of the maxAngle condition. Only if maxAngle is very big or
	 * 		the normals of the toothProfile have small curvatures the given samplingRate will correspond to the really constructed
	 * 		mating points.
	 */
	MatingGearConstructor(
		ToothProfile_ptr toothProfile,
		hpreal originalGearRadius,
		hpuint matingGearNTeeth,
		hpreal maxAngle,
		hpuint samplingRate
	);
	~MatingGearConstructor();

	MatingGearConstructionInformation* getInformation();

	std::vector<hpvec2>*    getMatingAngularPitchPoints();
	hpreal                  getMatingGearReferenceRadius();
	std::list<MatingPoint>* getMatingPointList();
	ToothProfile_ptr        getMatingToothProfile();
	std::vector<hpvec2>*    getOriginalAngularPitchPoints();
	hpreal                  getOriginalGearReferenceRadius();
	ToothProfile_ptr        getOriginalToothProfile();
	vector< vector<MatingPoint>* >* getSplitMatingPointLists();

	void reconstructMatingGear();
	void reconstructMatingGear(hpreal originalGearRadius);
	void reconstructMatingGear(hpreal originalGearRadius, hpuint matingGearNTeeth);

	static hpreal getMinRadiusForOriginGear(const ToothProfile& toothProfile, hpuint matingNTeeth);
	static hpuint getMinNumberOfTeethForMatingGear(const ToothProfile& toothProfile, hpreal originRadius);

private:
	void        chooseSuitableMatingPointsForGear();
	void        constructMatingGear();
	void        constructListsOfPossibleMatingPoints();
	MatingPoint getMatingPointOf(const hpvec2& point, const hpvec2& normal);
	hpvec2      getNormalAt(hpreal t);
	hpvec2      getValueAt(hpreal t);
	void        insertThicknessInMatingPoint(MatingPoint& matingPoint);
	hpreal      referenceRadiusAngle();

	MatingPointSelector                m_allMatingPoints;
	std::vector<hpreal>                m_angularPitchKnots;
	hpreal                             m_distanceOfCenters;
	MatingGearConstructionInformation* m_information;
	hpuint                             m_matingNTeeth;
	ToothProfile_ptr                   m_matingProfile;
	hpreal                             m_matingRadius;
	hpreal                             m_maxDiffAngle;
	hpreal                             m_module;
	ToothProfile_ptr                   m_originalToothProfile;
	BSplineCurve<hpvec2>*              m_originalToothCurve;
	BSplineCurve<hpvec2>*              m_originalGearCurve;
	hpreal                             m_originalRadius;
	hpuint                             m_samplingRate;
	vector< vector<MatingPoint>* >*    m_splitMatingPointLists;
	hpreal                             m_startKnots;
	hpreal                             m_stepSize;
	hpreal                             m_stopKnots;

};

#endif //MATINGGEARCONSTRUCTOR_H