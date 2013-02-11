#ifndef TOOTHPROFILE_H
#define TOOTHPROFILE_H

#include <vector>
#include "BSplineCurve.h"
#include "../../HappahTypes.h"

/** ToothProfile stellt das planare Zahnprofil eines Zahnes dar.
 * Es ist so ausgerichtet, dass der Ursprung (0,0) das Zentrum
 * des zugehörigen Zahnrades darstellt..
 * Der erste und letzte Punkt des Zahnprofils müssen auf demselben Kreis
 * um das Zahnradzentrum liegen.
 */
class ToothProfile {
public:
	virtual BSplineCurve* getRepresentation() = 0; //TODO
	virtual std::vector<hpvec2>* getAs2DPoints() = 0; //TODO
	virtual void rotate(hpreal angle) = 0;
	/* Checks if the order of the profile is in clock direction
	 * for an x-Axis pointing to the right and an y-Axis
	 * pointing to the top.
	 */
	virtual bool isInClockDirection() = 0;
	/* Checks if the order of the profile is in counter clock direction
	 * for an x-Axis pointing to the right and an y-Axis
	 * pointing to the top.
	 */
	virtual bool isInCounterClockDirection() = 0;
	/* Returns the angular pitch (Teilungswinkel) */
	virtual hpreal getAngularPitch() = 0; //Teilungswinkel

};

#endif //TOOTHPROFILE_H