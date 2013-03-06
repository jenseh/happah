#include <sstream>

#include "happah/gui/GUIManager.h"

GUIManager::GUIManager(SceneManager& sceneManager)
	:  m_counter(0),
		m_drawManager(sceneManager), 
		m_mainWindow(sceneManager, *this, m_drawManager), 
		m_sceneGraphExplorerPanel(m_mainWindow.getSceneGraphExplorerPanel()),
		m_sceneManager(sceneManager),
		m_toolPanel(m_mainWindow.getToolPanel()) {
	m_sceneManager.registerListener(this);
}

GUIManager::~GUIManager() {}

void GUIManager::handleGUIStateNodesDeletedEvent(vector<GUIStateNode_ptr>& guiStateNodes) {

}

void GUIManager::handleGUIStateNodeSelectedEvent(GUIStateNode_ptr guiStateNode) {
	m_toolPanel->setForm(guiStateNode->getForm());
}

bool GUIManager::init() {
	if (!m_drawManager.init()) {
		fprintf(stderr, "Draw manager initialization failed.\n");
		return false;
	}
	m_mainWindow.show();
	return true;
}

void GUIManager::insert(InvoluteGear_ptr involuteGear) {
	TriangleMesh_ptr involuteGearTriangleMesh = TriangleMesh_ptr(involuteGear->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	m_sceneManager.insert(involuteGear, involuteGearTriangleMesh, color);
	ostringstream oss;
	oss << "Involute Gear " << m_counter++;
	InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode = InvoluteGearGUIStateNode_ptr(new InvoluteGearGUIStateNode(involuteGear, m_toolPanel->getInvoluteGearForm(), oss.str()));
	involuteGearGUIStateNode->setTriangleMesh(involuteGearTriangleMesh);
	m_sceneManager.insert(involuteGear, involuteGearGUIStateNode);
}

void GUIManager::update(InvoluteGear_ptr involuteGear) {
	GUIStateNode_ptr guiStateNode = m_guiStateNodes[involuteGear];
	if(!guiStateNode) {
		cerr << "GUI state node for involute gear not found." << endl;
		return;
	}
	m_sceneManager.remove(involuteGear, guiStateNode->getTriangleMesh());
	TriangleMesh_ptr involuteGearTriangleMesh = TriangleMesh_ptr(involuteGear->toTriangleMesh());
	hpcolor color(1.0, 0.0, 0.0, 1.0);
	guiStateNode->setTriangleMesh(involuteGearTriangleMesh);
	m_sceneManager.insert(involuteGear, involuteGearTriangleMesh, color);
}


void GUIManager::sceneChanged() {
	m_sceneGraphExplorerPanel->clear();
	m_sceneManager.accept(*this);
}

void GUIManager::visit(InvoluteGearGUIStateNode_ptr involuteGearGUIStateNode) {
	m_guiStateNodes[involuteGearGUIStateNode->getInvoluteGear()] = involuteGearGUIStateNode;
	m_sceneGraphExplorerPanel->addItem(QString(involuteGearGUIStateNode->getName().c_str()), involuteGearGUIStateNode);
}
