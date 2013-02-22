#include "DiscGearGrindTool.h"

DiscGearGrindTool::DiscGearGrindTool(SceneManager3D* sceneManager):m_sceneManager(sceneManager)
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
    //Fill with all gears
    vbox->addWidget(&m_gearBox);
    // Fill with all discs
    vbox->addWidget(&m_discBox);

    vbox->addWidget(createButton);

    gbox->setLayout(vbox);

    connect(createButton,  SIGNAL(clicked()), this, SLOT(createSimulation()));
    connect(m_timeSlider,      SIGNAL(valueChanged(hpreal)), this, SLOT(changeTime(hpreal)));

    setInitialState();
}

DiscGearGrindTool::~DiscGearGrindTool(){
    delete m_timeSlider;
}


void DiscGearGrindTool::createSimulation(){
    /*
    m_gear = new InvoluteSpurGear();
    m_disc = new Disc();
    */
    std::list<SceneManager3D::ManagedItem> items = m_sceneManager->getItems();
    std::list<SceneManager3D::ManagedItem>::iterator it;
    int gearIndex = m_gearBox.currentIndex();
    int discIndex = m_discBox.currentIndex();
    if( gearIndex < items.size() && discIndex < items.size() ){
        it = items.begin();
        std::advance(it, gearIndex);
        m_gear = (Gear*)it->renderItem->getNonDrawable();

        it = items.begin();
        std::advance(it, discIndex);
        m_disc = (Disc*)it->renderItem->getNonDrawable();


        m_simulation = new DiscGearGrind(m_disc, m_gear);
        pair<TriangleMesh*, TriangleMesh*> displayRes = m_simulation->getDisplay(m_time);

        m_discMesh = displayRes.second;
        emit emitComponent(new RenderItem3D(m_disc, m_discMesh, "Disc: simulation result"));

        m_gearMesh = displayRes.first;
        emit emitComponent(new RenderItem3D(m_gear, m_gearMesh, "Gear: simulation result"));
    }
}
void DiscGearGrindTool::changeTime(hpreal time){
    m_time = time*0.01;
    updateSimulation();
}

void DiscGearGrindTool::updateSimulation(){
    if( m_gearMesh != NULL ){
        pair<TriangleMesh*, TriangleMesh*> displayRes = m_simulation->getDisplay(m_time);
        // Does not have to be deleted because the simulation takes care of memory managment
        m_gearMesh = displayRes.first;
        m_discMesh = displayRes.second;
        emit changed();
    }
}

void DiscGearGrindTool::setInitialState(){
    m_time = 0.0;
    m_timeSlider->setSliderValues(m_time*100.0, 0, 100);
    m_gearMesh = NULL;
}

void DiscGearGrindTool::sceneChanged(){
    m_gearBox.clear();
    m_discBox.clear();
    std::list<SceneManager3D::ManagedItem> items = m_sceneManager->getItems();
    for( std::list<SceneManager3D::ManagedItem>::iterator it = items.begin(); it != items.end(); ++it){
        m_gearBox.addItem(QString(it->renderItem->getName().c_str()));
        m_discBox.addItem(QString(it->renderItem->getName().c_str()));
    }
 }

