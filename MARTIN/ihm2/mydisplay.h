#ifndef MYDISPLAY_H
#define MYDISPLAY_H
#include "librairie.h"

//#define API OPEN_CV
#define API	QT

class MyDisplay
{
public:
    MyDisplay();
    ~MyDisplay();

#if API == OPENCV
    void camera();
    void camera_NVG();
    void camera_NVG_stretched();
    void camera_negatif();
    void face_tracking();
    void human_tracking();
#endif // OPENCV



    //void camera_binary();
    void negatif(IplImage* image);
    void stretch_histogram_NVG(IplImage* image);
    void detect_faces(CvHaarClassifierCascade *cascade, CvMemStorage *storage);
    void detect_human(CvHaarClassifierCascade *cascade, CvMemStorage *storage);
    //void threshold_callback(int valeur);

#if API == QT
    IplImage* image_camera(CvCapture* capture);
    IplImage* image_camera_NVG(CvCapture* capture);
    IplImage* image_camera_NVG_stretched(CvCapture* capture);
    IplImage* image_camera_negatif(CvCapture* capture);
    IplImage* image_face_tracking(CvCapture* capture);
    IplImage* image_human_tracking(CvCapture* capture);
#endif // QT




private:
    IplImage* frame = NULL;
    IplImage* img_nvg = NULL;
    IplImage* img_bin = NULL;
    CvCapture *capture = NULL;
    int column = 0;
    int lines = 0;
    int key = 0;
};
#endif
