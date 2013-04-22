#include "WormGenerator.h"

Worm_ptr WormGenerator::generateWormFrom(InvoluteGear_ptr involuteGear) {

	return Worm_ptr(new Worm(
			2,
			involuteGear->getModule(),
			involuteGear->getPressureAngle(),
			1,
			involuteGear->getModule() * 2.0));
}
