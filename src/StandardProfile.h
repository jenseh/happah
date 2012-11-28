#ifndef STANDARDPROFILE_H
#define STANDARDPROFILE_H

#include <glm/glm.hpp>
#include <math.h>
#include <vector>

//TODO: replace kopfspiel everywhere with equivalent word in English

class StandardProfile
{
    double module_;
    double profileAngle_; // Flankenwinkel
    double rootCircleRadius_;// Fussrundungsradius
    double kopfspiel_; // Kopfspiel

    void normalize(double& x)const;
    void calcRootCircleCenter(double *center)const;

public:
    StandardProfile(double module, double profileAngle, double rootCircleRadius, double kopfspiel);

    double getHeight(double x)const;

    void getProfilePartition(std::vector<glm::vec2>& partition, int numberSamples);
};

#endif // STANDARDPROFILE_H
