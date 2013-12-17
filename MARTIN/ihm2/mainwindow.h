#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

//#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
#include "camerawidget.h"
#include "qattitudeindicator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    CameraWidget *m_cvwidget;
    CvCapture *m_camera;
    int m_photoCounter;

    qAttitudeIndicator *attInd;

    Ui::MainWindow *ui;

protected:
    void timerEvent(QTimerEvent*);

public slots:
   // void savePicture(void);

};


#endif





