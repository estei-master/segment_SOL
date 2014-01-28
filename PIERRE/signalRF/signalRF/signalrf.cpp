#include "signalrf.h"
#include <QFile>
#include <QTextStream>

signalRF::signalRF(QWidget *parent) :
    QMainWindow(parent)
{
    progressBar1 = new QProgressBar(this);
    progressBar1->setGeometry(10, 10, 40, 110);
    progressBar1->setOrientation(Qt::Vertical);
    progressBar1->setValue(0);
    progressBar1->move(120, 0);
    progressBar1->setTextVisible(false);

    progressBar2 = new QProgressBar(this);
    progressBar2->setGeometry(10, 10, 40, 80);
    progressBar2->setOrientation(Qt::Vertical);
    progressBar2->setValue(0);
    progressBar2->move(80, 30);
    progressBar2->setTextVisible(false);

    progressBar3 = new QProgressBar(this);
    progressBar3->setGeometry(10, 10, 40, 50);
    progressBar3->setOrientation(Qt::Vertical);
    progressBar3->setValue(0);
    progressBar3->move(40, 60);
    progressBar3->setTextVisible(false);

    progressBar4 = new QProgressBar(this);
    progressBar4->setGeometry(10, 10, 40, 20);
    progressBar4->setOrientation(Qt::Vertical);
    progressBar4->setValue(0);
    progressBar4->move(0, 90);
    progressBar4->setTextVisible(false);

    startTimer(200);
}

void signalRF::timerEvent(QTimerEvent *event)
{
    QFile fichier("/home/pierre/Documents/signalRF/signalRF.txt");
    QString ligne;
    QTextStream flux(&fichier);

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!flux.atEnd())
        {
            ligne = fichier.readLine();
        }
        fichier.close();
    }
    else
        ligne = "Impossible d'ouvrir le fichier !";

    if(ligne.toInt() == 0)
    {
        progressBar4->setValue(0);
        progressBar3->setValue(0);
        progressBar2->setValue(0);
        progressBar1->setValue(0);
    }
    else if(ligne.toInt() == 1)
    {
        progressBar4->setValue(100);
        progressBar3->setValue(0);
        progressBar2->setValue(0);
        progressBar1->setValue(0);
    }
    else if(ligne.toInt() == 2)
    {
        progressBar4->setValue(100);
        progressBar3->setValue(100);
        progressBar2->setValue(0);
        progressBar1->setValue(0);
    }
    else if(ligne.toInt() == 3)
    {
        progressBar4->setValue(100);
        progressBar3->setValue(100);
        progressBar2->setValue(100);
        progressBar1->setValue(0);
    }
    else if(ligne.toInt() == 4)
    {
        progressBar4->setValue(100);
        progressBar3->setValue(100);
        progressBar2->setValue(100);
        progressBar1->setValue(100);
    }
}
