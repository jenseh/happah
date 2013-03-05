#ifndef DISCGEARGRINDTEST_H
#define DISCGEARGRINDTEST_H


#include "../core/geometries/Disc.h"
#include "../core/geometries/InvoluteGear.h"
#include "../core/simulations/DiscGearGrind.h"

class DiscGearGrindTest
{
    DiscGearGrind* m_simulation;
    Disc* m_disc;
    InvoluteGear* m_gear;

public:
    DiscGearGrindTest();

    Drawable* runSimulation(double t);
};
#endif // DISCGEARGRINDTEST_H
