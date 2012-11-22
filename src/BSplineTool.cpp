#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "BSplineTool.h"
#include "BSplineComponent.h"

BSplineTool::BSplineTool() {
	toolButton->setText("B");

	QVBoxLayout* vBox = new QVBoxLayout();

	QLabel* label = new QLabel("B-Spline Settings"); //TODO: move label into component
	vBox->addWidget(label);

	QPushButton* genBtn = new QPushButton("new");
	connect(genBtn, SIGNAL(clicked()), this, SLOT(generateComponent()));
	vBox->addWidget(genBtn);

	toolSettings->setLayout(vBox);
}

BSplineTool::~BSplineTool() {
}

void BSplineTool::generateComponent() {
	BSplineComponent* component = new BSplineComponent;
	emit emitComponent(component);
}
