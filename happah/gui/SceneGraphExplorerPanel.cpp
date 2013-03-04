#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/ComponentList.h"
#include "happah/gui/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(QWidget* parent)
	: QWidget(parent) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(new ComponentList());
	layout->addWidget(new QPushButton("Delete"));
	setLayout(layout);
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}
