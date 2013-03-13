#ifndef VECTOR_INPUT_H
#define VECTOR_INPUT_H

#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>

#include "happah/HappahTypes.h"

class VectorInput : public QGroupBox {
	Q_OBJECT


public:
	VectorInput(const QString &title, bool showLength, QWidget *parent = 0);

	void setVectorValue(hpvec3 value);
	hpvec3 getValue();

signals:
	void valueChanged(hpvec3 value);

private slots:
	void xValueChanged(double value);
	void yValueChanged(double value);
	void zValueChanged(double value);

private:
	QLabel* m_lengthLabel;
	bool m_showLength;
	QDoubleSpinBox* m_xValueBox;
	QDoubleSpinBox* m_yValueBox;
	QDoubleSpinBox* m_zValueBox;

};

#endif // VECTOR_INPUT_H

