#include "happah/geometries/gears/matinggear/MatingGearConstructionInformation.h"

MatingGearConstructionInformation::MatingGearConstructionInformation(MatingGearConstructor* constructor)
  : m_normals(new std::vector<BothGearInformation*>()),
	m_maskAllActivated(false),
	m_maskNormalsActivated(false),
	m_normalLength(1.0f) {

	std::list< MatingPoint >* allMatingPoints = constructor->getMatingPointList();

	//Colors
	m_additionalMatingColor = hpcolor(1.0f, 1.0f, 1.0f, 1.0f);
	m_additionalOriginColor = hpcolor(0.8f, 0.8f, 0.8f, 1.0f);
	m_maskingColor = hpcolor(0.0f, 0.0f, 0.0f, 1.0f);
	m_errorColor = hpcolor(1.0f, 0.0f, 0.0f, 1.0f);
	m_referenceCircleColor = hpcolor(0.1f, 0.1f, 0.7f, 1.0f);
	m_toothProfileColor = hpcolor(0.1f, 0.4f, 0.5f, 1.0f);

	std::vector<hpcolor> normalColors(allMatingPoints->size());
	hpreal adaption = (255.0f * 3) / normalColors.size();

	for(hpuint i = 0; i < normalColors.size(); ++i) {
		hpuint step = (i * adaption);
		hpuint red, green, blue;
		if(step / 256 <= 0) {
			red = step;
			green = 255 - step / 2;
			blue = 255 - step / 2;
		} else if (step / 256 <= 1) {
			red = 255 - (step - 256) / 2;
			green = step - 256;
			blue = 255 - (step - 256) / 2;
		} else {
			red = 255 - (step - 512) / 2;
			green = 255 - (step - 512) / 2;
			blue = step - 512;
		}
		hpcolor color = hpcolor(red, green, blue, 255) * (1.0f / 255.0f);
		normalColors[i] = color;
	}

	//Vector between centers
	hpvec2 toMatingCenter = hpvec2(constructor->getOriginalGearReferenceRadius() + constructor->getMatingGearReferenceRadius(), 0.0f);

	//Reference Circles
	MatingGearConstructionInformationPart originReferenceRadius =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(circle(constructor->getOriginalGearReferenceRadius(), hpvec2(0.0f, 0.0f))),
			m_referenceCircleColor * m_additionalOriginColor,
			"Original gear ref circle",
			HP_LINE_MESH);

	MatingGearConstructionInformationPart matingReferenceRadius =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(circle(constructor->getMatingGearReferenceRadius(), toMatingCenter)),
			m_referenceCircleColor * m_additionalMatingColor,
			"Mating gear ref circle",
			HP_LINE_MESH);

	m_referenceCircles = new BothGearInformation(originReferenceRadius, matingReferenceRadius);

	//Tooth Profiles And Normals
	BSplineCurve<hpvec2>* originalUsedPoints = new BSplineCurve<hpvec2>();
	BSplineCurve<hpvec2>* matingPoints = new BSplineCurve<hpvec2>();

	hpuint colorCounter = 0;
	for(auto it = allMatingPoints->begin(); it != allMatingPoints->end(); ++it) {
		if(it->error == ErrorCode::NO_ERROR) {

			//for tooth profile:
			originalUsedPoints->addControlPoint(it->originPoint);
			matingPoints->addControlPoint(it->point + toMatingCenter);

			//for normals:
			MatingGearConstructionInformationPart matingNormal =
				MatingGearConstructionInformationPart(
					BSplineCurve2D_ptr(normalLine(it->point + toMatingCenter, it->normal)),
					normalColors[colorCounter] * m_additionalMatingColor,
					"Normal Of Mating Gear",
					static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
			MatingGearConstructionInformationPart originalNormal =
				MatingGearConstructionInformationPart(
					BSplineCurve2D_ptr(normalLine(it->originPoint, it->originNormal)),
					normalColors[colorCounter] * m_additionalOriginColor,
					"Normal Of Original Gear",
					static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
			m_normals->push_back(new BothGearInformation(originalNormal, matingNormal));
			m_normalColors.push_back(normalColors[colorCounter]);
			++colorCounter;

		} else {
			MatingGearConstructionInformationPart originalNormal =
				MatingGearConstructionInformationPart(
					BSplineCurve2D_ptr(normalLine(it->originPoint, it->originNormal)),
					m_errorColor * m_additionalOriginColor,
					"Normal Of Original Gear without cut",
					static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
			m_normals->push_back(new BothGearInformation(originalNormal));
			m_normalColors.push_back(m_errorColor);
			++colorCounter;
		}
	}
	assert(m_normalColors.size() == allMatingPoints->size());
	assert(m_normalColors.size() == m_normals->size());

	//tooth profiles:
	MatingGearConstructionInformationPart originalToothProfile =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(originalUsedPoints),
			m_toothProfileColor * m_additionalOriginColor,
			"Used Points Of Original Gear",
			HP_POINT_CLOUD);
	MatingGearConstructionInformationPart matingToothProfile =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(matingPoints),
			m_toothProfileColor * m_additionalMatingColor,
			"Constructed Points Of Mating Gear",
			HP_POINT_CLOUD);
	
	m_toothProfiles = new BothGearInformation(originalToothProfile, matingToothProfile);
}

MatingGearConstructionInformation::~MatingGearConstructionInformation() {}

void MatingGearConstructionInformation::setNormalLength(hpreal length) {
	m_normalLength = length;
}

void MatingGearConstructionInformation::setDarkingOfNormals(bool darkened) {
	m_maskNormalsActivated = darkened;
	recolorNormals();
}

void MatingGearConstructionInformation::setAdditionalOriginColor(hpcolor color) {
	m_additionalOriginColor = color;
	recolorNormals();
	m_referenceCircles->originPart.color = m_referenceCircleColor * m_additionalOriginColor;
	m_toothProfiles->originPart.color = m_toothProfileColor * m_additionalOriginColor;
}

void MatingGearConstructionInformation::setAdditionalMatingColor(hpcolor color) {
	m_additionalMatingColor = color;
	recolorNormals();
	m_referenceCircles->matingPart.color = m_referenceCircleColor * m_additionalMatingColor;
	m_toothProfiles->matingPart.color = m_toothProfileColor * m_additionalMatingColor;
}

void MatingGearConstructionInformation::setMaskingColor(hpcolor color) {
	m_maskingColor = color;
}

void MatingGearConstructionInformation::recolorNormals() {
	assert(m_normals->size() == m_normalColors.size());
	for(hpuint i = 0; i < m_normals->size(); ++i) {
		hpcolor color = (m_maskAllActivated || m_maskNormalsActivated) ? m_maskingColor : m_normalColors[i];
		(*m_normals)[i]->originPart.color = color * m_additionalOriginColor;
		if((*m_normals)[i]->hasTwoParts) {
			(*m_normals)[i]->matingPart.color = m_normalColors[i] * m_additionalMatingColor;
		}
	}
}

//TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO 
//Use shared ptr instead of this, as no one knows when these things should and will be deleted!!!
BothGearInformation* MatingGearConstructionInformation::getReferenceCircles() {
	return m_referenceCircles;
}
BothGearInformation* MatingGearConstructionInformation::getToothProfiles() {
	return m_toothProfiles;
}
std::vector<BothGearInformation*>* MatingGearConstructionInformation::getNormals() {
	return m_normals;
}



BSplineCurve<hpvec2>* MatingGearConstructionInformation::normalLine(hpvec2 start, hpvec2 normal) {
	BSplineCurve<hpvec2>* line = new BSplineCurve<hpvec2>();
	line->setDegree(1);
	line->setPeriodic(false);
	line->addControlPoint(start);
	line->addControlPoint(start + m_normalLength * 0.8f * normal);
	line->addControlPoint(start + m_normalLength * normal);
	return line;
}

BSplineCurve<hpvec2>* MatingGearConstructionInformation::circle(hpreal radius, hpvec2 offset) {
	std::vector<hpvec2> circlePoints(16);
	for(unsigned int i = 0; i < 16; ++i) {
		hpreal alpha = M_PI * i / 8;
		circlePoints[i] = hpvec2(offset.x + radius * sin(alpha), offset.y + radius * cos(alpha));
	}
	BSplineCurve<hpvec2>* circle = new BSplineCurve<hpvec2>();
	circle->interpolatePoints(circlePoints);
	circle->setPeriodic(true);
	return circle;
}
