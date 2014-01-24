#include "battery.h"
#include <QFile>
#include <QTextStream>

battery::battery(QWidget *parent) :
    QMainWindow(parent)
{
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 10, 85, 20);

    startTimer(200);
}

void battery::timerEvent(QTimerEvent *event)
{
    QFile fichier("/tmp/LOG");
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
    if(ligne.toInt() >= 50)
        setStyleSheet("QProgressBar::chunk{background-color:green}");
    if(ligne.toInt() < 50)
        setStyleSheet("QProgressBar::chunk{background-color:orange}");
    if(ligne.toInt() < 20 )
        setStyleSheet("QProgressBar::chunk{background-color:red}");


}
