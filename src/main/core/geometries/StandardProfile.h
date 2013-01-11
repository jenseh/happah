#ifndef STANDARDPROFILE_H
#define STANDARDPROFILE_H

#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include <iostream>

#include "../../HappahTypes.h"

class StandardProfile {
public:
	StandardProfile(hpreal module, hpreal pressureAngle, // pressureAngle = Profilwinkel
            hpreal filletRadius,                         // filletRadius = Fußrundungsradius
			hpreal bottomClearance);                     // bottomClearance = Kopfspiel

	hpreal getHeight(hpreal x) const;

	void getProfilePartition(std::vector<glm::vec2>& partition,
			int numberSamples);

private:
    hpreal module_;
    hpreal pressureAngle_; // Flankenwinkel
    hpreal filletRadius_; // Fussrundungsradius
    hpreal bottomClearance_; // Kopfspiel

    void normalize(hpreal& x) const;
    void calcRootCircleCenter(hpreal *center) const;

};

#endif // STANDARDPROFILE_H
