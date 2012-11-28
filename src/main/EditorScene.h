#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>

class EditorScene: public QGraphicsScene {
	Q_OBJECT

public:
	EditorScene(QObject* parent = 0);
	~EditorScene();

};

#endif // EDITORSCENE_H
