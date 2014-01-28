#ifndef SIGNALRF_H
#define SIGNALRF_H

#include <QMainWindow>
#include "QProgressBar"

class signalRF : public QMainWindow
{
    Q_OBJECT
public:
    explicit signalRF(QWidget *parent = 0);
protected:
    void timerEvent(QTimerEvent *event);
private:
    QProgressBar *progressBar1;
    QProgressBar *progressBar2;
    QProgressBar *progressBar3;
    QProgressBar *progressBar4;
signals:

public slots:
    
};

#endif // SIGNALRF_H
