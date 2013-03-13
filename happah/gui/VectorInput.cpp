#include <QGridLayout>

#include "happah/gui/VectorInput.h"

VectorInput::VectorInput(const QString &title, bool showLength, QWidget *parent) :
	QGroupBox(parent), m_showLength(showLength)
{

	this->setTitle(title);

	m_xValueBox = new QDoubleSpinBox();
	m_xValueBox->setSingleStep(0.1f);
	m_xValueBox->setValue(0.0f);
	m_xValueBox->setMinimum(-99.99f);
	connect( m_xValueBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChanged(double)) );
	m_yValueBox = new QDoubleSpinBox();
	m_yValueBox->setSingleStep(0.1f);
	m_yValueBox->setValue(1.0f);
	m_yValueBox->setMinimum(-99.99f);
	connect( m_yValueBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChanged(double)) );
	m_zValueBox = new QDoubleSpinBox();
	m_zValueBox->setSingleStep(0.1f);
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
		m_lengthLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
		gridLayout->addWidget(m_lengthLabel, 1, 1, Qt::AlignTop);
	}

	this->setLayout(gridLayout);
}

void VectorInput::setVectorValue(hpvec3 value) {}

hpvec3 VectorInput::getValue() {}

void VectorInput::xValueChanged(double value) {}
void VectorInput::yValueChanged(double value) {}
void VectorInput::zValueChanged(double value) {}

