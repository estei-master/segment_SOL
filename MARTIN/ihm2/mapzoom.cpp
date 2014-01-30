#include <QtGui>
#include <QtNetwork>
#include <QTextStream>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QVector>
#include <QPainter>
#include "lightmaps.h"
#include "mapzoom.h"
#include "slippymap.h"
#include <stdio.h>
#include <stdlib.h>


void MapZoom::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice) {
        id = networkSession->sessionProperty(
                QLatin1String("UserChoiceConfiguration")).toString();
    } else {
        id = config.identifier();
    }

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

void MapZoom::testGps()
{
    QFile fichier("/home/Guillaume_Pierre/GPS/dataIHM.txt");
    QString ligne;
    float coordonnees[2];
    int i = 0;
    QTextStream flux(&fichier);

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!flux.atEnd())
        {
            ligne = fichier.readLine();
            if(i < 2)
                coordonnees[i] = ligne.toFloat();
            i++;
        }
        fichier.close();
        i = 0;
    }
    else
        ligne = "Impossible d'ouvrir le fichier !";

    latitude = coordonnees[0];
    longitude = coordonnees[1];
    map->setCenter(latitude, longitude);
}

void MapZoom::timerEvent(QTimerEvent *event)
{
    QFile fichier("/home/Guillaume_Pierre/GPS/dataIHM.txt");
    QString ligne;
    float coordonnees[2];
    int i = 0;
    QTextStream flux(&fichier);

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!flux.atEnd())
        {
            ligne = fichier.readLine();
            if(i < 2)
                coordonnees[i] = ligne.toFloat();
            i++;
        }
        fichier.close();
        i = 0;
    }
    else
        ligne = "Impossible d'ouvrir le fichier !";

    latitude = coordonnees[0];
    longitude = coordonnees[1];
    map->setCenter(latitude, longitude);
}

void MapZoom::aboutOsm()
{
    QDesktopServices::openUrl(QUrl("http://www.openstreetmap.org"));
}
