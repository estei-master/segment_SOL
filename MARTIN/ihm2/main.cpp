#include <QApplication>
#include "mainwindow.h"

/*  Modifs : Bouton start/stop Video actif
 *
 */

/**
*@mainpage projet SEGMENT SOL : https://github.com/estei-master/segment_SOL/
* \b Chef \b de \b Projet :
*               - TEXIER Pierre-jean
*
* \b Développeurs :
*               - PRADEAU Martin
*               - POUCH Pierre
*               - L'HUILLIER Guillaume
*               - OUKRAT Rémi
*
* \b Users \b Stories :
*1.	En tant qu'utilisateur, je souhaite que l'Interface Homme Machine (IHM) permette d'afficher le flux vidéo pour permettre un vol immersif.
*Le test se fera tout d'abord sur PC puisque Qt permet la portabilité de ses applications.
*
*2.	En tant qu'utilisateur, je souhaite que l'IHM affiche la position ainsi que les coordonnées GPS afin de pouvoir localiser le drone en temps réel.
*Le test s'effectuera directement sur cible puisque le drone n'a pas besoin de voler pour vérifier ces informations.
*
*3.	En tant qu'utilisateur, je souhaite que l'IHM intègre un témoin de batterie afin d'éviter une perte de contrôle du drone.
*Le test s'effectuera via un terminal avec la commande :
*cat /sys/class/power_supply/battery/capacity
*
*4.	En tant qu'utilisateur, je souhaite que l'IHM dispose d'un arrêt d'urgence en cas de problème afin d'éviter un risque de casses matérielles.
*
*5.	En tant qu'utilisateur, je souhaite que l'IHM affiche la durée du vol en temps réel via un chronomètre afin de vérifier l'autonomie du vol. Le test s'effectuera directement sur cible.
*
*6.	En tant qu'utilisateur, je souhaite que l'IHM affiche les conditions météorologiques en temps réel (vitesse du vent, température) afin d'éviter les risques de casses.
*
*7.	En tant qu'utilisateur, je souhaite que l'IHM dispose de deux onglets pour différencier vol immersif et vol à vue. Test sur PC puis sur cible.
*
*8.	En tant qu'utilisateur, je souhaite que l'IHM permette la visualisation des accélérations sur les axes X, Y, Z.
*
*9.	En tant que programmeur, je souhaite que le code qui va générer l'IHM soit formalisé afin de faciliter le développement et le déverminage.
*
*10. En tant que programmeur, je souhaite que l'IHM dispose d'un manuel utilisateur afin que tout le monde puisse piloter le drone.
*
*\b Prototype \b de \b l'IHM :
*\image html IHM.png
*\brief
*\image html IHM2.png
*/

/**
* \file main.cpp
* \brief Ficher main qui permet d'afficher la MainWindow.
* \author Martin PRADEAU
* \version Version finale
* \date Janvier 2014
*/

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    int retval = app.exec();
    return retval;
}
