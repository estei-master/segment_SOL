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

MapZoom::MapZoom()
    : QMainWindow(0)
{
    map = new LightMaps(this);
    setCentralWidget(map);
    map->setFocus();

    /*m_normalMap = new SlippyMap(this);
    connect(m_normalMap, SIGNAL(updated(QRect)), SLOT(updateMap(QRect)));*/

    QAction *testGpsAction = new QAction(tr("&testGps"), this);
    QAction *nightModeAction = new QAction(tr("Night Mode"), this);
    nightModeAction->setCheckable(true);
    nightModeAction->setChecked(false);
    QAction *osmAction = new QAction(tr("About OpenStreetMap"), this);
    connect(testGpsAction, SIGNAL(triggered()), SLOT(testGps()));
    connect(nightModeAction, SIGNAL(triggered()), map, SLOT(toggleNightMode()));
    connect(osmAction, SIGNAL(triggered()), SLOT(aboutOsm()));

#if defined(Q_OS_SYMBIAN) || defined(Q_OS_WINCE_WM)
    menuBar()->addAction(testGpsAction);
    menuBar()->addAction(nightModeAction);
    menuBar()->addAction(osmAction);
#else
    QMenu *menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(testGpsAction);
    menu->addSeparator();
    menu->addAction(nightModeAction);
    menu->addAction(osmAction);
#endif

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id =
            settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system
        // default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    } else {
        networkSession = 0;
    }

    setWindowTitle(tr("Light Maps"));

    startTimer(200);
}

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
    QFile fichier("/home/pierre/Documents/GPS/testQT/lightmaps/dataIHM.txt");
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
    QFile fichier("/home/pierre/Documents/GPS/testQT/lightmaps/dataIHM.txt");
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
