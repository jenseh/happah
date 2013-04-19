#include "WormGearGrindWorker.h"
#include <QMetaType>

WormGearGrindWorker::WormGearGrindWorker(WormGearGrind_ptr wormGearGrind, QThread* thread, WormGearGrindWorkerListener* wormGearGrindWorkerListener):
	m_wormGearGrind(wormGearGrind), m_listener(wormGearGrindWorkerListener) {
	this->moveToThread(thread);
	connect(thread, SIGNAL(started()), this, SLOT(process()));
	connect(this, SIGNAL(finished()), thread, SLOT(quit()));
	connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	qRegisterMetaType<WormGearGrind_ptr>("WormGearGrind_ptr");
	connect(this, SIGNAL(insert(WormGearGrind_ptr)),
			m_listener, SLOT(insert(WormGearGrind_ptr)),
			Qt::ConnectionType::QueuedConnection);
}

WormGearGrindWorker::~WormGearGrindWorker() {
	delete m_listener;
}

void WormGearGrindWorker::process() {
	m_wormGearGrind->runSimulation();
	m_listener->insert(m_wormGearGrind);
	emit insert(m_wormGearGrind);
	emit finished();
}
