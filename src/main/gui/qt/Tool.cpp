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

bool Tool::knowsItem( RenderItem3D* renderItem ) {
	return false;
}
bool Tool::knowsItem( Drawable2D* drawable ) {
	return false;
}
void Tool::reactivate( RenderItem3D* renderItem ) {
}
void Tool::reactivate( Drawable2D* drawable ) {
}

void Tool::finalise() {
}

void Tool::leftClickAt( QPointF point ) {
}

void Tool::rightClickAt( QPointF point ) {
}
