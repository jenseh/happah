#include "happah/gui/qt/tools/InvoluteSpurGearTool.h"

#include <QGroupBox>
#include <iostream>
#include "happah/gui/RenderItem3D.h"

InvoluteSpurGearTool::InvoluteSpurGearTool(SceneManager& sceneManager) 
	: m_sceneManager(sceneManager) {
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
	m_helixAngleSlider      = new GearSlider(tr("helix angle"));

	QPushButton* createButton  = new QPushButton("create gear");

	vbox = new QVBoxLayout();
	vbox->addWidget(m_toothCountSlider);
	vbox->addWidget(m_moduleSlider);
	vbox->addWidget(m_facewidthSlider);
	vbox->addWidget(m_pressureAngleSlider);
	vbox->addWidget(m_bottomClearanceSlider);
	vbox->addWidget(m_filletRadiusSlider);
	vbox->addWidget(m_helixAngleSlider);
	vbox->addWidget(createButton);

	gbox->setLayout(vbox);

	connect(createButton,       SIGNAL(clicked()), this, SLOT(createGear()));
	connect(m_toothCountSlider,      SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));
	connect(m_moduleSlider,          SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_facewidthSlider,       SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
	connect(m_pressureAngleSlider,   SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));
	connect(m_bottomClearanceSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBottomClearance(hpreal)));
	connect(m_filletRadiusSlider,    SIGNAL(valueChanged(hpreal)), this, SLOT(changeFilletRadius(hpreal)));
	connect(m_helixAngleSlider,      SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));

	m_gear = InvoluteSpurGear_ptr(new InvoluteSpurGear());
	updateRanges();
}

InvoluteSpurGearTool::~InvoluteSpurGearTool() {
}

void InvoluteSpurGearTool::createGear() {
	m_mode = this->EDITMODE;
	m_gearMesh = TriangleMesh_ptr(m_gear->toTriangleMesh());
	m_gearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f); //ka, kd, ks, phong
	m_sceneManager.add(m_gear, m_gearMesh);
}

void InvoluteSpurGearTool::updateGear() {
	if (m_gearMesh) {
		m_sceneManager.remove(m_gear, m_gearMesh);
		m_gearMesh = TriangleMesh_ptr(m_gear->toTriangleMesh());
		m_sceneManager.add(m_gear, m_gearMesh);
	}
}

void InvoluteSpurGearTool::updateRanges() {
	uint* toothCounts = m_gear->getPossibleToothCounts();
	hpreal* modules = m_gear->getPossibleModules();
	hpreal* pressureAngles = m_gear->getPossiblePressureAngles();
	hpreal* bottomClearances = m_gear->getPossibleBottomClearances();
	hpreal* filletRadien = m_gear->getPossibleFilletRadien();
	hpreal epsilon = 0.0001f;

	m_toothCountSlider->setSliderValues(m_gear->getToothCount(), toothCounts[0], toothCounts[1]);
	m_moduleSlider->setSliderValues(m_gear->getModule(), modules[0], modules[1]);
	m_facewidthSlider->setSliderValues(m_gear->getFacewidth(), 0.0f, m_gear->getReferenceRadius() * 2.0f);
	m_pressureAngleSlider->setSliderValues(m_gear->getPressureAngle(), pressureAngles[0], pressureAngles[1]);
	m_bottomClearanceSlider->setSliderValues(m_gear->getBottomClearance(), bottomClearances[0], bottomClearances[1]);
	m_filletRadiusSlider->setSliderValues(m_gear->getFilletRadius(), filletRadien[0], filletRadien[1]);
	m_helixAngleSlider->setSliderValues(m_gear->getHelixAngle(), -(epsilon + M_PI / 2.0f), epsilon + M_PI / 2.0f );
}

void InvoluteSpurGearTool::changeToothCount(hpreal toothCount) {
	if (m_gear->setToothCount(toothCount)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeModule(hpreal module) {
	if (m_gear->setModule(module)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeFacewidth(hpreal facewidth) {
	if (m_gear->setFacewidth(facewidth)) {
		updateGear();
	}
}
void InvoluteSpurGearTool::changePressureAngle(hpreal angle) {
	if (m_gear->setPressureAngle(angle)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeBottomClearance(hpreal bottomClearance) {
	if (m_gear->setBottomClearance(bottomClearance)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeFilletRadius(hpreal radius) {
	if (m_gear->setFilletRadius(radius)) {
		updateRanges();
		updateGear();
	}
}
void InvoluteSpurGearTool::changeHelixAngle(hpreal angle) {
	if (m_gear->setHelixAngle(angle)) {
		updateRanges();
		updateGear();
	}
}

