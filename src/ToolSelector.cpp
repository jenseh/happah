#include <QVBoxLayout>
#include <QTextStream>
#include <QWidget>

#include "ToolSelector.h"

ToolSelector::ToolSelector(QWidget* parent) {
	setParent(parent);

	toolCount = 0;
	currToolID = 0;

	settingsWidgetStack = new QStackedWidget;
	settingsWidgetStack->addWidget(new QWidget);

	buttonGroup = new QButtonGroup(this);
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(toolSelected(int)));

	QVBoxLayout* vBox = new QVBoxLayout(this);

	selectorGrid = new QGridLayout();
	selectorGrid->setSpacing(2);

	vBox->addLayout(selectorGrid);
	vBox->addStretch(1);

	setLayout(vBox);
}

ToolSelector::~ToolSelector() {
}

QWidget* ToolSelector::getSettingsWidget() {
	return settingsWidgetStack;
}

void ToolSelector::addTool(Tool* tool) {

	toolList.append(tool);

	int row = (toolCount / buttonsPerRow);
	int col = (toolCount % buttonsPerRow);

	tool->toolButton->setFixedSize(40, 40);
	tool->toolButton->setCheckable(true);
//	toolButton->setParent(this);
	buttonGroup->addButton(tool->toolButton, toolCount);
	selectorGrid->addWidget(tool->toolButton, row, col);

	settingsWidgetStack->addWidget(tool->toolSettings);

	toolCount += 1;
}

void ToolSelector::toolSelected(int toolID) {
	settingsWidgetStack->setCurrentIndex(toolID + 1);

	toolList[currToolID]->disconnect( SIGNAL(emitComponent( Component* )) );
	connect( toolList[toolID], SIGNAL(emitComponent( Component* )),
			this, SLOT(newComponent( Component* )) );
	currToolID = toolID;

//	QTextStream out(stdout);
//	out << "Button " << toolID << endl;
}

void ToolSelector::newComponent(Component* component) {
	emit emitComponent(component);
}
