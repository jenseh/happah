#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <memory>
#include <QMenu>


class GUIStateNode;
typedef std::shared_ptr<GUIStateNode> GUIStateNode_ptr;

class ContextMenu : public QMenu {
	Q_OBJECT

public:
	ContextMenu(QWidget *parent = 0);
};
#endif //CONTEXTMENU_H
