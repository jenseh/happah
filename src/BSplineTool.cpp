#include "BSplineTool.h"

BSplineTool::BSplineTool() {
    getToolButton()->setText("B");

	QVBoxLayout* vbox = new QVBoxLayout();

	QLabel* label = new QLabel("B-Spline Settings"); //TODO: move label into component
	vbox->addWidget(label);

	QPushButton* genBtn = new QPushButton("new");
	connect(genBtn, SIGNAL(clicked()), this, SLOT(generateComponent()));
	vbox->addWidget(genBtn);

    getToolSettings()->setLayout(vbox);
}

BSplineTool::~BSplineTool() {
}

void BSplineTool::generateComponent() {

	BSplineComponent* component = new BSplineComponent;
	emit emitComponent(component);

}
