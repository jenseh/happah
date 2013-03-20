#include "happah/geometries/Disc.h"

#ifndef GEARPROFILEDISC_H_
#define GEARPROFILEDISC_H_

class GearProfileDisc: public Disc{
public:
	GearProfileDisc(Gear& gear);
	virtual ~GearProfileDisc();

	hpreal getRadius();
	void setRadius(hpreal radius) {}

private:
	Gear& m_gear;
	hpreal m_radius;

	void createHeightProfile();
};

#endif /* GEARPROFILEDISC_H_ */
