#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>
#include <QDebug>
//#include <opencv/cv.h>
#include </usr/local/include/opencv2/opencv.hpp>

/**
* \file camerawidget.h
* \brief Fichier d'inclusion des librairies nécessaires au widget.
* \author Martin PRADEAU
* \version Version finale
* \date Janvier 2014
*/

class CameraWidget : public QWidget
{

public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget(void);
    QPixmap toPixmap(IplImage *);
    void putFrame(IplImage *);

private:
    QLabel *m_imageLabel;
    QVBoxLayout *m_layout;
    QImage m_image;

};

#endif
