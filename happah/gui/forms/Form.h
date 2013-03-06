#ifndef FORM_H
#define FORM_H

#include <QWidget>

class Form : public QWidget {

public:
	Form(QWidget* parent = 0);
	virtual ~Form();

	virtual void reset() = 0;

};


#endif // FORM_H
