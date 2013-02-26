#include <QVBoxLayout>
#include <QLabel>

#include "happah/gui/qt/SplineTool.h"

SplineTool::SplineTool() {
	getToolButton()->setText("S");

	QVBoxLayout* vbox = new QVBoxLayout();

	QLabel* label = new QLabel("Spline Settings");
	vbox->addWidget(label);

	getToolSettings()->setLayout(vbox);
}

SplineTool::~SplineTool() {
}
