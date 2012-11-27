#ifndef STANDARTPROFILE_H
#define STANDARTPROFILE_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include <vector>

class StandartProfile
{
    // Werden übergeben
    double mModul;
    double mDegree; // Flankenwinkel
    double rootCircleRadius;// Fußrundungsradius
    double mCP; // Kopfspiel

    // Werden aus Modul und Winkel berechnet
    // X Start Werte
    double mFlankStart; // Anfang der Flanken
    double mFloorCyrcleStart; // Fußrundungsanfang
    double mFloorStart; // X Anfang des Bodens
    // Y Formeln der Komponenten
    // Flanken Formeln
    double mSlopeFlank; // Steigung
    double mCFlank; // Y-Achsenabschnitt
    // Fußrundung
    double mFloorCyrcleMiddle[2];

    void normalize(double& x)const;

public:
    StandartProfile(double modul, double degree, double radius, double cp);

    double getHeight(double x)const; // gibt höhe auf interval [0,1] zurück

    void getProfilePartition(std::vector<glm::vec2>& partition, int numberSamples);
};

#endif // STANDARTPROFILE_H
