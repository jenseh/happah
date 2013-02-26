#ifndef DISCGEARGRINDTOOL_H
#define DISCGEARGRINDTOOL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>

#include "happah/HappahTypes.h"
#include "happah/geometries/Disc.h"
#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/gui/qt/GearSlider.h"
#include "happah/gui/qt/SceneManager3D.h"
#include "happah/gui/qt/tools/Tool.h"
#include "happah/simulations/DiscGearGrind.h"


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
