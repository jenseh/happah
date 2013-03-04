#ifndef GEAR_H
#define GEAR_H

#include <glm/glm.hpp>
#include <vector>
#include "happah/geometries/NonDrawable.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/TriangleMesh.h"
#include "happah/geometries/QuadMesh.h"

/** @class Gear
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
 * parameters (module, radius, toothcount,...) or with point clouds,
 * this class holds only the few methods which all representations have.
 * 
 * Besides that it implements the toTriangleMesh() and toQuadMesh() methods,
 * as these will be the same for most Gears.
 */
class Gear: public NonDrawable {

public:
	Gear(std::string name = "Gear");
	~Gear();
	/** @brief Get a 2D representation of the transverse profile (Stirnprofil)
	 *
	 * @param z cut is made at depth z of the gear
	 */
	//virtual BSlineCurve* toTransverseToothProfileSystem(hpreal z) = 0;
	
	//Following would be nice for the future
	/** @brief Get a 2D representation of the Gear cut at sectionalPlane
	 */
	//virtual BSplineCurve* toToothProfileSystem(std::vector<hpvec4>sectionalPlane) = 0;

	virtual hpreal getAngularPitch() = 0;
	virtual uint   getToothCount() = 0;
	virtual hpreal getFacewidth() = 0;
	virtual hpreal getHelixAngle() = 0;
	virtual bool   toothProfileIsInClockDirection();
	//getToothProfile should return all points of one tooth,
	//even the last point, which must be the same one as the
	//first one of next tooth will be.
	virtual std::vector<hpvec2>* getToothProfile() = 0;
	//getGearProfile can use getToothProfile but has to bear in mind
	//that no two points may lay on each other - so special care is
	//needed for first and last point of the tooth profile.
	virtual std::vector<hpvec2>* getGearProfile(hpreal depth);
	TriangleMesh* toTriangleMesh(); //from NonDrawable
	QuadMesh* toQuadMesh(); //from NonDrawable

protected:
	const static uint TOOTH_SAMPLE_SIZE = 100;
	const static uint WIDTH_SAMPLE_SIZE = 10;

private:
	std::vector<hpvec4>* toMesh(void (Gear::*putTogetherAs)(const hpvec4(&)[4], std::vector<hpvec4>*&));
	void putTogetherAsTriangles(const hpvec4 (&points)[4], std::vector<hpvec4> *&vertexData);
	void putTogetherAsQuads(const hpvec4 (&points)[4], std::vector<hpvec4> *&vertexData);
	void smoothTriangleMeshNormals(std::vector<hpvec4> *&vertexData);

public:
void printVec4(hpvec4 vec) {
	std::cerr << "[ " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " ]" << std::endl;
}
void printVec3(hpvec3 vec) {
	std::cerr << "[ " << vec.x << ", " << vec.y << ", " << vec.z << " ]" << std::endl;
}

};


#endif //GEAR_H
