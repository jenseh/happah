#include "happah/geometries/Disc.h"
#include <memory>

#ifndef STANDARDDISC_H_
#define STANDARDDISC_H_

class StandardProfileDisc: public Disc {
public:
	StandardProfileDisc(hpreal radius = 1.0);
	virtual ~StandardProfileDisc();

	hpreal getRadius();
	void setRadius(hpreal radius);

private:
	hpreal m_radius;
    StandardProfile* m_standardProfile;

    void createHeightProfile();
    void updateValues();
};

typedef std::shared_ptr<StandardProfileDisc> StandardProfileDisc_ptr;

#endif /* STANDARDDISC_H_ */
