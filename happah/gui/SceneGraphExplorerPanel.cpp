#include <QPushButton>
#include <QVBoxLayout>

#include "happah/gui/SceneGraphExplorerPanel.h"

SceneGraphExplorerPanel::SceneGraphExplorerPanel(QWidget* parent)
	: QWidget(parent), m_listWidget(new QListWidget(this)) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(m_listWidget);
	layout->addWidget(new QPushButton("Delete"));
	setLayout(layout);
}

SceneGraphExplorerPanel::~SceneGraphExplorerPanel() {}
