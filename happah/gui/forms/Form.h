#ifndef FORM_H
#define FORM_H

#include <QWidget>

class Form : public QWidget {
public:
	Form(QWidget* parent = 0);
	virtual ~Form();

	virtual void reset() = 0;
	virtual void handleSelection();
	virtual void handleSelection(int pointIndex){}
	virtual void handleDrag(float dx,float dy);
};


#endif // FORM_H
