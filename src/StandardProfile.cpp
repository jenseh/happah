#include "StandardProfile.h"


StandardProfile::StandardProfile(double modul,double degree, double rootCircleRadius, double cp):
    mModul(modul), mDegree(degree), rootCircleRadius(rootCircleRadius), mCP(cp)
{
    rootCircleRadius /= mModul;
    // x = y / m
    // m = 1 / tan(degree) , y( Hoehe) = 2
    // m = tan(90degrees-winkel)
    mSlopeFlank = -tan(0.5*M_PI-degree);
    mSlopeFlank *= M_PI; // Streckungsfaktor
    double flankWidth = 2.0 / (-mSlopeFlank);
    double floorWidth = 0.25*(1.0 - 2*flankWidth);
    mFloorStart = 0.5 - floorWidth; // Wert ohne Fussrundung
    mFlankStart = 0.5 - floorWidth - flankWidth; // Ohne Kopfrundung

    // Flanken gleichung berechnen ( y = xm + c )
    // c = y -m*x
    mCFlank = -1.0 - mSlopeFlank*mFloorStart;

    // Fussbodenrundungsgleichung berechnen
    // diesmal Flanken in andere richtung verschieben
    double deltaY = -rootCircleRadius / sin(mDegree);
    // Schnittpunkt mit nach oben verschobenen Boden
    mFloorCyrcleMiddle[1] = rootCircleRadius - 1.0 - mCP;
    mFloorCyrcleMiddle[0] = (mFloorCyrcleMiddle[1] - mCFlank + deltaY) / mSlopeFlank;
    // Kreis tangiert boden unter mittlepunkt
    mFloorStart = mFloorCyrcleMiddle[0]; // Wert mit Fussrundung
    // Beruehrpunkt mit flanke berechnen
    double cTemp =  (mFloorCyrcleMiddle[1]+(1/mSlopeFlank)*mFloorCyrcleMiddle[0]); // Y Achsenabschnitt berechnen
    mFloorCyrcleStart = (cTemp - mCFlank) / (mSlopeFlank + (1.0/mSlopeFlank)); // geraden schneiden

}

void StandardProfile::normalize(double& x)const{
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

double StandardProfile::getHeight(double x)const{
    normalize(x);
    if( x < mFlankStart ){
        // Kopf
        return mModul;
    }else if( x < mFloorCyrcleStart){
        // Flanke
        return mModul*(x*mSlopeFlank + mCFlank);
    }else if( x < mFloorStart){
        // Fussrundung
        double tempX = mFloorCyrcleMiddle[0]-x;
        // y^2 = r^2-y^2
        return mModul*(mFloorCyrcleMiddle[1] - sqrt((rootCircleRadius*rootCircleRadius) - (tempX*tempX)));
    }else{
        // Fuss
        return mModul*(-1.0- mCP);
    }
}


void StandardProfile::getProfilePartition(std::vector<glm::vec2>& partition, int numberSamples){
    for(int i = 0; i < numberSamples; i++){
        double x = ((double)i / (double)numberSamples)*mModul*M_PI;
        double y = getHeight(x);
        partition.push_back(glm::vec2(x,y));
    }

}
