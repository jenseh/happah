#include "SimpleGearTool.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include "../RenderItem3D.h"
#include "../../core/geometries/InvoluteSpurGear.h"
#include "../../core/geometries/BSplineGearCurve.h"

SimpleGearTool::SimpleGearTool() {
	m_mode = this->IDLEMODE;

	getToolButton()->setText("SG");

	QVBoxLayout* vbox = new QVBoxLayout();
	QGroupBox* gbox = new QGroupBox("Simple Gear");
	vbox->addWidget(gbox);
	getToolSettings()->setLayout(vbox);

	m_helixAngleSlider = new GearSlider(tr("helix angle"));
	m_facewidthSlider  = new GearSlider(tr("facewidth"));
	m_radiusSlider     = new GearSlider(tr("approximated radius"));

	QPushButton* createButton = new QPushButton("create gear");
	m_changeOutlineButton = new QPushButton("change outline");
	m_changeOutlineButton->setEnabled(false);

	vbox = new QVBoxLayout();
	vbox->addWidget(m_helixAngleSlider);
	vbox->addWidget(m_facewidthSlider);
	vbox->addWidget(m_radiusSlider);
	vbox->addWidget(createButton);
	vbox->addWidget(m_changeOutlineButton);

	gbox->setLayout(vbox);

	connect(m_helixAngleSlider,    SIGNAL(valueChanged(hpreal)), this, SLOT(changeHelixAngle(hpreal)));
	connect(m_facewidthSlider,     SIGNAL(valueChanged(hpreal)), this, SLOT(changeFacewidth(hpreal)));
	connect(m_radiusSlider,        SIGNAL(valueChanged(hpreal)), this, SLOT(changeRadius(hpreal)));
	connect(createButton,          SIGNAL(clicked()), this, SLOT(createGear()));
	connect(m_changeOutlineButton, SIGNAL(clicked()), this, SLOT(toBSpline()));

	InvoluteSpurGear* invGear = new InvoluteSpurGear();
	m_gear = invGear->toSimpleGear();
	delete invGear;
	m_gearMesh = NULL;
	updateRanges();
}

SimpleGearTool::~SimpleGearTool() {}

void SimpleGearTool::createGear() {
	m_mode = this->EDITMODE;
	if (m_gearMesh != NULL) {
		InvoluteSpurGear* invGear = new InvoluteSpurGear();
		invGear->setFacewidth(m_gear->getFacewidth());
		invGear->setHelixAngle(m_gear->getHelixAngle());
		m_gear = invGear->toSimpleGear();
		delete invGear;
	}
	m_gearMesh = m_gear->toTriangleMesh();
	m_gearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f); //ka, kd, ks, phong
	m_changeOutlineButton->setEnabled(true);
	emit emitComponent(new RenderItem3D(m_gear, m_gearMesh, m_gearMesh->getName()));
}

void SimpleGearTool::updateGear() {
	if (m_gearMesh != NULL) {
		TriangleMesh *mesh = m_gear->toTriangleMesh();
		*m_gearMesh = *mesh;
		delete mesh;
		emit changed();
	}
}

void SimpleGearTool::updateRanges() {
	hpreal epsilon = 0.0001f;
	m_helixAngleSlider->setSliderValues(m_gear->getHelixAngle(), -(epsilon + M_PI / 2.0f), epsilon + M_PI / 2.0f );
	m_facewidthSlider->setSliderValues(m_gear->getFacewidth(), 0.0f, 2.0f);
	m_radiusSlider->setSliderValues(m_gear->getRadius(), m_gear->getRadius() / 2.0f, m_gear->getRadius() * 2.0f);
}

void SimpleGearTool::changeHelixAngle(hpreal angle) {
	m_gear->setHelixAngle(angle);
	updateGear();
}

void SimpleGearTool::changeFacewidth(hpreal facewidth) {
	m_gear->setFacewidth(facewidth);
	updateGear();
}

void SimpleGearTool::changeRadius(hpreal radius) {
	m_gear->setRadius(radius);
	updateRanges();
	updateGear();
}

void SimpleGearTool::finalise() {
	if(m_mode == this->EDITMODE) {
		m_mode = this->IDLEMODE;
		if(m_gearMesh != NULL) {
			InvoluteSpurGear *invGear = new InvoluteSpurGear();
			m_gear = invGear->toSimpleGear();
			delete invGear;
		}
		m_gearMesh = NULL;
		updateRanges();
		m_changeOutlineButton->setEnabled(false);
		emit changed();
	}
}

//TODO: We should find something else here. Dynamic casts are bad!!!
bool SimpleGearTool::knowsItem(RenderItem3D* renderItem) {
	return (dynamic_cast<SimpleGear*>(renderItem->getNonDrawable()) != NULL);
}
void SimpleGearTool::reactivate(RenderItem3D* renderItem) {
	m_mode = this->EDITMODE;
	if(m_gearMesh == NULL)
		delete m_gear;
	m_gear = dynamic_cast<SimpleGear*>(renderItem->getNonDrawable());
	m_gearMesh = dynamic_cast<TriangleMesh*>(renderItem->getDrawable());
	m_changeOutlineButton->setEnabled(true);
	updateRanges();
}

void SimpleGearTool::toBSpline() {
	if(m_mode == this->EDITMODE && m_gearMesh != NULL) {
		//m_gear->setScalingActivated(true);
		BSplineGearCurve* bspline = m_gear->getBSplineToothProfileInXYPlane();
		bspline->setName("BSplineCurve of Gear");
		emit deleteCurrentAndEmitNew(bspline);
		finalise();
	}
}