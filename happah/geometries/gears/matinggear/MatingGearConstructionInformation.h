#ifndef MATINGGEARCONSTRUCTIONINFORMATION_H
#define MATINGGEARCONSTRUCTIONINFORMATION_H

#include <vector>
#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
#include "happah/geometries/BSplineCurve.h"


class MatingGearConstructionInformation {

public:
	MatingGearConstructionInformation(MatingGearConstructor* constructor);
	~MatingGearConstructionInformation();

	bool                 areFurtherNormalsAvailable();
	BothGearInformation* getAngularPitches();
	BothGearInformation* getNextNormal();
	std::vector<BothGearInformation*>* getNormals();
	BothGearInformation* getReferenceCircles();
	BothGearInformation* getUsedConstructionPoints();
	void                 setAdditionalMatingColor(hpcolor color);
	void                 setAdditionalOriginColor(hpcolor color);
	void                 setDarkingOfNormals(bool darkened);
	void                 setMaskingColor(hpcolor color);
	void                 setNormalLength(hpreal length);
	void                 update();
	void                 useGearSizeAsNormalLength(bool normalsHaveGearLength);

private:
	BSplineCurve<hpvec2>* circle(hpreal radius, hpvec2 offset);
	void                  constructAngularPitchFan();
	void                  constructReferenceCircles();
	void                  constructUsedPointsAndNormals();
	void                  fillRainbowColorArray(std::vector<hpcolor>& colorArray);
	BSplineCurve<hpvec2>* normalLine(hpvec2 start, hpvec2 normal);
	BSplineCurve<hpvec2>* normalLine(hpvec2 start, hpvec2 normal, hpreal length);
	void                  recolorNormals();

	hpcolor                            m_additionalMatingColor;
	hpcolor                            m_additionalOriginColor;
	hpcolor                            m_angularPitchColor;
	BothGearInformation*               m_angularPitches;
	MatingGearConstructor*             m_constructor;
	hpcolor                            m_errorColor;
	bool                               m_gearSizeUsedAsNormalLength;
	bool                               m_maskAllActivated;
	hpcolor                            m_maskingColor;
	bool                               m_maskNormalsActivated;
	std::vector<BSplineCurve2D_ptr>    m_matingNormals;
	std::vector<hpcolor>               m_normalColors;
	hpreal                             m_normalLength;
	std::vector<BothGearInformation*>* m_normals;
	std::vector<BothGearInformation*>::iterator m_normalsIterator;
	std::vector<BSplineCurve2D_ptr>    m_originNormals;
	hpcolor                            m_referenceCircleColor;
	BothGearInformation*               m_referenceCircles;
	hpvec2                             m_toMatingCenter;
	hpcolor                            m_usedPointsColor;
	BothGearInformation*               m_usedPoints;

};

#endif // MATINGGEARCONSTRUCTIONINFORMATION_H
