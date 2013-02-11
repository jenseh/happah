#ifndef DISCGEARGRINDTOOL_H
#define DISCGEARGRINDTOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "../../HappahTypes.h"
#include "Tool.h"
#include "../../core/geometries/InvoluteSpurGear.h"
#include "../../core/geometries/Disc.h"
#include "../../core/simulations/DiscGearGrind.h"
#include "GearSlider.h"


class DiscGearGrindTool : public Tool {
Q_OBJECT

private:
    GearSlider* m_timeSlider;
    hpreal m_time;

    InvoluteSpurGear* m_gear;
    Drawable* m_gearMesh;
    Disc* m_disc;
    DiscGearGrind* m_simulation;

    void updateSimulation();
    void setInitialState();

public:
    DiscGearGrindTool();
    ~DiscGearGrindTool();

private slots:
    void createSimulation();
    void changeTime(hpreal time);
};

#endif // DISCGEARGRINDTOOL_H
