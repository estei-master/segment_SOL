#include "mydisplay.h"
#include "librairie.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <assert.h>

//threshold parameters
int threshold_select;
int inversion;

MyDisplay::MyDisplay()
{
}


MyDisplay::~MyDisplay()
{
}

void MyDisplay::camera()
{
    IplImage* frame = NULL;
    CvCapture *capture = cvCreateCameraCapture(CV_CAP_ANY);
    while (1){
        frame = cvQueryFrame(capture);
        cvShowImage("test", frame);
        int key = cvWaitKey(1);
        if (key == 'q')
        {
            break;
        }
        else {
            //nothing to do
        }
    }
    cvReleaseCapture(&capture);
}

void MyDisplay::camera_NVG()
{
    capture = cvCreateCameraCapture(CV_CAP_ANY);
    while (1){
        frame = cvQueryFrame(capture);
        img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);

        //conversion en niveau de gris
        cvConvertImage(frame, img_nvg, 0);

        cvShowImage("test", img_nvg);
        int key = cvWaitKey(1);
        if (key == 'q')
        {
            break;
        }
        else {
            //nothing to do
        }
    }
    cvReleaseCapture(&capture);
}

void MyDisplay::stretch_histogram_NVG(IplImage* image)
{
    //if the picture is in NVG
    if (image->nChannels != 1)
    {
        return;
    }
    else {
        //nothing to do
    }

    // fix the max and min for the mathematic function
    int pix_min = 255;
    int pix_max = 0;

    CvScalar scalaire;

    //we search pix_min and pix_max
    for (column = 0; column < image->width; column++)
    {
        for (lines = 0; lines < image->height; lines++)
        {
            //we take the pixel or scalaire
            scalaire = cvGet2D(image, lines, column);

            //we search extremums
            if (scalaire.val[0] < pix_min)
            {
                pix_min = (int)scalaire.val[0];
            }
            else if (scalaire.val[0] > pix_max)
            {
                pix_max = (int)scalaire.val[0];
            }
            else {
                //nothing to do
            }
        }
    }

    //we have max and min, we normalize
    for (column = 0; column < image->width; column++)
    {
        for (lines = 0; lines < image->height; lines++)
        {
            //we take the pixel or scalaire
            scalaire = cvGet2D(image, lines, column);

            //Normalize with mathematic equation
            scalaire.val[0] = 255 * (scalaire.val[0] - pix_min);
            scalaire.val[0] = scalaire.val[0] / (pix_max - pix_min);

            //we replace the pixel in the picture
            cvSet2D(image, lines, column, scalaire);
        }
    }
}

void MyDisplay::camera_NVG_stretched()
{
    capture = cvCreateCameraCapture(CV_CAP_ANY);
    while (1){
        frame = cvQueryFrame(capture);
        img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);

        //conversion en niveau de gris
        cvConvertImage(frame, img_nvg, 0);

        stretch_histogram_NVG(img_nvg);

        cvShowImage("test", img_nvg);
        int key = cvWaitKey(1);
        if (key == 'q')
        {
            break;
        }
        else {
            //nothing to do
        }
    }
    cvReleaseCapture(&capture);
}

void MyDisplay::negatif(IplImage* image)
{
    CvScalar scalar_return;

    for (column = 0; column < image->width; column++)
    {
        for (lines = 0; lines < image->height; lines++)
        {
            scalar_return = cvGet2D(image, lines, column);
            scalar_return.val[0] = 255 - scalar_return.val[0];
            cvSet2D(image, lines, column, scalar_return);
        }
    }
}

void MyDisplay::camera_negatif()
{
    capture = cvCreateCameraCapture(CV_CAP_ANY);
    while (1){
        frame = cvQueryFrame(capture);
        img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);

        //conversion en niveau de gris
        cvConvertImage(frame, img_nvg, 0);

        stretch_histogram_NVG(img_nvg);
        negatif(img_nvg);

        //frame = negatif(frame);
        cvShowImage("test", img_nvg);
        int key = cvWaitKey(1);
        if (key == 'q')
        {
            break;
        }
        else {
            //nothing to do
        }
    }
    cvReleaseCapture(&capture);

}

/*
void MyDisplay::detect_faces(CvHaarClassifierCascade *cascade, CvMemStorage *storage)
{
    int i;

    //we receive objects sequences with good criterias and 1.1 is the scale factor, 3 is the minimum neighbours, cvSize is the minimum size of the object
    CvSeq *faces = cvHaarDetectObjects(frame, cascade, storage, 1.1, 3, 0, cvSize(40, 40));

    //we draw rectangle on the objects
    for (i = 0; i < (faces ? faces->total : 0); i++)
    {
        CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
        cvRectangle(frame, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(255, 0, 0), 1, 8, 0);
    }
}

void MyDisplay::face_tracking()
{
    //variable for the face tracking
    CvHaarClassifierCascade *cascade = NULL;
    CvMemStorage *storage = NULL;

    cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_alt.xml", 0, 0, 0);

    //we start the capture
    capture = cvCreateCameraCapture(0);

    //initialize the storage memory
    storage = cvCreateMemStorage(0);

    //we start the window
    cvNamedWindow("Détection de visages", 1);

    while (key != 'q')
    {
        frame = cvQueryFrame(capture);
        detect_faces(cascade, storage);
        cvShowImage("Détection de visages", frame);
        key = cvWaitKey(10);
    }

    //we release the memory
    cvReleaseCapture(&capture);
    cvDestroyWindow("Détection de visages");
    cvReleaseHaarClassifierCascade(&cascade);
    cvReleaseMemStorage(&storage);
}

void MyDisplay::detect_human(CvHaarClassifierCascade *cascade, CvMemStorage *storage)
{
    int i;

    //we receive objects sequences with good criterias and 1.1 is the scale factor, 3 is the minimum neighbours, cvSize is the minimum size of the object
    CvSeq *faces = cvHaarDetectObjects(frame, cascade, storage, 1.1, 3, 0, cvSize(20, 60));

    //we draw rectangle on the objects
    for (i = 0; i < (faces ? faces->total : 0); i++)
    {
        CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
        cvRectangle(frame, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(255, 0, 0), 1, 8, 0);
    }
}

void MyDisplay::human_tracking()
{
    //variable for the face tracking
    CvHaarClassifierCascade *cascade = NULL;
    CvMemStorage *storage = NULL;

    cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_fullbody.xml", 0, 0, 0);

    //we start the capture
    capture = cvCreateCameraCapture(0);

    //initialize the storage memory
    storage = cvCreateMemStorage(0);

    //we start the window
    cvNamedWindow("Détection de visages", 1);

    while (key != 'q')
    {
        frame = cvQueryFrame(capture);
        detect_human(cascade, storage);
        cvShowImage("Détection de visages", frame);
        key = cvWaitKey(10);
    }

    //we release the memory
    cvReleaseCapture(&capture);
    cvDestroyWindow("Détection de visages");
    cvReleaseHaarClassifierCascade(&cascade);
    cvReleaseMemStorage(&storage);
}

*/

//void MyDisplay::camera_binary()
//{
//	frame = cvLoadImage("lena.jpg");
//	img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);
//	img_bin = cvCloneImage(img_nvg);
//	cvConvertImage(frame, img_nvg, 0);
//	cvNamedWindow("binarisation", CV_WINDOW_AUTOSIZE);
//	threshold_select = 127;
//	inversion = 0;
//	cvThreshold(img_nvg, img_bin, threshold_select, 255, CV_THRESH_BINARY);
//	cvShowImage("binarisation", img_bin);
//	cvCreateTrackbar("Seuil", "binarisation", &threshold_select, 255, threshold_callback);
//	cvCreateTrackbar("Inversion", "binarisation", &inversion, 1, threshold_callback);
//	cvWaitKey(0);
//	cvDestroyAllWindows();
//	cvReleaseImage(&img_nvg);
//	cvReleaseImage(&img_bin);
//}
//
////fonction to threshold the picture
//void MyDisplay::threshold_callback(int valeur)
//{
//	//variable to verify if inversion is active
//	int manipulate;
//
//	//we chose the mode
//	if (inversion == 0)
//	{
//		manipulate = CV_THRESH_BINARY;
//	}
//	else{
//		manipulate = CV_THRESH_BINARY_INV;
//	}
//
//	//modify the threshold
//	cvThreshold(img_nvg, img_bin, threshold_select, 255, manipulate);
//
//
//	//we do changes in the same window
//	cvShowImage("binarisation", img_bin);
//
//	//morphology_callback(valeur);
//}


IplImage* MyDisplay::image_camera(CvCapture* capture)
{
    IplImage* frame = NULL;
    frame = cvQueryFrame(capture);
    return frame;
}

IplImage* MyDisplay::image_camera_NVG(CvCapture* capture)
{
    frame = cvQueryFrame(capture);
    img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);

    //conversion en niveau de gris
    cvConvertImage(frame, img_nvg, 0);
    return frame;
}

IplImage* MyDisplay::image_camera_NVG_stretched(CvCapture* capture)
{

    frame = cvQueryFrame(capture);
    img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);

    //conversion en niveau de gris
    cvConvertImage(frame, img_nvg, 0);

    stretch_histogram_NVG(img_nvg);

    return img_nvg;
}

IplImage* MyDisplay::image_camera_negatif(CvCapture* capture)
{

    frame = cvQueryFrame(capture);
    img_nvg = cvCreateImage(cvGetSize(frame), frame->depth, 1);

    //conversion en niveau de gris
    cvConvertImage(frame, img_nvg, 0);

    stretch_histogram_NVG(img_nvg);
    negatif(img_nvg);
    return img_nvg;
}

/*
IplImage* MyDisplay::image_face_tracking(CvCapture* capture)
{
    //variable for the face tracking
    CvHaarClassifierCascade *cascade = NULL;
    CvMemStorage *storage = NULL;

    cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_alt.xml", 0, 0, 0);

    //initialize the storage memory
    storage = cvCreateMemStorage(0);

    frame = cvQueryFrame(capture);
    detect_faces(cascade, storage);
}

IplImage* MyDisplay::image_human_tracking(CvCapture* capture)
{
    //variable for the face tracking
    CvHaarClassifierCascade *cascade = NULL;
    CvMemStorage *storage = NULL;

    cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_fullbody.xml", 0, 0, 0);

    //initialize the storage memory
    storage = cvCreateMemStorage(0);


    frame = cvQueryFrame(capture);
    detect_human(cascade, storage);
}
*/
