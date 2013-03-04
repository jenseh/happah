#ifndef TOOL_H
#define TOOL_H

#include <QPushButton>
#include <QWidget>

#include "happah/gui/Drawable2D.h"

class Tool: public QObject {
Q_OBJECT

public:
	Tool();
	~Tool();

	QPushButton* getToolButton();
	QWidget* getToolSettings();
	virtual bool knowsItem( Drawable2D* drawable );
	virtual void reactivate( Drawable2D* drawable );

signals:
	void emitComponent(Drawable2D* drawable);
	void deleteCurrentAndEmitNew(Drawable2D* drawable);
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
