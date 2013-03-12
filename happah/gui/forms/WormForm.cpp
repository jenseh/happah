#include <QPushButton>
#include <QVBoxLayout>

#include "happah/geometries/Worm.h"
#include "happah/gui/forms/WormForm.h"

WormForm::WormForm(WormListener& wormListener, QWidget* parent)
	: Form(parent),
		m_toothCountSlider(new GearSlider(tr("tooth count"))),
		m_moduleSlider(new GearSlider(tr("module"))),
		m_pressureAngleSlider(new GearSlider(tr("pressure angle"))),
		m_wormInserted(false),
		m_wormListener(wormListener) {
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

	Worm* worm = new Worm();
	m_worm = Worm_ptr(worm);
	delete worm;

	updateRanges();
}

WormForm::~WormForm() {}

void WormForm::changeToothCount(hpreal toothCount) {
	m_worm->setToothCount((int) round(toothCount));
	updateWorm();
}

void WormForm::changeModule(hpreal module) {
	m_worm->setModule(module);
	updateWorm();
}

void WormForm::changePressureAngle(hpreal pressureAngle) {
	m_worm->setPressureAngle(pressureAngle);
	updateRanges();
	updateWorm();
}

void WormForm::createWorm() {
	//TODO: create a worm here
//	if(m_wormInserted)
//		m_worm = Worm_ptr(new Worm(*m_worm));
//	m_wormListener.insert(m_worm);
//	m_wormInserted = true;
}

Worm_ptr WormForm::getWorm() const {
	return m_worm;
}

void WormForm::reset() {
	Worm* worm = new Worm();
	m_worm = Worm_ptr(worm);
	delete worm;
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
		m_wormListener.update(m_worm);
}

void WormForm::updateRanges() {
	m_toothCountSlider->setSliderValues((hpreal) m_worm->getToothCount(), 1, 100);
	m_moduleSlider->setSliderValues(m_worm->getModule(), 0.1 * M_PI, 20.0 * M_PI);
	m_pressureAngleSlider->setSliderValues(m_worm->getPressureAngle(), 0.1, 0.785);
}
