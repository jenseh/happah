#include <QGridLayout>
#include "happah/gui/widgets/LabeledIntegerSpinBox.h"

LabeledIntegerSpinBox::LabeledIntegerSpinBox(const QString& label, QWidget* parent)
	:QGroupBox(parent){

	m_spinBox = new QSpinBox();
	connect(m_spinBox,SIGNAL(valueChanged(int)),this,SLOT(myValueChanged(int)));
	m_label = new QLabel(label,this);
	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->addWidget(m_label,0,0);
	gridLayout->addWidget(m_spinBox,0,1);

	this->setLayout(gridLayout);
}

LabeledIntegerSpinBox::~LabeledIntegerSpinBox() {
	// TODO Auto-generated destructor stub
}

int LabeledIntegerSpinBox::getValue(){
	return m_spinBox->value();
}

void LabeledIntegerSpinBox::setValue(int value){
	m_spinBox->setValue(value);
}

void LabeledIntegerSpinBox::myValueChanged(int value){
	emit(valueChanged(value));
}


