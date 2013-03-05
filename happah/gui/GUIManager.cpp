#include "happah/gui/GUIManager.h"

GUIManager::GUIManager(SceneManager& sceneManager)
	: m_drawManager(sceneManager), m_mainWindow(sceneManager, *this, m_drawManager), m_sceneManager(sceneManager) {}

GUIManager::~GUIManager() {}

bool GUIManager::init() {
	if (!m_drawManager.init()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return false;
	}
	m_mainWindow.show();
	return true;
}

void GUIManager::insert(InvoluteGear_ptr involuteGear) {
	TriangleMesh_ptr involuteGearMesh = TriangleMesh_ptr(involuteGear->toTriangleMesh());
	//involuteGearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f);
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager.insert(involuteGear, involuteGearMesh, color);
	InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode = InvoluteGearGUIStateNode_ptr(new InvoluteGearGUIStateNode(involuteGear, m_mainWindow.getInvoluteGearForm(), "Involute Gear"));
	m_sceneManager.insert(involuteGear, involuteGearGUIStateNode);
	m_lastInvoluteGearMesh = involuteGearMesh;
}

void GUIManager::update(InvoluteGear_ptr involuteGear) {
	m_sceneManager.remove(involuteGear, m_lastInvoluteGearMesh);
	TriangleMesh_ptr involuteGearMesh = TriangleMesh_ptr(involuteGear->toTriangleMesh());
	//involuteGearMesh->setMaterial(0.25f, 0.5f, 1.0f, 10.0f);
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager.insert(involuteGear, involuteGearMesh, color);
	m_lastInvoluteGearMesh = involuteGearMesh;
}

