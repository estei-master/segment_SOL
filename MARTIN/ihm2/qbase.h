#ifndef QBASE_H
#define QBASE_H

#include <QThread>
#include <QMessageBox>
#include "nunchuck.h"
#include "zigbee.h"
#include "qattitudeindicator.h"

class QBase : public QThread
{
    Q_OBJECT
public:
    explicit QBase(QObject *parent = 0);

    void run();
    void terminate();

    qAttitudeIndicator   *Horizon;
    Nunchuck             *NunchuckDirection;
    Nunchuck             *NunchuckAltitude;
    ZigBee               *ModuleZigBee;
private:
    QMessageBox          MsgBox;
signals:

public slots:
    void enableCamera(bool bEnable);
};

#endif // QBASE_H
