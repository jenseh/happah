#ifndef PLANEFORM_H
#define PLANEFORM_H

#include "happah/geometries/Plane.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/VectorInput.h"
#include "happah/gui/forms/Form.h"

class PlaneForm : public Form {
Q_OBJECT

public:
	PlaneForm(GUIManager& guiManager, QWidget* parent = NULL);
	~PlaneForm();

	Plane_ptr getPlane() const;
	void reset();
	void setPlane(Plane_ptr plane);

private slots:
	void createPlane();
	void updatePlaneOrigin();
	void updatePlaneNormal();

private:
	GUIManager& m_guiManager;
	VectorInput* m_originInput;
	VectorInput* m_normalInput;
	Plane_ptr m_plane;
	bool m_planeInserted;

};

#endif // PLANEFORM_H
