#include <QtGui/QApplication>
#include "mainwindow.h"
#include "librairie.h"
#include "mydisplay.h"
#include "battery.h"



#include <QtGui>
#include <QtNetwork>
#include <QTextStream>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QVector>
#include <QPainter>
#include "lightmaps.h"

#include "slippymap.h"
#include <stdio.h>
#include <stdlib.h>

#include <fstream>


/*  Dans ce cette classe se feront toutes les mises à jour graphiques
 *  Les moyens :
 *      - Timer :  -- De la classe avec startTimer et tiemerEvent()
 *                 -- Et QTimer, connecté à un slot
 *    - Qthread :     Les signaux et slots permettent de passer des paramètres,
 *                    tu peux démarrer des threads qui surveillent le niveau de batterie, gèrent la communication, ...
 *                    et échanger des paramètres avec connet()
 *
 *  Rappel : l'horizon artificiel, c'est pour le vol aux instruments.
 *           Au pire tu le place dans un angle et tu le garde toujours visible.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadBase = new QBase();
    m_cvwidget = new CameraWidget();

    batterie = new battery;
    ui->batterylayout->addWidget(batterie);
    batterie2 = new battery;
    ui->batterylayout_2->addWidget(batterie2);



    map = new LightMaps();
    ui->maplayout->addWidget(map);


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

        setWindowTitle(tr("WELCOME TO THE APPLICATION OF ESTEI STUDENTS !"));

        //startTimer(200);




    indexOnglet = ui->Onglet->currentIndex();
    bVideoIsOn = false;

    m_photoCounter = 0;
    connect(ui->Photo, SIGNAL(pressed()), this, SLOT(savePicture()));

    connect(ui->Onglet, SIGNAL(currentChanged(int)), this, SLOT(ChangeOnglet(int)));
    connect(ui->VideoStreaming, SIGNAL(clicked()), this, SLOT(ButtonVideo()));
    startTimer(47);     //Environ 21 images/s

    /*  And Go!!    */
    threadBase->start();

}


MainWindow::~MainWindow()
{

    threadBase->terminate();
    if(m_camera != NULL)
        cvReleaseCapture(&m_camera);
    delete threadBase;
    delete ui;
}


void MainWindow::sessionOpened()
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

void MainWindow::testGps()
{
    QFile fichier("/home/estei/projet/fonctionnel/GPS/testQT/lightmaps/dataIHM.txt");
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


void MainWindow::aboutOsm()
{
    QDesktopServices::openUrl(QUrl("http://www.openstreetmap.org"));
}

//Puts a new frame in the widget every 47 msec : GRAPHIQUE
void MainWindow::timerEvent(QTimerEvent*)
{

    QTime time;
    QString Qtmp;
    std::ofstream    f("/tmp/LogMainWindow", std::ios_base::app);

    time.start();

    switch(indexOnglet) {

    case INDEX_ONGLET_CAMERA:
        if(bVideoIsOn) {
           assert(m_camera);
           image = cvQueryFrame(m_camera);

           /*image = display.image_camera(m_camera);*/
           assert(image);

            m_cvwidget->putFrame(image);

        }


        break;
    default:
        break;
     }

    QFile fichier("/home/estei/projet/fonctionnel/GPS/testQT/lightmaps/dataIHM.txt");
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

    Qtmp.sprintf("Time to execut mainWindowTimeEvent : %d\n",time.elapsed());
    f.write(Qtmp.toStdString().c_str(), Qtmp.length());
}

void MainWindow::ChangeOnglet(int index)
{
    indexOnglet = index;

    switch(indexOnglet) {

    case INDEX_ONGLET_CAMERA:
            ui->horizon_layout->removeWidget(threadBase->Horizon);
            //threadBase->terminate();
            ui->maplayout2->removeWidget(map);
            ui->maplayout->addWidget(map);
            ui->batterylayout2->removeWidget(batterie);
            ui->batterylayout->addWidget(batterie);
            ui->batterylayout2_2->removeWidget(batterie2);
            ui->batterylayout_2->addWidget(batterie2);

        break;

    case INDEX_ONGLET_HORIZON:
            //threadBase->start();
            ui->horizon_layout->addWidget(threadBase->Horizon);
            ui->maplayout->removeWidget(map);
            ui->maplayout2->addWidget(map);
            ui->batterylayout->removeWidget(batterie);
            ui->batterylayout2->addWidget(batterie);
            ui->batterylayout_2->removeWidget(batterie2);
            ui->batterylayout2_2->addWidget(batterie2);
        break;
    default:
        break;
    }
}

void MainWindow::ButtonVideo()
{
    if(bVideoIsOn) {
        ui->cameralayout->removeWidget(m_cvwidget);
        cvReleaseCapture(&m_camera);
        bVideoIsOn = false;
    }
    else {
        ui->cameralayout->addWidget(m_cvwidget);
        m_camera = cvCreateCameraCapture(0);
        bVideoIsOn = true;
    }
}

void MainWindow::ButtonEmergency()
{


}

//Saves a new picture

void MainWindow::savePicture(void)
{
    IplImage *image = cvQueryFrame(m_camera);

    QPixmap photo = m_cvwidget->toPixmap(image);

    if (photo.save("/tmp/Picture" + QString::number(m_photoCounter) + ".jpg")) {
        qDebug("Picture successfully saved!");
        m_photoCounter++;
    } else {
        qDebug("Error while saving the picture");
    }
}

