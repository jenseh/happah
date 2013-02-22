#include "DiscGearGrindTest.h".h"

DiscGearGrindTest::DiscGearGrindTest()
{
    m_disc = new Disc;
    m_gear = new InvoluteSpurGear;
    m_simulation = new DiscGearGrind(m_disc, m_gear);
    std::cout<<"Test init done\n";
}

Drawable* DiscGearGrindTest::runSimulation(double t){
    std::cout<<"Start calculating grinding depth\n";
    return m_simulation->getDisplay(t).first;
}


