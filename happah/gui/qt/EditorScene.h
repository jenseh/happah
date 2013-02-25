#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>

class EditorScene: public QGraphicsScene {
Q_OBJECT

public:
	EditorScene(QObject* parent = 0);
	~EditorScene();
	void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent );
	void wheelEvent( QGraphicsSceneWheelEvent * wheelEvent );

signals:
	void leftClickedAt( QPointF point );
	void rightClickedAt( QPointF point );
	void scaleScene( int );

};

#endif // EDITORSCENE_H
