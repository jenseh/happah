#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include "../geometries/Disc.h"
#include "../geometries/InvoluteSpurGear.h"
#include "../kdtree/TriangleKDTree.h"
#include "../primitives/Color.h"

class DiscGearGrind
{
public:
    DiscGearGrind(Disc* disc, InvoluteSpurGear* gear);
    ~DiscGearGrind();

    void runSimulation();
    Drawable* calculateGrindingDepth();

private:
    Disc* m_disc;
    InvoluteSpurGear* m_gear;

};

#endif // DISCGEARGRIND_H
