#include "DiscGearGrindWorker.h"
#include <QMetaType>

DiscGearGrindWorker::DiscGearGrindWorker(DiscGearGrind_ptr discGearGrind, QThread* thread, DiscGearGrindWorkerListener* discGearGrindWorkerListener):
	m_discGearGrind(discGearGrind), m_listener(discGearGrindWorkerListener) {
	this->moveToThread(thread);
	connect(thread, SIGNAL(started()), this, SLOT(process()));
	connect(this, SIGNAL(finished()), thread, SLOT(quit()));
	connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	qRegisterMetaType<DiscGearGrind_ptr>("DiscGearGrind_ptr");
	connect(this, SIGNAL(insert(DiscGearGrind_ptr)),
			m_listener, SLOT(insert(DiscGearGrind_ptr)),
			Qt::ConnectionType::QueuedConnection);
}

DiscGearGrindWorker::~DiscGearGrindWorker() {
	delete m_listener;
}

void DiscGearGrindWorker::process() {
	m_discGearGrind->runSimulation();
	m_listener->insert(m_discGearGrind);
	emit insert(m_discGearGrind);
	emit finished();
}
