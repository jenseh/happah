#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include <QPushButton>

//#include "Component.h"
#include "../../core/Drawable2D.h"

class Tool: public QObject {
Q_OBJECT

public:
	Tool();
	~Tool();

	QPushButton* getToolButton();
	QWidget* getToolSettings();

signals:
	void emitComponent(Drawable2D* drawable);
	void changed();

private:
	QPushButton* toolButton;
	QWidget* toolSettings;

public slots:
	virtual void finalise();
	virtual void leftClickAt( QPointF point );
	virtual void rightClickAt( QPointF point );
};

#endif // TOOL_H
