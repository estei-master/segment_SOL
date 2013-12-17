#include "mainwindow.h"
#include "camerawidget.h"
#include <QApplication>
#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
#include <assert.h>
#include "ui_mainwindow.h"




int main(int argc, char **argv) {

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    int retval = app.exec();
    return retval;
}
