#include "WormGenerator.h"

Worm_ptr WormGenerator::generateWormFrom(InvoluteGear_ptr involuteGear) {

	return Worm_ptr(new Worm(involuteGear->getNumberOfTeeth(),
			involuteGear->getModule(),
			involuteGear->getPressureAngle()));
}

//Worm_ptr WormGenerator::generateWormFrom(StandardProfile* profile, hpuint toothCount, hpuint rotations, hpreal faceWidth) {
//    return Worm_ptr(new Worm(profile, toothCount, rotations, faceWidth));
//}
