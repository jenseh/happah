#include "DiscGenerator.h"



SurfaceOfRevolution_ptr DiscGenerator::generateDiscFrom(CylindricalGear& cylindricalGear) {
    std::vector<hpvec2> profile;
    profile.reserve(100);
    cylindricalGear.getToothSpaceProfile(profile);
    invertProfile(profile);
    return SurfaceOfRevolution_ptr(new SurfaceOfRevolution(profile));
}

SurfaceOfRevolution_ptr DiscGenerator::generateDiscFrom(StandardProfile profile) {
    std::vector<hpvec2> vertexData;
    vertexData.reserve(50);
    profile.getProfilePartition(vertexData);
    invertProfile(vertexData);
    return SurfaceOfRevolution_ptr(new SurfaceOfRevolution(vertexData));
}

void DiscGenerator::invertProfile(std::vector<hpvec2>& profile) {
	hpreal maxY = 0;
	for(std::vector<hpvec2>::iterator it = profile.begin(); it != profile.end(); ++it ) {
		maxY = glm::max(maxY, it->y);
	}
	for(std::vector<hpvec2>::iterator it = profile.begin(); it != profile.end(); ++it ) {
		it->y = glm::abs(it->y - maxY);
	}
}
