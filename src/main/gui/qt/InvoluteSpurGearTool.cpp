#include "InvoluteSpurGearTool.h"

#include <QGroupBox>
#include <iostream>
#include "../../test/DiscGearGrindTest.h"
#include "../RenderItem3D.h"

InvoluteSpurGearTool::InvoluteSpurGearTool() {
	m_mode = this->IDLEMODE;

	getToolButton()->setText("IG");

	QVBoxLayout* vbox = new QVBoxLayout();
	QGroupBox* gbox = new QGroupBox("Involute Spur Gear");
	vbox->addWidget(gbox);
	getToolSettings()->setLayout(vbox);

	m_toothCountSlider      = new GearSlider(tr("number of teeth"), false);
	m_moduleSlider          = new GearSlider(tr("module"));
	m_facewidthSlider       = new GearSlider(tr("facewidth"));
	m_pressureAngleSlider   = new GearSlider(tr("pressure angle"));
	m_bottomClearanceSlider = new GearSlider(tr("bottom clearance"));
	m_filletRadiusSlider    = new GearSlider(tr("fillet radius"));

	QPushButton* setBackButton      = new QPushButton("set back values"); //good if they are out of visible range
	QPushButton* toSimpleGearButton = new QPushButton("to gear mesh");
	QPushButton* createButton       = new QPushButton("create gear");

	vbox = new QVBoxLayout();
	vbox->addWidget(m_toothCountSlider);
	vbox->addWidget(m_moduleSlider);
	vbox->addWidget(m_facewidthSlider);
	vbox->addWidget(m_pressureAngleSlider);
	vbox->addWidget(m_bottomClearanceSlider);
	vbox->addWidget(m_filletRadiusSlider);
	vbox->addWidget(setBackButton);
	vbox->addWidget(toSimpleGearButton);
	vbox->addWidget(createButton);

	gbox->setLayout(vbox);

	connect(createButton,       SIGNAL(clicked()), this, SLOT(createGear()));
	connect(toSimpleGearButton, SIGNAL(clicked()), this, SLOT(toSimpleGear()));
	connect(setBackButton,      SIGNAL(clicked()), this, SLOT(setBack()));
	connect(m_toothCountSlider,      SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));
	connect(m_moduleSlider,          SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_facewidthSlider,       SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
	connect(m_pressureAngleSlider,   SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));
	connect(m_bottomClearanceSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
	connect(m_filletRadiusSlider,    SIGNAL(valueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));

	m_gear = new InvoluteSpurGear();
	m_gearMesh = m_gear->toTriangleMesh();
	setInitialState();

}

InvoluteSpurGearTool::~InvoluteSpurGearTool() {
}

void InvoluteSpurGearTool::createGear() {
	m_gearMesh = m_gear->toTriangleMesh();
	//drawable->setColor(0.8f, 0.5f, 0.1f, 0.5f);
	m_gearMesh->setMaterial(0.25f,        //ka
			     0.5f,        //kd
			     1.0f,        //ks
			     10.0f);      //phong
	emit emitComponent(new RenderItem3D(m_gear, m_gearMesh, m_gearMesh->getName()));
	//DiscGearGrindTest test;
	//emit emitComponent(test.runSimulation());

}

void InvoluteSpurGearTool::setInitialState() {
	InvoluteSpurGear *gear = new InvoluteSpurGear();
	*m_gear = *gear;
	delete gear;
	m_toothCount = m_gear->getToothCount();
	m_module = m_gear->getModule();
	m_facewidth = m_gear->getFacewidth();
	m_pressureAngle = m_gear->getPressureAngle();
	m_bottomClrearance = m_gear->getBottomClearance();
	m_filletRadius = m_gear->getFilletRadius();
	updateRanges();
}

void InvoluteSpurGearTool::setBack() {
	setInitialState();
	updateGear();
}

void InvoluteSpurGearTool::updateGear() {
	TriangleMesh *mesh = m_gear->toTriangleMesh();
	*m_gearMesh = *mesh;
	delete mesh;
	emit changed();
}

void InvoluteSpurGearTool::updateRanges() {
	uint* toothCounts = m_gear->getPossibleToothCounts();
	hpreal* modules = m_gear->getPossibleModules();
	hpreal* pressureAngles = m_gear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_gear->getPossibleBottomClearances();
	hpreal* filletRadien = m_gear->getPossibleFilletRadien();

	m_toothCountSlider->setSliderValues(m_toothCount, toothCounts[0], toothCounts[1]);
	m_moduleSlider->setSliderValues(m_module, modules[0], modules[1]);
	m_facewidthSlider->setSliderValues(m_facewidth, 0.0f, m_gear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_pressureAngle, pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setSliderValues(m_bottomClrearance, bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setSliderValues(m_filletRadius, filletRadien[0], filletRadien[1]);
}

void InvoluteSpurGearTool::changeToothCount(hpreal toothCount) {
	if (m_gear->setToothCount(toothCount)) {
		m_toothCount = toothCount;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeModule(hpreal module) {
	if (m_gear->setModule(module)) {
		m_module = module;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeFacewidth(hpreal facewidth) {
	if (m_gear->setFacewidth(facewidth)) {
		m_facewidth = facewidth;
		updateGear();
	}
}
void InvoluteSpurGearTool::changePressureAngle(hpreal angle) {
	if (m_gear->setPressureAngle(angle)) {
		m_pressureAngle = angle;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeBottomClearance(hpreal bottomClearance) {
	if (m_gear->setBottomClearance(bottomClearance)) {
		m_bottomClrearance = bottomClearance;
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeFilletRadius(hpreal radius) {
	if (m_gear->setFilletRadius(radius)) {
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
	}
}

void InvoluteSpurGearTool::toSimpleGear() {

}

