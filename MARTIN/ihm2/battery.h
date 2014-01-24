#ifndef BATTERY_H
#define BATTERY_H

#include <QMainWindow>
#include "QProgressBar"

class battery : public QMainWindow
{
    Q_OBJECT
public:
    explicit battery(QWidget *parent = 0);

protected:
    void timerEvent(QTimerEvent *event);
private:
    QProgressBar *progressBar;
signals:

public slots:

};

#endif // BATTERY_H
