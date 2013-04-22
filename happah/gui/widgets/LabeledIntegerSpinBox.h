#ifndef LABELED_INTEGER_SPINBOX_H_
#define LABELED_INTEGER_SPINBOX_H_

#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>

class LabeledIntegerSpinBox : public QGroupBox {
Q_OBJECT

public:
	LabeledIntegerSpinBox(const QString& label, QWidget* parent= 0);
	virtual ~LabeledIntegerSpinBox();

	int getValue();
	void setValue(int value);

signals:
	void valueChanged(int);

private slots:
	void myValueChanged(int value);

private:
	QLabel* m_label;
	QSpinBox* m_spinBox;
};

#endif /* LABELED_INTEGER_SPINBOX_H_ */
