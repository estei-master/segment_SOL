#ifndef BATTERY_H
#define BATTERY_H

#include <QMainWindow>
#include "QProgressBar"

/**
* \file battery.h
* \brief Fichier d'inclusion des librairies nécessaires au widget permettant l'affichage de l'état des batteries.
* \author Martin PRADEAU / Pierre POUCH
* \version Version finale
* \date Janvier 2014
*/

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
