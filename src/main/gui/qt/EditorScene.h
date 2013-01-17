#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class EditorScene: public QGraphicsScene {
Q_OBJECT

public:
	EditorScene(QObject* parent = 0);
	~EditorScene();
	void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent );

signals:
	void leftClickedAt( QPointF point );
	void rightClickedAt( QPointF point );

};

#endif // EDITORSCENE_H
