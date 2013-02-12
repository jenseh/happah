#include <QVBoxLayout>
#include <QTextStream>
#include <QWidget>
#include <typeinfo>

#include "ToolSelector.h"

ToolSelector::ToolSelector(QWidget* parent) {
	setParent(parent);

	m_toolCount = 0;
	m_currToolID = 0;

	m_settingsWidgetStack = new QStackedWidget;
	m_settingsWidgetStack->addWidget(new QWidget);

	m_buttonGroup = new QButtonGroup(this);
	connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this,
			SLOT(toolSelected(int)));

	QVBoxLayout* vBox = new QVBoxLayout(this);

	m_selectorGrid = new QGridLayout();
	m_selectorGrid->setSpacing(2);

	vBox->addLayout(m_selectorGrid);
	vBox->addStretch(1);

	setLayout(vBox);
}

ToolSelector::~ToolSelector() {
}

QWidget* ToolSelector::getSettingsWidget() {
	return m_settingsWidgetStack;
}

void ToolSelector::addTool(Tool* tool) {
	m_toolList.append(tool);

	int row = (m_toolCount / BUTTONS_PER_ROW);
	int col = (m_toolCount % BUTTONS_PER_ROW);

	tool->getToolButton()->setFixedSize(40, 40);
	tool->getToolButton()->setCheckable(true);
//	toolButton->setParent(this);
	m_buttonGroup->addButton(tool->getToolButton(), m_toolCount);
	m_selectorGrid->addWidget(tool->getToolButton(), row, col);

	m_settingsWidgetStack->addWidget(tool->getToolSettings());

	m_toolCount += 1;
}

void ToolSelector::toolSelected(int toolID) {
	m_settingsWidgetStack->setCurrentIndex(toolID + 1);

	m_toolList[m_currToolID]->finalise();
	m_toolList[m_currToolID]->disconnect( SIGNAL(changed()) );
	m_toolList[m_currToolID]->disconnect( SIGNAL(deleteComponent()) );
	m_toolList[m_currToolID]->disconnect( SIGNAL(emitComponent(Drawable2D*)));
	m_toolList[m_currToolID]->disconnect( SIGNAL(emitComponent(RenderItem3D*)));
	
	connect(m_toolList[toolID], SIGNAL(emitComponent(Drawable2D*)), this, SLOT(newComponent(Drawable2D*)));
	connect(m_toolList[toolID], SIGNAL(emitComponent(RenderItem3D*)), this, SLOT(newComponent(RenderItem3D*)));

	connect(m_toolList[toolID], SIGNAL(changed()), this, SLOT(update()) );
	connect(m_toolList[toolID], SIGNAL(deleteComponent()), this, SLOT(deleteComponent()));

	m_currToolID = toolID;
//	m_toolList[m_currToolID]->disconnect(SIGNAL(emitComponent(Component*)));
//	connect(m_toolList[toolID], SIGNAL(emitComponent(Component*)), this,
//			SLOT(newComponent(Component*)));

//	QTextStream out(stdout);
//	out << "Button " << toolID << endl;
}

//void ToolSelector::newComponent(Component* component) {
//	std::string name = component->text().toStdString();
//	emit emitDrawable( drawable );
//}

void ToolSelector::newComponent(Drawable2D* drawable) {
	emit emitDrawable( drawable );
}

void ToolSelector::newComponent(RenderItem3D* renderItem) {
	emit emitDrawable( renderItem );
}

void ToolSelector::update() {
	emit changed();
}

void ToolSelector::deleteComponent() {
	emit deleteCurrentComponent();
}

void ToolSelector::finalise( std::string name ) {
	m_toolList[m_currToolID]->finalise();
}

void ToolSelector::activateTool ( RenderItem3D* renderItem) {
	for (unsigned int i = 0; i < m_toolList.size(); ++i) {
		if (m_toolList[i]->knowsItem(renderItem)) {
			toolSelected(i);
			m_toolList[i]->reactivate(renderItem);
		}
	}
}

void ToolSelector::leftClickAt( QPointF point ) {
	m_toolList[m_currToolID]->leftClickAt( point );
}

void ToolSelector::rightClickAt( QPointF point ) {
	m_toolList[m_currToolID]->rightClickAt( point );
}
