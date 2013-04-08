#include "happah/gui/GUIManager.h"
#include "happah/gui/Worker.h"
#include "happah/simulations/DiscGearGrind.h"

#ifndef DISCGEARGRINDWORKER_H_
#define DISCGEARGRINDWORKER_H_

class DiscGearGrindWorkerListener: public QObject {
	Q_OBJECT
private:
	GUIManager* m_guiManager;
public:
	DiscGearGrindWorkerListener(GUIManager* guiManager): m_guiManager(guiManager) {}

	public slots:
		void insert(DiscGearGrind_ptr discGearGrind) {
			m_guiManager->insert(discGearGrind);
		}
};

class DiscGearGrindWorker: public Worker {
	Q_OBJECT
	DiscGearGrind_ptr m_discGearGrind;
	DiscGearGrindWorkerListener* m_listener;
public:
	DiscGearGrindWorker(DiscGearGrind_ptr discGearGrind, QThread* thread, DiscGearGrindWorkerListener* discGearGrindWorkerListener);
	~DiscGearGrindWorker();
	public slots:
	    void process();

	signals:
	    void insert(DiscGearGrind_ptr discGearGrind);
};

#endif /* DISCGEARGRINDWORKER_H_ */
