
#ifndef WORKER_H_
#define WORKER_H_
#include <QThread>
class Worker: public QObject {
    Q_OBJECT
public slots:
    virtual void process()= 0;

    signals:
        void finished();

};

#endif /* WORKER_H_ */
