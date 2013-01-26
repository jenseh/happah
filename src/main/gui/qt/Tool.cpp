#include "Tool.h"

Tool::Tool() {
	m_toolButton = new QPushButton();
	m_toolSettings = new QWidget();
}

Tool::~Tool() {
}

QPushButton* Tool::getToolButton() {
	return m_toolButton;
}

QWidget* Tool::getToolSettings() {
	return m_toolSettings;
}

void Tool::finalise() {
}

void Tool::leftClickAt( QPointF point ) {
}

void Tool::rightClickAt( QPointF point ) {
}
