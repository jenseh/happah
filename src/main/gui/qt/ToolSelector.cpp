#include <QVBoxLayout>
#include <QTextStream>
#include <QWidget>

#include "ToolSelector.h"

ToolSelector::ToolSelector(QWidget* parent) {
	setParent(parent);

	toolCount_ = 0;
	currToolID_ = 0;

	settingsWidgetStack_ = new QStackedWidget;
	settingsWidgetStack_->addWidget(new QWidget);

	buttonGroup_ = new QButtonGroup(this);
	connect(buttonGroup_, SIGNAL(buttonClicked(int)), this,
			SLOT(toolSelected(int)));

	QVBoxLayout* vBox = new QVBoxLayout(this);

	selectorGrid_ = new QGridLayout();
	selectorGrid_->setSpacing(2);

	vBox->addLayout(selectorGrid_);
	vBox->addStretch(1);

	setLayout(vBox);
}

ToolSelector::~ToolSelector() {
}

QWidget* ToolSelector::getSettingsWidget() {
	return settingsWidgetStack_;
}

void ToolSelector::addTool(Tool* tool) {
	toolList_.append(tool);

	int row = (toolCount_ / BUTTONS_PER_ROW);
	int col = (toolCount_ % BUTTONS_PER_ROW);

	tool->getToolButton()->setFixedSize(40, 40);
	tool->getToolButton()->setCheckable(true);
//	toolButton->setParent(this);
	buttonGroup_->addButton(tool->getToolButton(), toolCount_);
	selectorGrid_->addWidget(tool->getToolButton(), row, col);

	settingsWidgetStack_->addWidget(tool->getToolSettings());

	toolCount_ += 1;
}

void ToolSelector::toolSelected(int toolID) {
	settingsWidgetStack_->setCurrentIndex(toolID + 1);

	toolList_[currToolID_]->disconnect(SIGNAL(emitComponent(Component*)));
	connect(toolList_[toolID], SIGNAL(emitComponent(Component*)), this,
			SLOT(newComponent(Component*)));
	currToolID_ = toolID;

//	QTextStream out(stdout);
//	out << "Button " << toolID << endl;
}

void ToolSelector::newComponent(Component* component) {
	emit emitComponent(component);
}
