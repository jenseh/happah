#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include <QPushButton>

#include "Component.h"

class Tool: public QObject {
	Q_OBJECT

public:
	Tool();
	~Tool();

    QPushButton* getToolButton();
    QWidget* getToolSettings();

	signals:
	void emitComponent( Component* component );

private:
	QPushButton* toolButton;
	QWidget* toolSettings;
};

#endif // TOOL_H
