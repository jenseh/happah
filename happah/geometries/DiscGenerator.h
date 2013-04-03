#ifndef GRINDINGWHEEL_H
#define GRINDINGWHEEL_H
#include "happah/geometries/gears/Gear.h"
#include "happah/geometries/StandardProfile.h"
#include "happah/geometries/SurfaceOfRevolution.h"

class DiscGenerator
{
	static void invertProfile(std::vector<hpvec2>& profile);
public:
    static SurfaceOfRevolution_ptr generateDiscFrom(Gear& gear);
    static SurfaceOfRevolution_ptr generateDiscFrom(StandardProfile profile);
};

#endif // GRINDINGWHEEL_H
