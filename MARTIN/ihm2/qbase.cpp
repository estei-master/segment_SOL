#include "qbase.h"
#include "stdio.h"

#include <QTime>
#include <fstream>

QBase::QBase(QObject *parent) :
    QThread(parent)
{
    Horizon = new qAttitudeIndicator();
    NunchuckDirection = new Nunchuck(PARAM_DIRECTION);
    NunchuckAltitude = new Nunchuck(PARAM_ALTITUDE);
    ModuleZigBee = new ZigBee();


    if(!NunchuckAltitude->bInitialize) {
        MsgBox.setText("Echec de connexion : Commande Altitude\t\n               (Veuillez la reconnecter)");
        MsgBox.exec();
        NunchuckAltitude->bInitialize = NunchuckAltitude->Initialize(PARAM_ALTITUDE);

        if(!NunchuckAltitude->bInitialize) {
            MsgBox.setText("Echec de connexion : Commande Altitude\t\n               (Abandon)");
            MsgBox.exec();
        }
    }

    if(!NunchuckDirection->bInitialize) {
        MsgBox.setText("Echec de connexion : Commande Direction\t\n               (Veuillez la reconnecter)");
        MsgBox.exec();
        NunchuckDirection->bInitialize = NunchuckDirection->Initialize(PARAM_DIRECTION);

        if(!NunchuckDirection->bInitialize) {
            MsgBox.setText("Echec de connexion : Commande Direction\t\n               (Abandon)");
            MsgBox.exec();
        }
    }

    if(!ModuleZigBee->bInitialize) {
        MsgBox.setText("Echec de connexion : Module de Communication\t\n             (Abandon)");
        MsgBox.exec();
    }
}

void QBase::run()
{
    //Doit attendre l'information de démarrage du drone : puis emettre toutes les 500ms
    //Pourrait émettre toutes les 500ms, 250ms avant que le drone écoute?. (voir fonction boquante read)
    //FONCTION DE SINCRONISATION !!
    QTime time;
    QString Qtmp;
    std::ofstream    f("/tmp/LogZigBee", std::ios_base::app);

    time.start();

    while (1) {

        /* Recupère les données des commandes */
        if(NunchuckDirection->bInitialize)
            NunchuckDirection->ReadCommand();

        if(NunchuckDirection->bButtonZ) {

        }

        if(NunchuckDirection->bButtonC) {

        }

        /* Mise à jour des commandes de vol et de l'Horizon(pour test) */
        switch (NunchuckDirection->cJoystickX) {
        case JCENTRE:
            Horizon->roll = 0.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransY = 0;    //Vérifier avec Nabil!!!
            break;
        case JDROITE:
            Horizon->roll = -15.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransY = 1;    //Vérifier avec Nabil!!!
            break;
        case JGAUCHE:
            Horizon->roll = 15.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransY = -1;    //Vérifier avec Nabil!!!
            break;
        case JDROITE_MAX:
            Horizon->roll = -30.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransY = 2;    //Vérifier avec Nabil!!!
            break;
        case JGAUCHE_MAX:
            Horizon->roll = 30.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransY = -2;    //Vérifier avec Nabil!!!
            break;
        default:
            Horizon->roll = 90.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransY = 0;    //Vérifier avec Nabil!!!
            break;
        }

        switch (NunchuckDirection->cJoystickY) {
        case JCENTRE:
            Horizon->pitch = 0.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransX = 0;    //Vérifier avec Nabil!!!
            break;
        case JHAUT:
            Horizon->pitch = 10.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransX = -1;    //Vérifier avec Nabil!!!
            break;
        case JBAS:
            Horizon->pitch = -10.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransX = 1;    //Vérifier avec Nabil!!!
            break;
        case JHAUT_MAX:
            Horizon->pitch = 20.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransX = -2;    //Vérifier avec Nabil!!!
            break;
        case JBAS_MAX:
            Horizon->pitch = -20.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransX = 2;    //Vérifier avec Nabil!!!
            break;
        default:
            Horizon->pitch = 90.0;
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransX = 0;    //Vérifier avec Nabil!!!
            break;
        }
        Horizon->doHorizon();

        switch (NunchuckAltitude->cJoystickX) {
        case JCENTRE:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cRotZ = 0;    //Vérifier avec Nabil!!!
            break;
        case JDROITE:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cRotZ = 1;    //Vérifier avec Nabil!!!
            break;
        case JGAUCHE:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cRotZ = -1;    //Vérifier avec Nabil!!!
            break;
        case JDROITE_MAX:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cRotZ = 2;    //Vérifier avec Nabil!!!
            break;
        case JGAUCHE_MAX:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cRotZ = -2;    //Vérifier avec Nabil!!!
            break;
        default:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cRotZ = 0;    //Vérifier avec Nabil!!!
            break;
        }

        switch (NunchuckAltitude->cJoystickY) {
        case JCENTRE:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransZ = 0;    //Vérifier avec Nabil!!!
            break;
        case JHAUT:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransZ = 1;    //Vérifier avec Nabil!!!
            break;
        case JBAS:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransZ = -1;    //Vérifier avec Nabil!!!
            break;
        case JHAUT_MAX:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransZ = 2;    //Vérifier avec Nabil!!!
            break;
        case JBAS_MAX:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransZ = -2;    //Vérifier avec Nabil!!!
            break;
        default:
            /* Mise à jour des commandes de vol */
            ModuleZigBee->st_CommandDrone.cTransZ = 0;    //Vérifier avec Nabil!!!
            break;
        }

        //if(SET_CONFIG_TO_DRONE) {
            //OPEN_WINDOW_CONFIG AND SEND CONFIG
            //ModuleZigBee->SendConfig();
        //}
        //else {
            Qtmp.sprintf("Time before send : %d\n",time.elapsed());
            f.write(Qtmp.toStdString().c_str(), Qtmp.length());
            ModuleZigBee->SendCommand();

        //}
        Qtmp.sprintf("Time before receive : %d\n",time.elapsed());
        f.write(Qtmp.toStdString().c_str(), Qtmp.length());
        //printf("%s\n",Qtmp.toStdString().c_str());
        ModuleZigBee->receive();
        Qtmp.sprintf("Time after receive : %d\n",time.elapsed());
        f.write(Qtmp.toStdString().c_str(), Qtmp.length());

        usleep(50000);//Pour ralentir le programme...
        time.restart();

    }
}

void QBase::terminate()
{
    delete ModuleZigBee;
    delete NunchuckDirection;
    delete NunchuckAltitude;
    delete Horizon;
}

void QBase::enableCamera(bool bEnable)
{

}
