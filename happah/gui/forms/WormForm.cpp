#include <QPushButton>
#include <QVBoxLayout>

#include "happah/geometries/gears/Worm.h"
#include "happah/gui/forms/WormForm.h"

WormForm::WormForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
		m_guiManager(guiManager),
		m_baseRadiusSlider(new LabeledRealValuedSlider(tr("base radius"))),
		m_moduleSlider(new LabeledRealValuedSlider(tr("module"))),
		m_pressureAngleSlider(new LabeledRealValuedSlider(tr("pressure angle"))),
		m_toothCountSlider(new LabeledRealValuedSlider(tr("tooth count"))),
		m_rotationsSlider(new LabeledRealValuedSlider(tr("rotations"))),
		m_wormInserted(false) {
	QPushButton* createButton = new QPushButton("create worm");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_baseRadiusSlider);
	layout->addWidget(m_toothCountSlider);
	layout->addWidget(m_moduleSlider);
	layout->addWidget(m_pressureAngleSlider);
	layout->addWidget(m_rotationsSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createWorm()));
	connect(m_baseRadiusSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeBaseRadius(hpreal)));
	connect(m_toothCountSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));
	connect(m_moduleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_pressureAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));
	connect(m_rotationsSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeRotations(hpreal)));

	m_worm = Worm_ptr(new Worm());
	updateRanges();
}

WormForm::~WormForm() {
	delete m_baseRadiusSlider;
	delete m_toothCountSlider;
	delete m_moduleSlider;
	delete m_pressureAngleSlider;
	delete m_rotationsSlider;
}

void WormForm::changeBaseRadius(hpreal baseRadius) {
	m_worm->setBaseRadius(baseRadius);
	updateRanges();
	updateWorm();
}

void WormForm::changeToothCount(hpreal toothCount) {
	m_worm->setToothCount((int) round(toothCount));
	updateRanges();
	updateWorm();
}

void WormForm::changeModule(hpreal module) {
	m_worm->setModule(module);
	updateRanges();
	updateWorm();
}

void WormForm::changePressureAngle(hpreal pressureAngle) {
	m_worm->setPressureAngle(pressureAngle);
	updateRanges();
	updateWorm();
}

void WormForm::changeRotations(hpreal rotations) {
	m_worm->setRotations(rotations);
	updateRanges();
	updateWorm();
}

void WormForm::createWorm() {
	if(m_wormInserted)
		m_worm = Worm_ptr(new Worm(*m_worm));
	m_guiManager.insert(m_worm,HP_TRIANGLE_MESH);
	m_wormInserted = true;
}

Worm_ptr WormForm::getWorm() const {
	return m_worm;
}

void WormForm::reset() {
	m_worm = Worm_ptr(new Worm());
	m_wormInserted = false;

	updateRanges();
}

void WormForm::setWorm(Worm_ptr worm) {
	m_worm = worm;
	m_wormInserted = true;

	updateRanges();
}

void WormForm::updateWorm() {
	if(m_wormInserted) {
		m_guiManager.update(m_worm);
	}
}

void WormForm::updateRanges() {
	hpreal baseRadius = m_worm->getBaseRadius();
	hpreal toothCount = (hpreal) m_worm->getToothCount();
	hpreal module = m_worm->getModule();
	hpreal pressureAngle = m_worm->getPressureAngle();
	hpreal rotations = m_worm->getRotations();

	m_baseRadiusSlider->setSliderValues(baseRadius, 0.1, 4);
	m_toothCountSlider->setSliderValues(toothCount, 1, 20);
	m_moduleSlider->setSliderValues(module, 0.002 * M_PI, 0.1 * M_PI);
	m_pressureAngleSlider->setSliderValues(pressureAngle, 10.0 / 360.0 * 2.0 * M_PI, 90.0 / 360.0 * 2.0 * M_PI);
	m_rotationsSlider->setSliderValues(rotations, 0.0, 20.0);
}
