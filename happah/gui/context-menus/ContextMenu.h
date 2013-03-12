#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>

class ContextMenu : public QMenu {
	Q_OBJECT

public:
	ContextMenu(QWidget *parent = 0);
};
#endif //CONTEXTMENU_H
