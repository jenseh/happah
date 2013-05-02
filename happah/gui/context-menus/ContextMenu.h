#ifndef CONTEXT_MENU_H
#define CONTEXT_MENU_H

#include <memory>
#include <QMenu>

using namespace std;

class GUIStateNode;
typedef shared_ptr<GUIStateNode> GUIStateNode_ptr;

class ContextMenu : public QMenu {
Q_OBJECT

public:
	ContextMenu(QWidget* parent = 0);
	virtual ~ContextMenu();

};
#endif //CONTEXT_MENU_H
