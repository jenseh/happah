#include "InvoluteSpurGearTool.h"

#include <QGroupBox>
#include "../../core/models/TriangleMesh.h"

InvoluteSpurGearTool::InvoluteSpurGearTool() {
	m_mode = this->IDLEMODE;

	m_gear = new InvoluteSpurGear();

	m_toothCount = m_gear->getToothCount();
	m_module = m_gear->getModule();
	m_facewidth = m_gear->getFacewidth();
	m_pressureAngle = m_gear->getPressureAngle();
	m_bottomClrearance = m_gear->getBottomClearance();
	m_filletRadius = m_gear->getFilletRadius();

	uint* toothCounts = m_gear->getPossibleToothCounts();
	hpreal* modules = m_gear->getPossibleModules();
	hpreal* pressureAngles = m_gear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_gear->getPossibleBottomClearances();
	hpreal* filletRadien = m_gear->getPossibleFilletRadien();

	getToolButton()->setText("IG");

    QVBoxLayout* vbox = new QVBoxLayout();
    QGroupBox* gbox = new QGroupBox("Involute Spur Gear");
    vbox->addWidget(gbox);
    getToolSettings()->setLayout(vbox);

    m_toothCountSlider      = new GearSlider(tr("Number of teeth"), toothCounts[0], toothCounts[1], toothCounts[1] - toothCounts[0]);
    m_moduleSlider          = new GearSlider(tr("module"), modules[0], modules[1], 100);
    m_facewidthSlider       = new GearSlider(tr("facewidth"), 0.0f, m_gear->getReferenceRadius() * 2.0f, 100);
    m_pressureAngleSlider   = new GearSlider(tr("pressure angle"), pressureAngles[0], pressureAngles[1], 100);
    m_bottomClearanceSlider = new GearSlider(tr("bottom clearance"), bottomClearances[0], bottomClearances[1], 100);
    m_filletRadiusSlider    = new GearSlider(tr("fillet radius"), filletRadien[0], filletRadien[1], 100);

    QPushButton* createButton = new QPushButton("create gear");

    vbox = new QVBoxLayout();
    vbox->addWidget(m_toothCountSlider);
    vbox->addWidget(m_moduleSlider);
    vbox->addWidget(m_facewidthSlider);
    vbox->addWidget(m_pressureAngleSlider);
    vbox->addWidget(m_bottomClearanceSlider);
    vbox->addWidget(m_filletRadiusSlider);
    vbox->addWidget(createButton);

    gbox->setLayout(vbox);

    connect(createButton, SIGNAL(clicked()), this, SLOT(createGear()));
	
}

InvoluteSpurGearTool::~InvoluteSpurGearTool() {
}

void InvoluteSpurGearTool::createGear() {
	m_gear = new InvoluteSpurGear(m_toothCount, m_module, m_facewidth, m_pressureAngle, m_bottomClrearance, m_filletRadius);
	TriangleMesh *drawable = m_gear->toTriangleMesh();
	emit emitComponent(drawable);
}
