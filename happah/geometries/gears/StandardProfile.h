#ifndef STANDARDPROFILE_H
#define STANDARDPROFILE_H

#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include <iostream>

#include "happah/HappahTypes.h"

class StandardProfile {
public:
	StandardProfile(hpreal module, hpreal pressureAngle, // pressureAngle = Profilwinkel
            hpreal filletRadius,                         // filletRadius = Fußrundungsradius
			hpreal bottomClearance);                     // bottomClearance = Kopfspiel

	hpreal getHeight(hpreal x) const;
	hpreal getMaxHeight() const;

    void getProfilePartition(std::vector<glm::vec2>& partition);

private:
    hpreal m_module;
    hpreal m_pressureAngle; // Flankenwinkel
    hpreal m_filletRadius; // Fussrundungsradius
    hpreal m_bottomClearance; // Kopfspiel

    void normalize(hpreal& x) const;
    void calcRootCircleCenter(hpreal *center) const;

};

#endif // STANDARDPROFILE_H
