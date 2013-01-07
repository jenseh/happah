#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include "../geometries/Disc.h"
#include "../geometries/SpurGear.h"
#include "../kdtree/TriangleKDTree.h"

class DiscGearGrind
{
public:
    DiscGearGrind(Disc* disc, SpurGear* gear);
    ~DiscGearGrind();

    void runSimulation();
    vector<Color> calculateGrindingDepth();

private:
    Disc* m_disc;
    SpurGear* m_gear;

};

#endif // DISCGEARGRIND_H
