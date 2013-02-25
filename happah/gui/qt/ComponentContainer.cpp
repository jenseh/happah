#include "happah/gui/qt/ComponentContainer.h"
#include <iostream>

ComponentContainer::ComponentContainer(QGraphicsScene* scene, QWidget* parent) :
		QListWidget(parent), scene_(scene) {
}

ComponentContainer::~ComponentContainer() {
}

void ComponentContainer::addComponent(Component* component) {
	this->addItem(component);
	scene_->addItem(component);
}

void ComponentContainer::addComponent(std::string label) {
    const QString labelAsQString = QString::fromStdString(label);
    this->addItem(labelAsQString);
}

