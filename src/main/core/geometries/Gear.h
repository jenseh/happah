#ifndef GEAR_H
#define GEAR_H

#include "NonDrawable.h"
#include <glm/glm.hpp>
#include "../../HappahTypes.h"
#include "../models/TriangleMesh.h"
#include "../models/QuadMesh.h"

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
	Gear(std::string name);
	~Gear();

	virtual hpreal getAngularPitch() = 0;
	virtual uint getToothCount() = 0;
	virtual hpreal getFacewidth() = 0;
	virtual std::vector<hpvec2>* getToothProfile() = 0;
	virtual std::vector<hpvec2>* getGearProfile(hpreal depth) = 0;
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

};


#endif //GEAR_H