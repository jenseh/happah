#ifndef WORMGENERATOR_H_
#define WORMGENERATOR_H_

#include "happah/geometries/gears/CylindricalGear.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/gears/Worm.h"

class WormGenerator
{
public:
    static Worm_ptr generateWormFrom(InvoluteGear_ptr involuteGear);
};

#endif /* WORMGENERATOR_H_ */
