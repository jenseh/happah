#include "ComponentContainer.h"

ComponentContainer::ComponentContainer(QGraphicsScene* scene, QWidget* parent) :
		QListWidget(parent), scene_(scene) {
	;
}

ComponentContainer::~ComponentContainer() {
}

void ComponentContainer::addComponent(Component* newComponent) {
	this->addItem(newComponent);
	scene_->addItem(newComponent);
}

