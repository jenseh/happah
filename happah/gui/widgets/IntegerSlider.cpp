#include "happah/gui/widgets/IntegerSlider.h"

IntegerSlider::IntegerSlider(QWidget *parent) : QSlider(parent) {
	initialize();
}
IntegerSlider::IntegerSlider(Qt::Orientation orientation, QWidget* parent = 0) : QSlider(parent) {
	initialize();
}
IntegerSlider::~IntegerSlider() {
}
IntegerSlider::initialize() {
	setTickPosition(QSlider::TicksBelow);
	setSingleStep(1);
	setPageStep(10);
	setTickInterval(1);
}