#ifndef QTH_BASE_H
#define QTH_BASE_H

#include <QThread>
#include "qattitudeindicator.h"

#define QTHREAD_HORIZON           0
#define QTHREAD_COMUNICATION      1

class QTh_Base : public QThread
{
    //Q_OBJECT
public:
    explicit QTh_Base(int type, QObject *parent = 0);
    void run();


    qAttitudeIndicator  *attInd;

private:
    int                 typeThread;



public slots:

};

#endif // QTH_BASE_H
