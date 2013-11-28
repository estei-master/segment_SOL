/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtNetwork>
#include "lightmaps.h"
#include "mapzoom.h"

MapZoom::MapZoom()
    : QMainWindow(0)
{
    map = new LightMaps(this);
    setCentralWidget(map);
    map->setFocus();

    QAction *THALES_AvionicsAction = new QAction(tr("&THALES_Avionics"), this);
    QAction *MAISONAction = new QAction(tr("&MAISON"), this);
    QAction *ESTEIAction = new QAction(tr("&ESTEI"), this);
    QAction *nightModeAction = new QAction(tr("Night Mode"), this);
    nightModeAction->setCheckable(true);
    nightModeAction->setChecked(false);
    QAction *osmAction = new QAction(tr("About OpenStreetMap"), this);
    connect(THALES_AvionicsAction, SIGNAL(triggered()), SLOT(chooseTHALES_Avionics()));
    connect(MAISONAction, SIGNAL(triggered()), SLOT(chooseMAISON()));
    connect(ESTEIAction, SIGNAL(triggered()), SLOT(chooseESTEI()));
    connect(nightModeAction, SIGNAL(triggered()), map, SLOT(toggleNightMode()));
    connect(osmAction, SIGNAL(triggered()), SLOT(aboutOsm()));

#if defined(Q_OS_SYMBIAN) || defined(Q_OS_WINCE_WM)
    menuBar()->addAction(THALES_AvionicsAction);
    menuBar()->addAction(MAISONAction);
    menuBar()->addAction(ESTEIAction);
    menuBar()->addAction(nightModeAction);
    menuBar()->addAction(osmAction);
#else
    QMenu *menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(THALES_AvionicsAction);
    menu->addAction(MAISONAction);
    menu->addAction(ESTEIAction);
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

void MapZoom::chooseTHALES_Avionics()
{
    map->setCenter(44.854955, -0.697322);
}

void MapZoom::chooseMAISON()
{
    map->setCenter(44.994604, -0.446722);
}

void MapZoom::chooseESTEI()
{
    map->setCenter(44.86121, -0.557104);
}

void MapZoom::aboutOsm()
{
    QDesktopServices::openUrl(QUrl("http://www.openstreetmap.org"));
}
