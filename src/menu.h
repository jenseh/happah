#ifndef MENU_H_
#define MENU_H_

#include <QtGui>

class MenuClass : public QWidget {
	Q_OBJECT
public:
	MenuClass(QWidget *parent = 0);
private:
	QVBoxLayout* MenuBox;
	QVBoxLayout* SphereBox;
	QPushButton* CreateSphere;
	QGroupBox*	 SphereGroup;
	QVBoxLayout* TriangleBox;
	QPushButton* CreateTriangle;
	QGroupBox*	 TriangleGroup;

};

#endif /* MENU_H_ */
