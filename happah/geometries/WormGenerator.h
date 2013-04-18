#ifndef WORMGENERATOR_H_
#define WORMGENERATOR_H_

#include "happah/geometries/gears/CylindricalGear.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/gears/Worm.h"

class WormGenerator
{
public:
    static Worm_ptr generateWormFrom(InvoluteGear_ptr involuteGear);
//    static Worm_ptr generateWormFrom(StandardProfile* profile, hpuint toothCount, hpuint rotations, hpreal faceWidth);
};

#endif /* WORMGENERATOR_H_ */
