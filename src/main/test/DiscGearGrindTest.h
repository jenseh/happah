#ifndef DISCGEARGRINDTEST_H
#define DISCGEARGRINDTEST_H


#include "../core/geometries/Disc.h"
#include "../core/geometries/InvoluteSpurGear.h"
#include "../core/simulations/DiscGearGrind.h"

class DiscGearGrindTest
{
    DiscGearGrind* m_simulation;
    Disc* m_disc;
    InvoluteSpurGear* m_gear;

public:
    DiscGearGrindTest();

    Drawable* runSimulation();
};

#endif // DISCGEARGRINDTEST_H
