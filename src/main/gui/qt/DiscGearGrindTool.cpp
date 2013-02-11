#include "DiscGearGrindTool.h"

DiscGearGrindTool::DiscGearGrindTool()
{
    getToolButton()->setText("D");

    QVBoxLayout* vbox = new QVBoxLayout();
    QGroupBox* gbox = new QGroupBox("Simulation Settings");
    vbox->addWidget(gbox);
    getToolSettings()->setLayout(vbox);

    m_timeSlider = new GearSlider(tr("time"), false);

    QPushButton* createButton  = new QPushButton("create simulation");

    vbox = new QVBoxLayout();
    vbox->addWidget(m_timeSlider);
    vbox->addWidget(createButton);

    gbox->setLayout(vbox);

    connect(createButton,  SIGNAL(clicked()), this, SLOT(createSimulation()));
    connect(m_timeSlider,      SIGNAL(valueChanged(hpreal)), this, SLOT(changeTime(hpreal)));

    setInitialState();
}

DiscGearGrindTool::~DiscGearGrindTool(){

}


void DiscGearGrindTool::createSimulation(){
    m_gear = new InvoluteSpurGear();
    m_disc = new Disc();
    m_simulation = new DiscGearGrind(m_disc, m_gear);
    m_gearMesh = m_simulation->getDisplay(m_time);
    emit emitComponent(new RenderItem3D(m_gear, m_gearMesh, "Gear: simulation result"));
}
void DiscGearGrindTool::changeTime(hpreal time){
    m_time = time*0.01;
    updateSimulation();
}

void DiscGearGrindTool::updateSimulation(){
    m_gearMesh = m_simulation->getDisplay(m_time);
    emit emitComponent(new RenderItem3D(m_gear, m_gearMesh, "Gear: simulation result"));
}

void DiscGearGrindTool::setInitialState(){
    m_time = 0.0;
    m_timeSlider->setSliderValues(m_time*100.0, 0, 100);
}

