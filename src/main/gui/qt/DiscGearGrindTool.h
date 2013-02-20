#ifndef DISCGEARGRINDTOOL_H
#define DISCGEARGRINDTOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>

#include "../../HappahTypes.h"
#include "Tool.h"
#include "../../core/geometries/InvoluteSpurGear.h"
#include "../../core/geometries/Disc.h"
#include "../../core/simulations/DiscGearGrind.h"
#include "GearSlider.h"
#include "SceneManager3D.h"


class DiscGearGrindTool : public Tool,public SceneListener {
Q_OBJECT

private:
    SceneManager3D* m_sceneManager;
    GearSlider* m_timeSlider;
    hpreal m_time;

    QComboBox m_gearBox;
    QComboBox m_discBox;

    Gear* m_gear;
    TriangleMesh* m_gearMesh;
    Disc* m_disc;
    TriangleMesh* m_discMesh;
    DiscGearGrind* m_simulation;

    void updateSimulation();
    void setInitialState();

public:
    DiscGearGrindTool(SceneManager3D* sceneManager);
    ~DiscGearGrindTool();
    void sceneChanged();

private slots:
    void createSimulation();
    void changeTime(hpreal time);
};

#endif // DISCGEARGRINDTOOL_H
