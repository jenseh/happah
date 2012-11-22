#ifndef BSPLINETOOL_H
#define BSPLINETOOL_H

#include "ToolSelector.h"
#include "Tool.h"

class BSplineTool: public Tool {
	Q_OBJECT

public:
	BSplineTool();
	~BSplineTool();

private slots:
	void generateComponent();

};

#endif
