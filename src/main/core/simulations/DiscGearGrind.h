#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include "../geometries/Disc.h"
#include "../geometries/SpurGear.h"
#include "../kdtree/TriangleKDTree.h"

class DiscGearGrind
{
    Disc* m_disc;
    SpurGear* m_gear;

public:
    DiscGearGrind(Disc* disc, SpurGear* gear);

    void CalculateGrindingDepth();
};

#endif // DISCGEARGRIND_H
