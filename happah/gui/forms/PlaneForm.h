#ifndef PLANEFORM_H
#define PLANEFORM_H

#include "happah/geometries/Plane.h"
#include "happah/gui/forms/Form.h"
#include "happah/gui/forms/PlaneListener.h"
#include "happah/gui/VectorInput.h"

class PlaneForm : public Form {
Q_OBJECT

public:
	PlaneForm(PlaneListener& planeListener, QWidget* parent = NULL);
	~PlaneForm();

	Plane_ptr getPlane() const;
	void reset();
	void setPlane(Plane_ptr plane);

private slots:
	void createPlane();
	void updatePlaneOrigin();
	void updatePlaneNormal();

private:
	VectorInput* m_originInput;
	VectorInput* m_normalInput;
	Plane_ptr m_plane;
	bool m_planeInserted;
	PlaneListener& m_planeListener;

};

#endif // PLANEFORM_H
