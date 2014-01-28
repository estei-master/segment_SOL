#include "batterie.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>

batterie::batterie(QWidget *parent) :
    QMainWindow(parent)
{
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 10, 190, 40);
    startTimer(200);
}

void batterie::timerEvent(QTimerEvent *event)
{
    QFile fichier("/home/pierre/Documents/batterie/niveauBatterie.txt");
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

    progressBar->setValue(ligne.toInt());

    if(ligne.toInt() >= 90)
        setStyleSheet("QProgressBar::chunk{background-color:green}");
    else if(ligne.toInt() >= 50 && ligne.toInt() < 90)
        setStyleSheet("QProgressBar::chunk{background-color:yellow}");
    else if(ligne.toInt() >= 20 && ligne.toInt() < 50)
        setStyleSheet("QProgressBar::chunk{background-color:orange}");
    else if(ligne.toInt() < 20)
        setStyleSheet("QProgressBar::chunk{background-color:red}");
}
