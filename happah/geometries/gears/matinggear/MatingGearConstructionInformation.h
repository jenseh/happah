#ifndef MATINGGEARCONSTRUCTIONINFORMATION_H
#define MATINGGEARCONSTRUCTIONINFORMATION_H

#include <vector>
#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
#include "happah/geometries/BSplineCurve.h"


class MatingGearConstructionInformation {

public:
	MatingGearConstructionInformation(MatingGearConstructor* constructor);
	~MatingGearConstructionInformation();

	std::vector<BothGearInformation*>* getNormals();
	BothGearInformation* getReferenceCircles();
	BothGearInformation* getToothProfiles();

	void setAdditionalMatingColor(hpcolor color);
	void setAdditionalOriginColor(hpcolor color);
	void setDarkingOfNormals(bool darkened);
	void setMaskingColor(hpcolor color);
	void setNormalLength(hpreal length);

private:
	BSplineCurve<hpvec2>* circle(hpreal radius, hpvec2 offset);
	BSplineCurve<hpvec2>* normalLine(hpvec2 start, hpvec2 normal);
	void recolorNormals();

	std::vector<BSplineCurve2D_ptr> m_matingNormals;
	std::vector<BSplineCurve2D_ptr> m_originNormals;
	std::vector<hpcolor> m_normalColors;
	hpcolor m_maskingColor;
	hpcolor m_errorColor;
	hpcolor m_additionalOriginColor;
	hpcolor m_additionalMatingColor;
	hpcolor m_referenceCircleColor;
	hpcolor m_toothProfileColor;
	bool m_maskAllActivated;
	bool m_maskNormalsActivated;

	BothGearInformation* m_referenceCircles;
	BothGearInformation* m_toothProfiles;
	std::vector<BothGearInformation*>* m_normals;

	hpreal m_normalLength;

};

#endif // MATINGGEARCONSTRUCTIONINFORMATION_H
