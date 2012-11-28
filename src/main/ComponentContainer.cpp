#include "ComponentContainer.h"

ComponentContainer::ComponentContainer(QGraphicsScene* scene, QWidget* parent) :
		QListWidget(parent), scene_(scene) {
	;
}

ComponentContainer::~ComponentContainer() {
}

void ComponentContainer::addComponent(Component* component) {
    this->addItem(component);
    scene_->addItem(component);
}

