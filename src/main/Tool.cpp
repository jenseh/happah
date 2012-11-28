#include "Tool.h"

Tool::Tool() {
	toolButton = new QPushButton();
	toolSettings = new QWidget();
}

Tool::~Tool() {
}

QPushButton* Tool::getToolButton() {
	return toolButton;
}

QWidget* Tool::getToolSettings() {
	return toolSettings;
}
