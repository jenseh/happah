#include "SimpleGearTool.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include "../RenderItem3D.h"
#include "../../core/geometries/InvoluteSpurGear.h"

SimpleGearTool::SimpleGearTool() {
	m_mode = this->IDLEMODE;

	getToolButton()->setText("SG");

	QVBoxLayout* vbox = new QVBoxLayout();
	QGroupBox* gbox = new QGroupBox("Simple Gear");
	vbox->addWidget(gbox);
	getToolSettings()->setLayout(vbox);

	m_helixAngleSlider = new GearSlider(tr("helix angle"));
	m_facewidthSlider  = new GearSlider(tr("facewidth"));

	QPushButton* createButton = new QPushButton("create gear");

	vbox = new QVBoxLayout();
	vbox->addWidget(m_helixAngleSlider);
	vbox->addWidget(m_facewidthSlider);
	vbox->addWidget(createButton);

	gbox->setLayout(vbox);

	connect(m_helixAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));
	connect(m_facewidthSlider,  SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
	connect(createButton,       SIGNAL(clicked()), this, SLOT(createGear()));

	InvoluteSpurGear* invGear = new InvoluteSpurGear();
	m_gear = invGear->toSimpleGear();
	delete invGear;
	m_gearMesh = m_gear->toTriangleMesh();
	m_helixAngle = m_gear->getHelixAngle();
	m_facewidth = m_gear->getFacewidth();
	updateRanges();
}

SimpleGearTool::~SimpleGearTool() {}

void SimpleGearTool::createGear() {
	m_gearMesh = m_gear->toTriangleMesh();
	m_gearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f); //ka, kd, ks, phong
	emit emitComponent(new RenderItem3D(m_gear, m_gearMesh, m_gearMesh->getName()));
}

void SimpleGearTool::updateGear() {
	TriangleMesh *mesh = m_gear->toTriangleMesh();
	*m_gearMesh = *mesh;
	delete mesh;
	emit changed();
}

void SimpleGearTool::updateRanges() {
	m_helixAngleSlider->setSliderValues(m_helixAngle, 0.0f, M_PI / 2.0f);
	m_facewidthSlider->setSliderValues(m_facewidth, 0.0f, 2.0f);
}

void SimpleGearTool::changeHelixAngle(hpreal angle) {
	m_gear->setHelixAngle(angle);
	updateGear();
}

void SimpleGearTool::changeFacewidth(hpreal facewidth) {
	m_gear->setFacewidth(facewidth);
	updateGear();
}

void SimpleGearTool::finalise() {

}