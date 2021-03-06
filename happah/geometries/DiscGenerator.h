#ifndef DISCGENERATOR_H
#define DISCGENERATOR_H
#include "happah/geometries/gears/CylindricalGear.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/SurfaceOfRevolution.h"

class DiscGenerator
{
	static void invertProfile(std::vector<hpvec2>& profile);
public:
    static SurfaceOfRevolution_ptr generateDiscFrom(CylindricalGear& cylindricalGear);
    static SurfaceOfRevolution_ptr generateDiscFrom(StandardProfile profile);
};

#endif // DISCGENERATOR_H
