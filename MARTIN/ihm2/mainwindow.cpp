#include <QtGui/QApplication>
#include "mainwindow.h"
#include "camerawidget.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include "qattitudeindicator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CvCapture *camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage *image = cvQueryFrame(camera);
    assert(image);

    m_camera = camera;
    m_photoCounter = 0;
    m_cvwidget = new CameraWidget(this);
    startTimer(100);  // 0.1-second timer
    //sleep(3);
    ui->gridLayout->addWidget(m_cvwidget);

    attInd = new qAttitudeIndicator(this);
    ui->gridLayout_2->addWidget(attInd);
}

MainWindow::~MainWindow()
{
    CvCapture *camera = cvCreateCameraCapture(0);

    cvReleaseCapture(&camera);
    delete ui;
}


//Puts a new frame in the widget every 100 msec
void MainWindow::timerEvent(QTimerEvent*)
{
    IplImage *image = cvQueryFrame(m_camera);
    m_cvwidget->putFrame(image);

}

/*//Saves a new picture
void MainWindow::savePicture(void)
{
    IplImage *image = cvQueryFrame(m_camera);

    QPixmap photo = m_cvwidget->toPixmap(image);

    if (photo.save("/home/rborges/Desktop/picture" + QString::number(m_photoCounter) + ".jpg")) {
        qDebug("Picture successfully saved!");
        m_photoCounter++;
    } else {
        qDebug("Error while saving the picture");
    }
}*/

