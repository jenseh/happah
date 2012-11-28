#include "StandardProfile.h"
#include <iostream>


StandardProfile::StandardProfile(double module, double profileAngle, double rootCircleRadius, double kopfspiel):
    module_(module), profileAngle_(profileAngle), rootCircleRadius_(rootCircleRadius), kopfspiel_(kopfspiel)
{
    // Angle has to be smaller than approximately 38.146 degrees or 0.785 rad
    if (tan(profileAngle_) > M_PI / 4)
        std::cerr << "ERROR: Your angle is too big with " << profileAngle_ << std::endl;
    if (rootCircleRadius_ > kopfspiel_ / (1 - sin(profileAngle_)) ||
        rootCircleRadius_ > (sin(profileAngle_) / (1 - sin(profileAngle_))) *
                                (((M_PI - 4 * tan(profileAngle_)) / 4 * tan(profileAngle_)) * module_
                                    - kopfspiel_))
        std::cerr << "ERROR: Your rootCircleRadius is too big with " << rootCircleRadius_ << std::endl;
}

void StandardProfile::normalize(double& x)const{
    x /= ( module_ * M_PI );
    // Modulo
    while( x - 1.0 > 0){
        x -= 1.0;
    }
    // Spiegeln
    if( x > 0.5 ){
        x = 1.0 - x;
    }
    x *= ( module_ * M_PI );
}

void StandardProfile::calcRootCircleCenter(double *center)const {
    double t = (kopfspiel_  + rootCircleRadius_ * ( 1 + sin(profileAngle_))) / cos(profileAngle_);
    center[0] = module_ * M_PI
                + cos(profileAngle_) * rootCircleRadius_ + t * sin(profileAngle_);
    center[1] =   sin(profileAngle_) * rootCircleRadius_ - t * cos(profileAngle_);
}

/**
 * Calculates the profiel for one gear pitch.
 * double x has to be bigger than or equal 0.
 * When x = 0 the height at the center of a tooth
 * of the gear is calculated.
 * When x = pitch / 2 the height at the center of
 * the gap between two teeth is calculated.
 */
double StandardProfile::getHeight(double x)const{
    /* Values are only calculated of one half of a pitch.
     * Therefore x is converted to values in [0, m * pi / 2], with
     * m = module. The second half of the pitch is mirrored and
     * therefore we start for x = 0 at a center of one pitch.
     * x_1, ..., x_5 are used for the different regions of a pitch:
     * 
     * 0   <= x < x_1  --> right half of top land
     * x_1 <= x < x_2  --> flank without kopfspiel
     * x_2 <= x < x_3  --> rest of flank until root circle is starting
     * x_3 <= x < x_4  --> region of root circle
     * x_4 <= x < x_5  --> left bottom land (until center of bottom land)
     */
    normalize(x); 
    
    //calculate x-function for half of one pitch

    double x_1 = (module_ * M_PI) / 4 - tan(profileAngle_) * module_;
    double x_2 = (module_ * M_PI) / 4 + tan(profileAngle_) * module_;
    double x_3 = x_2 + (kopfspiel_ +
                        rootCircleRadius_ * (sin(profileAngle_) - 1)) *
                        tan(profileAngle_);
    double x_4 = x_3 + rootCircleRadius_ * cos(profileAngle_);
    double x_5 = (module_ * M_PI) / 2;

    double center[2];
    calcRootCircleCenter(center);

    if      (x < x_1) return module_;
    else if (x < x_3) return (x - (module_ * M_PI) / 4 ) * (-cos(profileAngle_) / sin(profileAngle_));
    else if (x < x_4) return (center[1] -
                                sqrt(rootCircleRadius_ * rootCircleRadius_ - 
                                     (x - center[0]) * (x - center[0])));
    else return -module_ - kopfspiel_;
}


void StandardProfile::getProfilePartition(std::vector<glm::vec2>& partition, int numberSamples){
    for(int i = 0; i < numberSamples; i++){
        double x = ((double)i / (double)numberSamples) * module_ * M_PI;
        double y = getHeight(x);
        partition.push_back(glm::vec2(x,y));
    }

}