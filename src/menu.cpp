#include "menu.h"


MenuClass::MenuClass(QWidget *parent) : QWidget(parent) {

	//Sphere Menu
	CreateSphere = new QPushButton("Create Sphere");
	SphereBox = new QVBoxLayout;
	SphereBox->addWidget(CreateSphere);
	SphereGroup = new QGroupBox("Sphere");
	SphereGroup->setLayout(SphereBox);

	//Triangle Menu
	CreateTriangle = new QPushButton("Create Triangle");
	TriangleBox = new QVBoxLayout;
	TriangleBox->addWidget(CreateTriangle);
	TriangleGroup = new QGroupBox("Triangle");
	TriangleGroup->setLayout(TriangleBox);

	//Put everything together
	MenuBox = new QVBoxLayout;
	MenuBox->setSizeConstraint(QLayout::SetFixedSize);
	MenuBox->addWidget(SphereGroup);
	MenuBox->addWidget(TriangleGroup);

	// Signals
	QObject::connect(CreateTriangle,SIGNAL(clicked()),
			qApp,SLOT(quit()));


	setLayout(MenuBox);

}








