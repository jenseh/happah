#ifndef VECTOR_INPUT_H
#define VECTOR_INPUT_H

#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>

#include "happah/HappahTypes.h"

class VectorInput : public QGroupBox {
	Q_OBJECT

public:
	VectorInput(const QString &title, bool showLength, bool zeroAllowed, QWidget *parent = 0);

	hpvec3 getValue();
	hpreal getLength();
	void setValue(hpvec3 value);

signals:
	void valueChanged();

private slots:
	void xValueChanged(double value);
	void yValueChanged(double value);
	void zValueChanged(double value);

private:
	bool m_showLength;
	bool m_zeroAllowed;
	QLabel* m_lengthLabel;
	QDoubleSpinBox* m_xValueBox;
	QDoubleSpinBox* m_yValueBox;
	QDoubleSpinBox* m_zValueBox;

};

#endif // VECTOR_INPUT_H

