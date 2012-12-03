#ifndef STANDARDPROFILE_H
#define STANDARDPROFILE_H

#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include <iostream>

class StandardProfile {
public:
	StandardProfile(double module, double pressureAngle, // pressureAngle = Profilwinkel
            double filletRadius,                         // filletRadius = Fußrundungsradius
			double bottomClearance);                     // bottomClearance = Kopfspiel

	double getHeight(double x) const;

	void getProfilePartition(std::vector<glm::vec2>& partition,
			int numberSamples);

private:
    double module_;
    double pressureAngle_; // Flankenwinkel
    double filletRadius_; // Fussrundungsradius
    double bottomClearance_; // Kopfspiel

    void normalize(double& x) const;
    void calcRootCircleCenter(double *center) const;

};

#endif // STANDARDPROFILE_H
