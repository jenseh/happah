#ifndef SPHERE_PATCH_FORM_H_
#define SPHERE_PATCH_FORM_H_

#include "happah/geometries/SpherePatch.h"
#include "happah/gui/GUIManager.h"
#include "happah/gui/forms/Form.h"

class SpherePatchForm : public Form{
Q_OBJECT
public:
	SpherePatchForm(GUIManager& guiManager, QWidget* parent = 0);
	virtual ~SpherePatchForm();

	SpherePatch_ptr getSpherePatch() const;
	void reset();
	void setSpherePatch(SpherePatch_ptr spherePatch);
	void handleSelection(){emit selected(this);}
signals:
	void selected(Form* form);
private:
	GUIManager& m_guiManager;
	SpherePatch_ptr m_spherePatch;
	bool m_spherePatchInserted;

	void updateSpherePatch();
private slots:
	void createSpherePatch();
};

#endif /* SPHEREPATCHFORM_H_ */
