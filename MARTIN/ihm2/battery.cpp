#include "battery.h"
#include <QFile>
#include <QTextStream>

/**
* \file battery.cpp
* \brief Ce programme permet l'affichage des états des batteries du drone et du segment sol grâce à des QProgressBar.
* \author Martin PRADEAU / Pierre POUCH
* \version Version finale
* \date Janvier 2014
*/

/**
 * \brief    Constructeur
 * \details  Permet la déclaration et la définition de de la taille de la progressBar
 * \param    QWidget *parent
 */

battery::battery(QWidget *parent) :
    QMainWindow(parent)
{
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 10, 85, 20);
    startTimer(200);
}

/**
 * \brief    Timer
 * \details  Permet le rafraichissement des valeurs pour l'affichage de l'état des batteries du drone et de la base.
 * \param    QTimerEvent *event
 */

void battery::timerEvent(QTimerEvent *event)
{
    /*QFile fichier("/home/estei/projet/fonctionnel/GPS/niveauBatterie.txt");*/                                              /* Récupère la valeur contenue dans le répertoire /temp/LOG pour la batterie de la base */
    /* POUR L'INTEGRATION */
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
    progressBar->setValue(ligne.toInt());                                   /* Fixe la valeur de la progressBar avec la valeur récupérée */
    if(ligne.toInt() >= 50)                                                 /* Si la valeur est supérieure ou égale à 50%, elle est de couleur verte */
        setStyleSheet("QProgressBar::chunk{background-color:green}");
    if(ligne.toInt() < 50)                                                  /* Si la valeur est inférieure à 50%, elle est de couleur orange */
        setStyleSheet("QProgressBar::chunk{background-color:orange}");
    if(ligne.toInt() < 20 )                                                 /* Si la valeur est inférieure à 20%, elle est de couleur rouge */
        setStyleSheet("QProgressBar::chunk{background-color:red}");


}
