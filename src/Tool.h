#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include <QPushButton>

#include "Component.h"

class Tool: public QObject {
	Q_OBJECT

public:
	QPushButton* toolButton;
	QWidget* toolSettings;

	signals:
	void emitComponent( Component* component );

public:
	Tool();
	~Tool();

};

#endif // TOOL_H
