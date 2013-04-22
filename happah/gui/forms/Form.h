#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include "happah/math/Ray.h"

class Form : public QWidget {
public:
	Form(QWidget* parent = 0);
	virtual ~Form();

	virtual void reset() = 0;
	virtual void handleSelection();
	virtual void handleSelection(int pointIndex){}
	virtual void handleDrag(Ray& ray);
	virtual void handleRay(Ray& ray);
	virtual void handleConnection();
};


#endif // FORM_H
