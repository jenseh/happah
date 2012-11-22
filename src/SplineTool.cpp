#include <QVBoxLayout>
#include <QLabel>

#include "SplineTool.h"

SplineTool::SplineTool() {
	toolButton->setText("S");

	QVBoxLayout* vbox = new QVBoxLayout();

	QLabel* label = new QLabel("Spline Settings");
	vbox->addWidget(label);

	toolSettings->setLayout(vbox);
}

SplineTool::~SplineTool() {
}
