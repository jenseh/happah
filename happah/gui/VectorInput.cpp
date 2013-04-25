#include <QGridLayout>

#include "happah/gui/VectorInput.h"

VectorInput::VectorInput(const QString &title, bool showLength, bool zeroAllowed, QWidget *parent) :
	QGroupBox(parent), m_showLength(showLength), m_zeroAllowed(zeroAllowed)
{

	this->setTitle(title);

	double stepSize = 0.05f;
	m_xValueBox = new QDoubleSpinBox();
	m_xValueBox->setSingleStep(stepSize);
	m_xValueBox->setValue(0.0f);
	m_xValueBox->setMinimum(-99.99f);
	connect( m_xValueBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChanged(double)) );
	m_yValueBox = new QDoubleSpinBox();
	m_yValueBox->setSingleStep(stepSize);
	if( !m_zeroAllowed ) {
		m_yValueBox->setValue(1.0f);
	}
	else {
		m_yValueBox->setValue(0.0f);
	}
	m_yValueBox->setMinimum(-99.99f);
	connect( m_yValueBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChanged(double)) );
	m_zValueBox = new QDoubleSpinBox();
	m_zValueBox->setSingleStep(stepSize);
	m_zValueBox->setValue(0.0f);
	m_zValueBox->setMinimum(-99.99f);
	connect( m_zValueBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChanged(double)) );

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setHorizontalSpacing(0);
	gridLayout->setVerticalSpacing(0);
	gridLayout->addWidget(new QLabel("x:", this), 0, 0 );
	gridLayout->addWidget(m_xValueBox, 0, 1);
	gridLayout->addWidget(new QLabel("y:", this), 0, 2 );
	gridLayout->addWidget(m_yValueBox, 0, 3);
	gridLayout->addWidget(new QLabel("z:", this), 0, 4 );
	gridLayout->addWidget(m_zValueBox, 0, 5);

	if(m_showLength) {
		m_lengthLabel = new QLabel(this);
		m_lengthLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		QString lengthText;
		lengthText.setNum(this->getLength());
		lengthText = "Length: " + lengthText;
		m_lengthLabel->setText( lengthText );
		gridLayout->addWidget(m_lengthLabel, 1, 1, 1, 5, Qt::AlignTop);
	}

	this->setLayout(gridLayout);
}

hpvec3 VectorInput::getValue() {
	hpvec3 retValue = hpvec3( m_xValueBox->value(), m_yValueBox->value(), m_zValueBox->value() );
	return retValue;
}

hpreal VectorInput::getLength() {
	hpvec3 retValue = hpvec3( m_xValueBox->value(), m_yValueBox->value(), m_zValueBox->value() );
	return glm::length(retValue);
}

void VectorInput::setValue(hpvec3 value) {
	m_xValueBox->setValue(value.x);
	m_zValueBox->setValue(value.z);
	if( !m_zeroAllowed && value.x == 0.f && value.y == 0.f && value.z == 0.f ) {
		m_yValueBox->setValue(0.01f);
//		emit(valueChanged()); // TODO: necessary?
	}
	else {
		m_yValueBox->setValue(value.y);
	}
	if(m_showLength) {
		QString lengthText;
		lengthText.setNum(this->getLength());
		lengthText = "Length: " + lengthText;
		m_lengthLabel->setText( lengthText );
	}
}


void VectorInput::xValueChanged(double value) {
	if( !m_zeroAllowed && value == 0.f && m_yValueBox->value() == 0.f && m_zValueBox->value() == 0.f ) {
		m_yValueBox->setValue(0.01f);
	}
	if(m_showLength) {
		QString lengthText;
		lengthText.setNum(this->getLength());
		lengthText = "Length: " + lengthText;
		m_lengthLabel->setText( lengthText );
	}
	emit(valueChanged());
}
void VectorInput::yValueChanged(double value) {
	if( !m_zeroAllowed && value == 0.f && m_xValueBox->value() == 0.f && m_zValueBox->value() == 0.f ) {
		m_xValueBox->setValue(0.01f);
	}
	if(m_showLength) {
		QString lengthText;
		lengthText.setNum(this->getLength());
		lengthText = "Length: " + lengthText;
		m_lengthLabel->setText( lengthText );
	}
	emit(valueChanged());
}
void VectorInput::zValueChanged(double value) {
	if( !m_zeroAllowed && value == 0.f && m_xValueBox->value() == 0.f && m_yValueBox->value() == 0.f ) {
		m_yValueBox->setValue(0.01f);
	}
	if(m_showLength) {
		QString lengthText;
		lengthText.setNum(this->getLength());
		lengthText = "Length: " + lengthText;
		m_lengthLabel->setText( lengthText );
	}

	emit(valueChanged());
}

