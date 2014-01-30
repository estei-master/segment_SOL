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
#include <QtGui/qgridlayout.h>

/**
* \file mainwindow.cpp
* \brief Ce programme permet le placement de tous les widgets ou objets nécessaires au fonctionnement de l'application.
* \author Martin PRADEAU
* \version Version finale
* \date Janvier 2014
*/


/*  Dans cette classe se feront toutes les mises à jour graphiques
 *  Les moyens :
 *      - Timer :  -- De la classe avec startTimer et tiemerEvent()
 *                 -- Et QTimer, connecté à un slot
 *    - Qthread :     Les signaux et slots permettent de passer des paramètres,
 *                    Possibilité de démarrer des threads qui surveillent le niveau de batterie, gèrent la communication...
 *                    et échanger des paramètres avec connet()
 *
 *  Rappel : l'horizon artificiel, c'est pour le vol aux instruments.
 */

/**
 * \brief    Constructeur
 * \details  Permet la déclaration des widgets présents dans l'application.
 * \param    QWidget *parent
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Déclaration du widget permettant l'affichage vidéo des et du thread utilisé pour la communication et l'affichange de l'horizon artificiel */

    threadBase = new QBase();
    m_cvwidget = new CameraWidget();

    /* Déclaration du widget permettant l'affichage de l'état de la batterie et placement dans les layouts définis à l'aide de QtDesigner */

    batterie = new battery;
    ui->batterylayout->addWidget(batterie);
    batterie2 = new battery;
    ui->batterylayout_2->addWidget(batterie2);

    /* Déclaration des progressBars permettant l'affichage de la puissance du signal */

    progressBar1 = new QProgressBar(this);
    progressBar1->setGeometry(10, 10, 5, 10);
    progressBar1->setOrientation(Qt::Vertical);
    progressBar1->setTextVisible(false);
    progressBar1->setStyleSheet("QProgressBar::chunk{background-color:orange}");
    progressBar2 = new QProgressBar(this);
    progressBar2->setGeometry(10, 10, 5, 20);
    progressBar2->setOrientation(Qt::Vertical);
    progressBar2->setTextVisible(false);
    progressBar2->setStyleSheet("QProgressBar::chunk{background-color:orange}");
    progressBar3 = new QProgressBar(this);
    progressBar3->setGeometry(10, 10, 5, 30);
    progressBar3->setOrientation(Qt::Vertical);
    progressBar3->setTextVisible(false);
    progressBar3->setStyleSheet("QProgressBar::chunk{background-color:orange}");
    progressBar4 = new QProgressBar(this);
    progressBar4->setGeometry(10, 10, 5, 40);
    progressBar4->setOrientation(Qt::Vertical);
    progressBar4->setTextVisible(false);
    progressBar4->setStyleSheet("QProgressBar::chunk{background-color:orange}");

    //startTimer(200);

    /* Ajout des widgets affichant la puissance du signal dans les layouts prédéfinis à l'aide de QtDesigner */

    ui->powerlayout1->addWidget(progressBar1);
    ui->powerlayout2->addWidget(progressBar2);
    ui->powerlayout3->addWidget(progressBar3);
    ui->powerlayout4->addWidget(progressBar4);



    /* Déclaration du widget Lightmaps afin d'afficher la carte dans un layout préfdéfini à l'aide de QtDesigner */

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
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
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
                QNetworkConfiguration::Discovered)
            {
                config = manager.defaultConfiguration();
            }

            networkSession = new QNetworkSession(config, this);
            connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

            networkSession->open();
    }

    else
    {
            networkSession = 0;
    }

    /* Ajout d'un titre pour l'application */

    setWindowTitle(tr("WELCOME TO THE APPLICATION OF ESTEI STUDENTS !"));
    //startTimer(200);


    indexOnglet = ui->Onglet->currentIndex();
    bVideoIsOn = false;

    /* Mise à zéro de m_photoCounter et connexion entre le bouton "SAVE PICTURE" et la fonction décrite plus bas dans ce fichier */

    m_photoCounter = 0;
    connect(ui->Photo, SIGNAL(pressed()), this, SLOT(savePicture()));

    /* Connexion du bouton "START/STOP VIDEO STREAMING" au slot ButtonVideo */

    connect(ui->Onglet, SIGNAL(currentChanged(int)), this, SLOT(ChangeOnglet(int)));
    connect(ui->VideoStreaming, SIGNAL(clicked()), this, SLOT(ButtonVideo()));
    startTimer(47);     /* Environ 21 images/s */

    /*  Lancement du thread */
    threadBase->start();

}

/**
 * \brief    Destructeur
 * \details  Permet la destruction du thread et de la capture vidéo.
 * \param    void
 */

MainWindow::~MainWindow()
{
    if(m_camera != NULL)                                                        /* Appel à la fonction qui permet de détruire la capture de la vidéo si son argument n'est pas nul */
        cvReleaseCapture(&m_camera);
    threadBase->deleteLater();                                                  /* Destruction du thread */
    delete ui;                                                                  /* Destruction du fichier .ui */
}

/* Fontion nécessaire au fonctionnement de la map */

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

/* Fonction de tes du GPS */

void MainWindow::testGps()
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

/* Fonction qui permet de charger la carte sur internet */

void MainWindow::aboutOsm()
{
    QDesktopServices::openUrl(QUrl("http://www.openstreetmap.org"));
}

/**
 * \brief    Timer
 * \details  Permet le rafraichissement de l'affichage vidéo.
 * \param    QTimerEvent *
 */

void MainWindow::timerEvent(QTimerEvent*)
{
    QTime time;
    QString Qtmp;
    std::ofstream    f("/tmp/LogMainWindow", std::ios_base::app);

    time.start();

    switch(indexOnglet)
    {

        case INDEX_ONGLET_CAMERA:                                                       /* Dans le cas où l'onglet "VOL IMMERSIF est sélectionné */
            if(bVideoIsOn)                                                              /* Test si la vidéo est active */
            {
                assert(m_camera);                                                       /* Appel à la fonction assert qui renvoie une exception en cas d'erreur en précisant le fichier concerné et le numéro de ligne */
                image = cvQueryFrame(m_camera);                                         /* Acquisition de la vidéo */
                /*image = display.image_camera(m_camera);*/
                assert(image);                                                          /* Appel à la fonction assert qui renvoie une exception en cas d'erreur en précisant le fichier concerné et le numéro de ligne */
                m_cvwidget->putFrame(image);                                            /* Envoi de l'acquisition afin de l'afficher */
            }
        break;
    default:
        break;
     }

    /* Pour la map */

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

    Qtmp.sprintf("Time to execut mainWindowTimeEvent : %d\n",time.elapsed());
    f.write(Qtmp.toStdString().c_str(), Qtmp.length());

    /* Simulation du niveau de puissance de la liaison RF */

    //QFile fichier2("/home/estei/projet/fonctionnel/GPS/signalRF.txt");
    QFile fichier2("/home/Guillaume_Pierre/RF/signalRF.txt");
    QString ligne2;
    QTextStream flux2(&fichier2);

    if(fichier2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!flux2.atEnd())
        {
            ligne2 = fichier2.readLine();
        }
        fichier2.close();
    }
    else
        ligne2 = "Impossible d'ouvrir le fichier !";

    if(ligne2.toInt() < 1)
    {
        progressBar1->setValue(0);
        progressBar2->setValue(0);
        progressBar3->setValue(0);
        progressBar4->setValue(0);
    }

    else if(1 <= ligne2.toInt()&&ligne2.toInt() < 2)
    {
        progressBar1->setValue(100);
        progressBar2->setValue(0);
        progressBar3->setValue(0);
        progressBar4->setValue(0);
    }

    else if(2 <= ligne2.toInt()&&ligne2.toInt() < 3)
    {
        progressBar1->setValue(100);
        progressBar2->setValue(100);
        progressBar3->setValue(0);
        progressBar4->setValue(0);
    }

    else if(3 <= ligne2.toInt()&&ligne2.toInt() < 4)
    {
        progressBar1->setValue(100);
        progressBar2->setValue(100);
        progressBar3->setValue(100);
        progressBar4->setValue(0);
    }

    else if(4 <= ligne2.toInt()&&ligne2.toInt() < 5)
    {
        progressBar1->setValue(100);
        progressBar2->setValue(100);
        progressBar3->setValue(100);
        progressBar4->setValue(100);
    }

}


/**
 * \brief    Changement d'onglet
 * \details  Fonction qui permet l'ajout ou la destruction de widgets suivant l'onglet sélectionnée.
 * \param    int index
 */

void MainWindow::ChangeOnglet(int index)
{
    indexOnglet = index;

    switch(indexOnglet) {

    case INDEX_ONGLET_CAMERA:
            ui->horizon_layout->removeWidget(threadBase->Horizon);
            ui->maplayout2->removeWidget(map);
            ui->maplayout->addWidget(map);
            ui->batterylayout2->removeWidget(batterie);
            ui->batterylayout->addWidget(batterie);
            ui->batterylayout2_2->removeWidget(batterie2);
            ui->batterylayout_2->addWidget(batterie2);
            ui->powerlayout1_2->removeWidget(progressBar1);
            ui->powerlayout2_2->removeWidget(progressBar2);
            ui->powerlayout3_2->removeWidget(progressBar3);
            ui->powerlayout4_2->removeWidget(progressBar4);
            ui->powerlayout1->addWidget(progressBar1);
            ui->powerlayout2->addWidget(progressBar2);
            ui->powerlayout3->addWidget(progressBar3);
            ui->powerlayout4->addWidget(progressBar4);

        break;

    case INDEX_ONGLET_HORIZON:
            ui->horizon_layout->addWidget(threadBase->Horizon);
            ui->maplayout->removeWidget(map);
            ui->maplayout2->addWidget(map);
            ui->batterylayout->removeWidget(batterie);
            ui->batterylayout2->addWidget(batterie);
            ui->batterylayout_2->removeWidget(batterie2);
            ui->batterylayout2_2->addWidget(batterie2);
            ui->powerlayout1->removeWidget(progressBar1);
            ui->powerlayout2->removeWidget(progressBar2);
            ui->powerlayout3->removeWidget(progressBar3);
            ui->powerlayout4->removeWidget(progressBar4);
            ui->powerlayout1_2->addWidget(progressBar1);
            ui->powerlayout2_2->addWidget(progressBar2);
            ui->powerlayout3_2->addWidget(progressBar3);
            ui->powerlayout4_2->addWidget(progressBar4);

        break;
    default:
        break;
    }
}

/* */
/**
 * \brief    ButtonVideo
 * \details  Fonction permettant la destructution ou l'ajout du widget permettant la capture de la vidéo.
 * \param    void
 */

void MainWindow::ButtonVideo()
{
    if(bVideoIsOn)
    {
        ui->cameralayout->removeWidget(m_cvwidget);
        cvReleaseCapture(&m_camera);
        bVideoIsOn = false;
    }

    else
    {
        ui->cameralayout->addWidget(m_cvwidget);
        m_camera = cvCreateCameraCapture(0);
        bVideoIsOn = true;
    }
}

/**
 * \brief    Arrêt d'urgence
 * \details  Permet l'arrêt du drône en cas de grave problème.
 * \param    void
 */

void MainWindow::ButtonEmergency()
{

}

/**
 * \brief    Prise de photos
 * \details  Fonction permettant l'enregistrement de photos via un appui sur le bouton "SAVE PICTURE".
 * \param    void
 */

void MainWindow::savePicture(void)
{
    IplImage *image = cvQueryFrame(m_camera);
    QPixmap photo = m_cvwidget->toPixmap(image);

    if (photo.save("/tmp/Picture" + QString::number(m_photoCounter) + ".jpg"))                  /* Définition du chemin d'enregistrement */
    {
        qDebug("Picture successfully saved!");
        m_photoCounter++;                                                                       /* Incrémentation de m_photoCounter */
    }

    else
    {
        qDebug("Error while saving the picture");
    }
}

