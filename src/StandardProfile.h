#ifndef STANDARDPROFILE_H
#define STANDARDPROFILE_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include <vector>

class StandardProfile
{
    // Werden uebergeben
    double mModul;
    double mDegree; // Flankenwinkel
    double rootCircleRadius;// Fussrundungsradius
    double mCP; // Kopfspiel

    // Werden aus Modul und Winkel berechnet
    // X Start Werte
    double mFlankStart; // Anfang der Flanken
    double mFloorCyrcleStart; // Fussrundungsanfang
    double mFloorStart; // X Anfang des Bodens
    // Y Formeln der Komponenten
    // Flanken Formeln
    double mSlopeFlank; // Steigung
    double mCFlank; // Y-Achsenabschnitt
    // Fussrundung
    double mFloorCyrcleMiddle[2];

    void normalize(double& x)const;

public:
    StandardProfile(double modul, double degree, double radius, double cp);

    double getHeight(double x)const; // gibt Hoehe auf interval [0,1] zurueck //TODO: fix

    void getProfilePartition(std::vector<glm::vec2>& partition, int numberSamples);
};

#endif // STANDARDPROFILE_H
