#ifndef BATTERIE_H
#define BATTERIE_H

#include <QMainWindow>
#include "QProgressBar"

class batterie : public QMainWindow
{
    Q_OBJECT
public:
    explicit batterie(QWidget *parent = 0);
    
protected:
    void timerEvent(QTimerEvent *event);
private:
    QProgressBar *progressBar;
signals:
    
public slots:
    
};

#endif // BATTERIE_H
