#include "happah/gui/qt/EditorScene.h"

EditorScene::EditorScene(QObject* parent) :
		QGraphicsScene(parent) {
}

EditorScene::~EditorScene() {
}

void EditorScene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) {
	if( mouseEvent->button() == Qt::LeftButton )
		emit leftClickedAt( mouseEvent->scenePos() );
	else if( mouseEvent->button() == Qt::RightButton )
		emit rightClickedAt( mouseEvent->scenePos() );
}

void EditorScene::wheelEvent( QGraphicsSceneWheelEvent * wheelEvent ) {
	emit scaleScene(wheelEvent->delta());
}
