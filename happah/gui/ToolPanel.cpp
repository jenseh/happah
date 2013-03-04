#include <QGridLayout>
#include <QPushButton>

#include "happah/gui/ToolPanel.h"
#include "happah/gui/forms/InvoluteGearForm.h"

ToolPanel::ToolPanel(GUIManager& guiManager, QWidget* parent)
	: QWidget(parent), m_forms(new QStackedWidget(this)) {
	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->setSpacing(2);
	QWidget* buttons = new QWidget(this);
	buttons->setLayout(buttonsLayout);

	QPushButton* involuteGearButton = new QPushButton(tr("IG"), this);
	involuteGearButton->setFixedSize(40, 40);
	involuteGearButton->setCheckable(true);
	buttonsLayout->addWidget(involuteGearButton, 0, 0);
	m_forms->addWidget(new InvoluteGearForm(guiManager, m_forms));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(buttons);
	layout->addWidget(m_forms);
	setLayout(layout);
}

ToolPanel::~ToolPanel() {}
