#include "happah/gui/GUIManager.h"
#include "happah/gui/Worker.h"
#include "happah/simulations/WormGearGrind.h"

#ifndef WORMGEARGRINDWORKER_H_
#define WORMGEARGRINDWORKER_H_

class WormGearGrindWorkerListener: public QObject {
	Q_OBJECT
private:
	GUIManager* m_guiManager;
public:
	WormGearGrindWorkerListener(GUIManager* guiManager): m_guiManager(guiManager) {}

	public slots:
		void insert(WormGearGrind_ptr wormGearGrind) {
			m_guiManager->insert(wormGearGrind);
		}
};

class WormGearGrindWorker: public Worker {
	Q_OBJECT
	WormGearGrind_ptr m_wormGearGrind;
	WormGearGrindWorkerListener* m_listener;
public:
	WormGearGrindWorker(WormGearGrind_ptr wormGearGrind, QThread* thread, WormGearGrindWorkerListener* wormGearGrindWorkerListener);
	~WormGearGrindWorker();
	public slots:
	    void process();

	signals:
	    void insert(WormGearGrind_ptr wormGearGrind);
};

#endif /* WORMGEARGRINDWORKER_H_ */
