#include "standartprofile.h"


StandartProfile::StandartProfile(double modul,double degree, double rootCircleRadius, double cp):
    mModul(modul), mDegree(degree), rootCircleRadius(rootCircleRadius), mCP(cp)
{
    rootCircleRadius /= mModul;
    // x = y / m
    // m = 1 / tan(degree) , y( Höhe) = 2
    // m = tan(90°-winkel)
    mSlopeFlank = -tan(0.5*M_PI-degree);
    mSlopeFlank *= M_PI; // Streckungsfaktor
    double flankWidth = 2.0 / (-mSlopeFlank);
    double floorWidth = 0.25*(1.0 - 2*flankWidth);
    mFloorStart = 0.5 - floorWidth; // Wert ohne Fußrundung
    mFlankStart = 0.5 - floorWidth - flankWidth; // Ohne Kopfrundung

    // Flanken gleichung berechnen ( y = xm + c )
    // c = y -m*x
    mCFlank = -1.0 - mSlopeFlank*mFloorStart;

    // Fußbodenrundungsgleichung berechnen
    // diesmal Flanken in andere richtung verschieben
    double deltaY = -rootCircleRadius / sin(mDegree);
    // Schnittpunkt mit nach oben verschobenen Boden
    mFloorCyrcleMiddle[1] = rootCircleRadius - 1.0 - mCP;
    mFloorCyrcleMiddle[0] = (mFloorCyrcleMiddle[1] - mCFlank + deltaY) / mSlopeFlank;
    // Kreis tangiert boden unter mittlepunkt
    mFloorStart = mFloorCyrcleMiddle[0]; // Wert mit Fußrundung
    // Berührpunkt mit flanke berechnen
    double cTemp =  (mFloorCyrcleMiddle[1]+(1/mSlopeFlank)*mFloorCyrcleMiddle[0]); // Y Achsenabschnitt berechnen
    mFloorCyrcleStart = (cTemp - mCFlank) / (mSlopeFlank + (1.0/mSlopeFlank)); // geraden schneiden

}

void StandartProfile::normalize(double& x)const{
    x /= (mModul*M_PI);
    // Modulo
    while( x - 1.0 > 0){
        x -= 1.0;
    }
    // Spiegeln
    if( x > 0.5 ){
        x = 1.0 - x;
    }
}

double StandartProfile::getHeight(double x)const{
    normalize(x);
    if( x < mFlankStart ){
        // Kopf
        return mModul;
    }else if( x < mFloorCyrcleStart){
        // Flanke
        return mModul*(x*mSlopeFlank + mCFlank);
    }else if( x < mFloorStart){
        // Fußrundung
        double tempX = mFloorCyrcleMiddle[0]-x;
        // y² = r²-y²
        return mModul*(mFloorCyrcleMiddle[1] - sqrt((rootCircleRadius*rootCircleRadius) - (tempX*tempX)));
    }else{
        // Fuß
        return mModul*(-1.0- mCP);
    }
}


void StandartProfile::getProfilePartition(std::vector<glm::vec2>& partition, int numberSamples){
    for(int i = 0; i < numberSamples; i++){
        double x = ((double)i / (double)numberSamples)*mModul*M_PI;
        double y = getHeight(x);
        partition.push_back(glm::vec2(x,y));
    }

}
