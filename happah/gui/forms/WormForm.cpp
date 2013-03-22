#include <QPushButton>
#include <QVBoxLayout>

#include "happah/geometries/Worm.h"
#include "happah/gui/forms/WormForm.h"

WormForm::WormForm(GUIManager& guiManager, QWidget* parent)
	: Form(parent),
		m_guiManager(guiManager),
		m_moduleSlider(new Slider(tr("module"))),
		m_pressureAngleSlider(new Slider(tr("pressure angle"))),
		m_toothCountSlider(new Slider(tr("tooth count"))),
		m_wormInserted(false) {
	QPushButton* createButton = new QPushButton("create worm");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_toothCountSlider);
	layout->addWidget(m_moduleSlider);
	layout->addWidget(m_pressureAngleSlider);
	layout->addWidget(createButton);
	setLayout(layout);

	connect(createButton, SIGNAL(clicked()), this, SLOT(createWorm()));
	connect(m_toothCountSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeToothCount(hpreal)));
	connect(m_moduleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changeModule(hpreal)));
	connect(m_pressureAngleSlider, SIGNAL(valueChanged(hpreal)), this, SLOT(changePressureAngle(hpreal)));

	m_worm = Worm_ptr(new Worm());
	updateRanges();
}

WormForm::~WormForm() {
	delete m_toothCountSlider;
	delete m_moduleSlider;
	delete m_pressureAngleSlider;
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

void WormForm::createWorm() {
	//TODO: create a worm here
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
	if(m_wormInserted)
		m_guiManager.update(m_worm);
}

void WormForm::updateRanges() {
	hpreal toothCount = (hpreal) m_worm->getToothCount();
	hpreal module = m_worm->getModule();
	hpreal pressureAngle = m_worm->getPressureAngle();

	m_toothCountSlider->setSliderValues((hpreal) m_worm->getToothCount(), 1, 100);
	m_moduleSlider->setSliderValues(m_worm->getModule(), 0.001 * M_PI, 20.0 * M_PI);
	m_pressureAngleSlider->setSliderValues(m_worm->getPressureAngle(), 10.0 / 360.0 * 2.0 * M_PI, 90.0 / 360.0 * 2.0 * M_PI);
}
