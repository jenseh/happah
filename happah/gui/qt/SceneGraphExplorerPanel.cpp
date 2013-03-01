#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/qt/ComponentList.h"
#include "happah/gui/qt/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(QWidget* parent)
	: QWidget(parent) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(new ComponentList());
	layout->addWidget(new QPushButton("Delete"));
	setLayout(layout);
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}
