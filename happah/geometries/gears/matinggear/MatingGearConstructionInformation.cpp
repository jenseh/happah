#include "happah/geometries/gears/matinggear/MatingGearConstructionInformation.h"

MatingGearConstructionInformation::MatingGearConstructionInformation(MatingGearConstructor* constructor)
  : m_constructor(constructor),
	m_maskAllActivated(false),
	m_maskNormalsActivated(false),
	m_normalLength(1.0f) {

	//Default Colors
	m_additionalMatingColor = hpcolor(1.0f, 1.0f, 1.0f, 1.0f);
	m_additionalOriginColor = hpcolor(0.8f, 0.8f, 0.8f, 1.0f);
	m_angularPitchColor =     hpcolor(0.1f, 0.2f, 0.4f, 1.0f);
	m_maskingColor =          hpcolor(0.0f, 0.0f, 0.0f, 1.0f);
	m_errorColor =            hpcolor(1.0f, 0.0f, 0.0f, 1.0f);
	m_referenceCircleColor =  hpcolor(0.1f, 0.1f, 0.7f, 1.0f);
	m_toothProfileColor =     hpcolor(0.1f, 0.4f, 0.5f, 1.0f);

	std::list<MatingPoint>* allMatingPoints = m_constructor->getMatingPointList();

	std::vector<hpcolor> normalColors(allMatingPoints->size());
	fillRainbowColorArray(normalColors);

	//Vector between centers
	hpvec2 toMatingCenter = hpvec2(m_constructor->getOriginalGearReferenceRadius() + m_constructor->getMatingGearReferenceRadius(), 0.0f);

	//Reference Circles
	MatingGearConstructionInformationPart originReferenceRadius =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(circle(m_constructor->getOriginalGearReferenceRadius(), hpvec2(0.0f, 0.0f))),
			m_referenceCircleColor * m_additionalOriginColor,
			"Original gear ref circle",
			HP_LINE_MESH);

	MatingGearConstructionInformationPart matingReferenceRadius =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(circle(m_constructor->getMatingGearReferenceRadius(), toMatingCenter)),
			m_referenceCircleColor * m_additionalMatingColor,
			"Mating gear ref circle",
			HP_LINE_MESH);

	m_referenceCircles = new BothGearInformation(originReferenceRadius, matingReferenceRadius);

	//Angular Pitches
	std::vector<hpvec2>* angularOriginPitchPoints = m_constructor->getOriginalAngularPitchPoints();
	BSplineCurve<hpvec2>* angularOriginPitches = new BSplineCurve<hpvec2>();
	angularOriginPitches->setPeriodic(false);
	angularOriginPitches->setDegree(1);
	for(hpuint i = 0; i < angularOriginPitchPoints->size(); ++i) {
		angularOriginPitches->addControlPoint(hpvec2(0.0f, 0.0f));
		angularOriginPitches->addControlPoint((*angularOriginPitchPoints)[i]);
	}
	angularOriginPitches->addControlPoint(hpvec2(0.0f));
	MatingGearConstructionInformationPart angularOriginPitchPart = 
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(angularOriginPitches),
			m_angularPitchColor * m_additionalOriginColor,
			"Original gear angular pitches",
			HP_LINE_MESH);
	delete angularOriginPitchPoints;

	std::vector<hpvec2>* angularMatingPitchPoints = m_constructor->getMatingAngularPitchPoints();
	BSplineCurve<hpvec2>* angularMatingPitches = new BSplineCurve<hpvec2>();
	angularMatingPitches->setPeriodic(false);
	angularMatingPitches->setDegree(1);
	for(hpuint i = 0; i < angularMatingPitchPoints->size(); ++i) {
		angularMatingPitches->addControlPoint(toMatingCenter);
		angularMatingPitches->addControlPoint(toMatingCenter + (*angularMatingPitchPoints)[i]);
	}
	angularMatingPitches->addControlPoint(toMatingCenter);
	MatingGearConstructionInformationPart angularMatingPitchPart = 
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(angularMatingPitches),
			m_angularPitchColor * m_additionalMatingColor,
			"Original gear angular pitches",
			HP_LINE_MESH);
	delete angularMatingPitchPoints;

	m_angularPitches = new BothGearInformation(angularOriginPitchPart, angularMatingPitchPart);

	//Tooth Profiles And Normals
	BSplineCurve<hpvec2>* originalUsedPoints = new BSplineCurve<hpvec2>();
	BSplineCurve<hpvec2>* matingPoints = new BSplineCurve<hpvec2>();

	m_normals = new std::vector<BothGearInformation*>();
	m_normals->reserve(allMatingPoints->size());
	m_normalColors = std::vector<hpcolor>();
	m_normalColors.reserve(allMatingPoints->size());

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

	cerr << "MatingGearConstructionInformation::MatingGearConstructionInformation is before iterator " << endl;
	m_normalsIterator = m_normals->begin();

	//tooth profiles:
	MatingGearConstructionInformationPart originalToothProfile =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(originalUsedPoints),
			m_toothProfileColor * m_additionalOriginColor,
			"Used Points Of Original Gear",
			static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
	MatingGearConstructionInformationPart matingToothProfile =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(matingPoints),
			m_toothProfileColor * m_additionalMatingColor,
			"Constructed Points Of Mating Gear",
			static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
	
	m_toothProfiles = new BothGearInformation(originalToothProfile, matingToothProfile);

	delete allMatingPoints;
}

MatingGearConstructionInformation::~MatingGearConstructionInformation() {
	for(auto it = m_normals->begin(), end = m_normals->end(); it != end; ++it) {
		delete (*it);
	}
	delete m_normals;
	delete m_referenceCircles;
	delete m_toothProfiles;
}

bool MatingGearConstructionInformation::areFurtherNormalsAvailable() {
	return m_normalsIterator != m_normals->end();
}

BothGearInformation* MatingGearConstructionInformation::getAngularPitches() {
	return m_angularPitches;
}

BothGearInformation* MatingGearConstructionInformation::getNextNormal() {
	if(m_normalsIterator == m_normals->end()) {
		m_normalsIterator = m_normals->begin();
		//if no normals available return nullptr
		if(m_normalsIterator == m_normals->end()) {
			return nullptr;
		}
	}
	BothGearInformation* nextNormal = *m_normalsIterator;
	++m_normalsIterator;
	return nextNormal;
}

std::vector<BothGearInformation*>* MatingGearConstructionInformation::getNormals() {
	//because all normals are fetched, the normals iterator is set to the end to indicate that one has used it already
	m_normalsIterator = m_normals->end();
	return m_normals;
}

BothGearInformation* MatingGearConstructionInformation::getReferenceCircles() {
	return m_referenceCircles;
}

BothGearInformation* MatingGearConstructionInformation::getToothProfiles() {
	return m_toothProfiles;
}

void MatingGearConstructionInformation::setAdditionalMatingColor(hpcolor color) {
	m_additionalMatingColor = color;
	recolorNormals();
	m_referenceCircles->matingPart.color = m_referenceCircleColor * m_additionalMatingColor;
	m_toothProfiles->matingPart.color = m_toothProfileColor * m_additionalMatingColor;
}

void MatingGearConstructionInformation::setAdditionalOriginColor(hpcolor color) {
	m_additionalOriginColor = color;
	recolorNormals();
	m_referenceCircles->originPart.color = m_referenceCircleColor * m_additionalOriginColor;
	m_toothProfiles->originPart.color = m_toothProfileColor * m_additionalOriginColor;
}

void MatingGearConstructionInformation::setDarkingOfNormals(bool darkened) {
	m_maskNormalsActivated = darkened;
	recolorNormals();
}

void MatingGearConstructionInformation::setMaskingColor(hpcolor color) {
	m_maskingColor = color;
}

void MatingGearConstructionInformation::setNormalLength(hpreal length) {
	m_normalLength = length;
}

void MatingGearConstructionInformation::update() {

	std::list<MatingPoint>* allMatingPoints = m_constructor->getMatingPointList();

	std::vector<hpcolor> normalColors(allMatingPoints->size());
	fillRainbowColorArray(normalColors);

	//Vector between centers
	hpvec2 toMatingCenter = hpvec2(m_constructor->getOriginalGearReferenceRadius() + m_constructor->getMatingGearReferenceRadius(), 0.0f);

	//Reference Circles
	m_referenceCircles->originPart = MatingGearConstructionInformationPart(
		BSplineCurve2D_ptr(circle(m_constructor->getOriginalGearReferenceRadius(), hpvec2(0.0f, 0.0f))),
		m_referenceCircleColor * m_additionalOriginColor,
		"Original gear ref circle",
		HP_LINE_MESH);

	m_referenceCircles->matingPart = MatingGearConstructionInformationPart(
		BSplineCurve2D_ptr(circle(m_constructor->getMatingGearReferenceRadius(), toMatingCenter)),
		m_referenceCircleColor * m_additionalMatingColor,
		"Mating gear ref circle",
		HP_LINE_MESH);

	//Angular Pitches
	std::vector<hpvec2>* angularOriginPitchPoints = m_constructor->getOriginalAngularPitchPoints();
	BSplineCurve<hpvec2>* angularOriginPitches = new BSplineCurve<hpvec2>();
	angularOriginPitches->setPeriodic(false);
	angularOriginPitches->setDegree(1);
	for(hpuint i = 0; i < angularOriginPitchPoints->size(); ++i) {
		angularOriginPitches->addControlPoint(hpvec2(0.0f, 0.0f));
		angularOriginPitches->addControlPoint((*angularOriginPitchPoints)[i]);
	}
	angularOriginPitches->addControlPoint(hpvec2(0.0f));
	m_angularPitches->originPart.curve = BSplineCurve2D_ptr(angularOriginPitches);
	delete angularOriginPitchPoints;

	std::vector<hpvec2>* angularMatingPitchPoints = m_constructor->getMatingAngularPitchPoints();
	BSplineCurve<hpvec2>* angularMatingPitches = new BSplineCurve<hpvec2>();
	angularMatingPitches->setPeriodic(false);
	angularMatingPitches->setDegree(1);
	for(hpuint i = 0; i < angularMatingPitchPoints->size(); ++i) {
		angularMatingPitches->addControlPoint(toMatingCenter);
		angularMatingPitches->addControlPoint(toMatingCenter + (*angularMatingPitchPoints)[i]);
	}
	angularMatingPitches->addControlPoint(toMatingCenter);
	m_angularPitches->matingPart.curve = BSplineCurve2D_ptr(angularMatingPitches);

	//Tooth Profiles And Normals
	BSplineCurve<hpvec2>* originalUsedPoints = new BSplineCurve<hpvec2>();
	BSplineCurve<hpvec2>* matingPoints = new BSplineCurve<hpvec2>();

	hpuint oldSize = m_normals->size();

	m_normals->reserve(allMatingPoints->size());
	m_normalColors = std::vector<hpcolor>();
	m_normalColors.reserve(allMatingPoints->size());

	hpuint colorCounter = 0;
	hpuint i = 0;
	for(auto it = allMatingPoints->begin(), end = allMatingPoints->end(); it != end; ++it) {
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
			if(i < oldSize) {
				(*m_normals)[i]->originPart = originalNormal;
				(*m_normals)[i]->matingPart = matingNormal;
				(*m_normals)[i]->hasTwoParts = true;
				//TODO: better is probably:
				// *(*m_normals[i]) = BothGearInformation(originalNormal, matingNormal);
				//if possible use this here and below!
			} else {
				m_normals->push_back(new BothGearInformation(originalNormal, matingNormal));
			}
			m_normalColors.push_back(normalColors[colorCounter]);
		} else {
			MatingGearConstructionInformationPart originalNormal =
				MatingGearConstructionInformationPart(
					BSplineCurve2D_ptr(normalLine(it->originPoint, it->originNormal)),
					m_errorColor * m_additionalOriginColor,
					"Normal Of Original Gear without cut",
					static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
			if(i < oldSize) {
				(*m_normals)[i]->originPart = originalNormal;
				(*m_normals)[i]->matingPart = originalNormal;
				(*m_normals)[i]->hasTwoParts = false;
			} else {
				m_normals->push_back(new BothGearInformation(originalNormal));
			}
			m_normalColors.push_back(m_errorColor);
		}
		++i;
		++colorCounter;
	}
	//if new size of matingpoints is smaller than old one, the BothGearInformation pointers
	//of the left over m_normals have to be deleted and array has to be resized
	if(i < oldSize) {
		for(auto it = m_normals->begin() + i, end = m_normals->end(); it != end; ++it) {
			delete *it;
		}
		assert(i == allMatingPoints->size());
		m_normals->resize(i);
	}

	cerr << "normalColors: " << m_normalColors.size() << ", allMatingPoints: " << allMatingPoints->size() << ", m_normals: " << m_normals->size() << endl;
	assert(m_normalColors.size() == allMatingPoints->size());
	assert(m_normalColors.size() == m_normals->size());

	m_normalsIterator = m_normals->begin();

	//tooth profiles:
	MatingGearConstructionInformationPart originalToothProfile =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(originalUsedPoints),
			m_toothProfileColor * m_additionalOriginColor,
			"Used Points Of Original Gear",
			static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
	MatingGearConstructionInformationPart matingToothProfile =
		MatingGearConstructionInformationPart(
			BSplineCurve2D_ptr(matingPoints),
			m_toothProfileColor * m_additionalMatingColor,
			"Constructed Points Of Mating Gear",
			static_cast<Flags>(HP_LINE_MESH | HP_POINT_CLOUD));
	
	m_toothProfiles->originPart = originalToothProfile;
	m_toothProfiles->matingPart = matingToothProfile;

	delete allMatingPoints;
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

void MatingGearConstructionInformation::fillRainbowColorArray(std::vector<hpcolor>& normalColors) {
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
