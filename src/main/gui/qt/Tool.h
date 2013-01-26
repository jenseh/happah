#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include <QPushButton>

//#include "Component.h"
#include "../../gui/Drawable2D.h"
#include "../../core/models/Drawable.h"

class Tool: public QObject {
Q_OBJECT

public:
	Tool();
	~Tool();

	QPushButton* getToolButton();
	QWidget* getToolSettings();

signals:
	void emitComponent(Drawable2D* drawable);
	void emitComponent(Drawable* drawable);
	void changed();

private:
	QPushButton* m_toolButton;
	QWidget* m_toolSettings;

public slots:
	virtual void finalise();
	virtual void leftClickAt( QPointF point );
	virtual void rightClickAt( QPointF point );
};

#endif // TOOL_H
