#ifndef PLANEFORM_H
#define PLANEFORM_H

#include "happah/geometries/Plane.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/PlaneListener.h"

class PlaneForm : public Form {
Q_OBJECT

public:
	PlaneForm(PlaneListener& planeListener, QWidget* parent = NULL);
	~PlaneForm();

	Plane_ptr getPlane() const;
	void reset();
	void setPlane(Plane_ptr plane);

private:
	Plane_ptr m_plane;
	bool m_planeInserted;

};

#endif // PLANEFORM_H
