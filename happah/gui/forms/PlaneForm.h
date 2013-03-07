#ifndef PLANEFORM_H
#define PLANEFORM_H

#include "happah/geometries/Plane.h"
#include "happah/gui/forms/Form.h"

class PlaneForm : public Form {
Q_OBJECT

public:
	PlaneForm(QWidget* parent = 0);
	~PlaneForm();

	Plane_ptr getPlane() const;
	void reset();
	void setPlane(Plane_ptr plane);

private:
	Plane_ptr m_plane;
	bool m_planeInserted;

};

#endif // PLANEFORM_H
