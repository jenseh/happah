#ifndef MATINGGEARCONSTRUCTIONINFORMATIONPART_H
#define MATINGGEARCONSTRUCTIONINFORMATIONPART_H

#include <string>

#include "happah/geometries/BSplineCurve.h"
#include "happah/geometries/gears/ToothProfile.h"
#include "happah/HappahTypes.h"
#include "happah/HappahConstants.h"

struct MatingGearConstructionInformationPart {
	BSplineCurve2D_ptr curve;
	hpcolor color;
	string name;
	Flags drawModes;
	MatingGearConstructionInformationPart(BSplineCurve2D_ptr curve, hpcolor color, string name, Flags drawModes) : curve(curve), color(color), name(name), drawModes(drawModes) {}
	MatingGearConstructionInformationPart(const MatingGearConstructionInformationPart& part) : curve(part.curve), color(part.color), name(part.name), drawModes(part.drawModes) {}
	~MatingGearConstructionInformationPart() {}
};

struct MatingGearToothProfilePart {
	ToothProfile_ptr toothProfile;
	hpcolor color;
	string name;
	Flags drawModes;
	MatingGearToothProfilePart(ToothProfile_ptr toothProfile, hpcolor color, string name, Flags drawModes) : toothProfile(toothProfile), color(color), name(name), drawModes(drawModes) {}
	~MatingGearToothProfilePart() {}
};

struct BothGearInformation {

	bool hasTwoParts;
	MatingGearConstructionInformationPart matingPart, originPart;

	BothGearInformation(const MatingGearConstructionInformationPart& part) :
		hasTwoParts(false),
		matingPart(part),
		originPart(part) {}
	BothGearInformation(const MatingGearConstructionInformationPart& part1, const MatingGearConstructionInformationPart& part2) :
		hasTwoParts(true),
		matingPart(part2),
		originPart(part1) {}
};

#endif // MATINGGEARCONSTRUCTIONINFORMATIONPART_H