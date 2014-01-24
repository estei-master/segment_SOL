#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
//#include <opencv/highgui.h>
#include </usr/local/include/opencv2/highgui.hpp>
#include <assert.h>
#include "mydisplay.h"
#include "camerawidget.h"
#include "qbase.h"
#include "battery.h"
#include "ui_mainwindow.h"

#include "lightmaps.h"
#include "slippymap.h"

#define INDEX_ONGLET_CAMERA  0
#define INDEX_ONGLET_HORIZON 1

class QNetworkSession;
class LightMaps;
class SlippyMap;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    qreal latitude, longitude;

    ~MainWindow();

private slots:
    void sessionOpened();
    void testGps();
    void aboutOsm();

private:
    Ui::MainWindow  *ui;

    QBase           *threadBase;

    CameraWidget    *m_cvwidget;
    CvCapture       *m_camera;
    IplImage        *image;
    MyDisplay       display;

    LightMaps       *map;
    QNetworkSession *networkSession;

    battery         *batterie;
    battery         *batterie2;

    int             m_photoCounter;
    int             indexOnglet;
    bool            bVideoIsOn;

protected:
   void timerEvent(QTimerEvent*);

public slots:
    void ChangeOnglet(int index);
    void ButtonVideo();
    void ButtonEmergency();

    void savePicture(void);

};

#endif




