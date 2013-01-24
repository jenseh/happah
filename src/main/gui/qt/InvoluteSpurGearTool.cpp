#include "InvoluteSpurGearTool.h"

#include <QGroupBox>
#include "../../core/models/TriangleMesh.h"
#include <iostream>

InvoluteSpurGearTool::InvoluteSpurGearTool() {
	m_mode = this->IDLEMODE;

	setInitialState();

	m_gear = new InvoluteSpurGear();

	uint* toothCounts = m_gear->getPossibleToothCounts();
	hpreal* modules = m_gear->getPossibleModules();
	hpreal* pressureAngles = m_gear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_gear->getPossibleBottomClearances();
	hpreal* filletRadien = m_gear->getPossibleFilletRadien();

	getToolButton()->setText("G");

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
    QPushButton* setBackButton = new QPushButton("set back values"); //good if they are out of visible range

    vbox = new QVBoxLayout();
    vbox->addWidget(m_toothCountSlider);
    vbox->addWidget(m_moduleSlider);
    vbox->addWidget(m_facewidthSlider);
    vbox->addWidget(m_pressureAngleSlider);
    vbox->addWidget(m_bottomClearanceSlider);
    vbox->addWidget(m_filletRadiusSlider);
    vbox->addWidget(createButton);
    vbox->addWidget(setBackButton);

    gbox->setLayout(vbox);

    connect(createButton,  SIGNAL(clicked()), this, SLOT(createGear()));
    connect(setBackButton, SIGNAL(clicked()), this, SLOT(setBack()));
    connect(m_toothCountSlider,      SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));
    connect(m_moduleSlider,          SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
    connect(m_facewidthSlider,       SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
    connect(m_pressureAngleSlider,   SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));
    connect(m_bottomClearanceSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
    connect(m_filletRadiusSlider,    SIGNAL(valueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));
	
}

InvoluteSpurGearTool::~InvoluteSpurGearTool() {
}

void InvoluteSpurGearTool::createGear() {
	m_gear = new InvoluteSpurGear(m_toothCount, m_module, m_facewidth, m_pressureAngle, m_bottomClrearance, m_filletRadius);
	TriangleMesh *drawable = m_gear->toTriangleMesh();
	emit emitComponent(drawable);
}

void InvoluteSpurGearTool::setInitialState() {
	InvoluteSpurGear *gear = new InvoluteSpurGear();
	m_toothCount = gear->getToothCount();
	m_module = gear->getModule();
	m_facewidth = gear->getFacewidth();
	m_pressureAngle = gear->getPressureAngle();
	m_bottomClrearance = gear->getBottomClearance();
	m_filletRadius = gear->getFilletRadius();
	delete gear;
}

void InvoluteSpurGearTool::setBack() {
	setInitialState();
	updateGear();
}

void InvoluteSpurGearTool::updateGear() {
	emit changed();
	createGear();
	updateRanges();
}

void InvoluteSpurGearTool::updateRanges() {
	uint* toothCounts = m_gear->getPossibleToothCounts();
	hpreal* itoothCounts = new hpreal[2];
	itoothCounts[0] = toothCounts[0];
	itoothCounts[1] = toothCounts[1];

	m_toothCountSlider->setNewRange(itoothCounts);
	m_moduleSlider->setNewRange(m_gear->getPossibleModules());
	m_pressureAngleSlider->setNewRange(m_gear->getPossiblePressureAngles());
	m_bottomClearanceSlider->setNewRange(m_gear->getPossibleBottomClearances());
	m_filletRadiusSlider->setNewRange(m_gear->getPossibleFilletRadien());

}

void InvoluteSpurGearTool::changeToothCount(hpreal toothCount) {
	if (m_gear->setToothCount(toothCount)) {
		m_toothCount = toothCount;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeModule(hpreal module) {
	std::cerr << "module should be set";
	if (m_gear->setModule(module)) {
		std::cerr << "and is set" << std::endl;
		m_module = module;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeFacewidth(hpreal facewidth) {
	std::cerr << "facewidth should be set";
	if (m_gear->setToothCount(facewidth)) {
		std::cerr << "and is set" << std::endl;
		m_facewidth = facewidth;
		updateGear();
	}
}
void InvoluteSpurGearTool::changePressureAngle(hpreal angle) {
	std::cerr << "angle should be set";
	if (m_gear->setModule(angle)) {
		std::cerr << "and is set" << std::endl;
		m_pressureAngle = angle;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeBottomClearance(hpreal bottomClearance) {
	std::cerr << "bottom should be set";
	if (m_gear->setModule(bottomClearance)) {
		std::cerr << "and is set" << std::endl;
		m_bottomClrearance = bottomClearance;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeFilletRadius(hpreal radius) {
	std::cerr << "radius should be set";
	if (m_gear->setModule(radius)) {
		std::cerr << "and is set"<< std::endl;
		m_filletRadius = radius;
		updateRanges();
		updateGear();
	}
}

void InvoluteSpurGearTool::finalise() {
	if( m_mode == this->EDITMODE ) {
		m_mode = this->IDLEMODE;
		delete m_gear;
		m_gear = NULL;
		emit changed();
		std::cerr << "gear deleted and emitted changed()" << std::cerr;
	}
}

