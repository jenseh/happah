#ifndef CYLINDRICALGEAR_H
#define CYLINDRICALGEAR_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

using namespace std;

#include "happah/HappahTypes.h"
#include "happah/geometries/Geometry.h"
#include "happah/geometries/TriangleMesh.h"

/** @class CylindricalGear
 * @brief Simplest Gear class
 *
 * This class is only for gears with finite radius and therefore it differs
 * from the class Rack. Although in theory a gear with an infinite radius
 * is a rack, with this distinction we can ensure that every Gear has a
 * well-defined rotational axis.
 * 
 * The rotational axis of the gear lies on the z-axis and is centered
 * at (x, y) = (0, 0)
 * 
 * As there are different possibilities to define a gear, like with
 * parameters (module, radius, number of teeth,...) or with point clouds,
 * this class holds only the few methods which all representations have.
 * 
 * Besides it implements the toTriangleMesh() method as this will be the
 * same for most Gears.
 */
class CylindricalGear: public Geometry {

public:
	CylindricalGear();
	~CylindricalGear();
	/** @brief Get a 2D representation of the transverse profile (Stirnprofil)
	 *
	 * @param z cut is made at depth z of the gear
	 */
	//virtual BSlineCurve* toTransverseToothProfileSystem(hpreal z) = 0;
	
	//Following would be nice for the future
	/** @brief Get a 2D representation of the CylindricalGear cut at sectionalPlane
	 */
	//virtual BSplineCurve* toToothProfileSystem(vector<hpvec4>sectionalPlane) = 0;

	virtual hpreal getAngularPitch() = 0;
	virtual hpuint getNumberOfTeeth() = 0;
	virtual hpreal getFaceWidth() = 0;
	virtual hpreal getHelixAngle() = 0;
	//getToothProfile should return all points of one tooth,
	//even the last point, which must be the same one as the
	//first one of next tooth.
	virtual void getToothSpaceProfile(vector<hpvec2>& profile) = 0;
	virtual void getToothProfile(vector<hpvec2>& toothProfile) = 0;
	//getTraverseProfile can use getToothProfile but has to bear in mind
	//that no two points may lay on each other - so special care is
	//needed for first and last point of the tooth profile.
	virtual void getTraverseProfile(hpreal z, vector<hpvec2>& gearProfile);
	//nPointsPerTooth is the number of points used to sample one tooth
	//in such a way, that one whole tooth will consist of nPointsPerTooth + 1
	//points (as last points equals first point of next tooth) and the whole
	//gear will consist of nPointsPerTooth * getNumberOfTeeth() points.
	//nTraverseProfiles is the number of samples used to sample along the z axis
	//whereas nTraverseProfiles = 10 means, that the TriangleMesh will consist of
	//11 gear profiles with 10 intervals
	TriangleMesh3D* toTriangleMesh(hpuint nPointsPerTooth = 100, hpuint nTraverseProfiles = 10);

};

typedef shared_ptr<CylindricalGear> CylindricalGear_ptr;

#endif //CYLINDRICALGEAR_H
