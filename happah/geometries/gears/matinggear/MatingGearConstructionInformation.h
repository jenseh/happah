#ifndef MATINGGEARCONSTRUCTIONINFORMATION_H
#define MATINGGEARCONSTRUCTIONINFORMATION_H

#include <vector>
#include "happah/geometries/gears/matinggear/MatingGearConstructor.h"
#include "happah/geometries/BSplineCurve.h"


class MatingGearConstructionInformation {

public:
	MatingGearConstructionInformation(MatingGearConstructor* constructor);
	~MatingGearConstructionInformation();

	void setAdditionalOriginColor(hpcolor color);
	void setAdditionalMatingColor(hpcolor color);
	void setMaskingColor(hpcolor color);
	void setNormalLength(hpreal length);
	void setDarkingOfNormals(bool darkened);

	BothGearInformation* getReferenceCircles();
	BothGearInformation* getToothProfiles();
	std::vector<BothGearInformation*>* getNormals();



private:
	BSplineCurve<hpvec2>* normalLine(hpvec2 start, hpvec2 normal);
	BSplineCurve<hpvec2>* circle(hpreal radius, hpvec2 offset);
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
