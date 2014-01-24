#include "nunchuck.h"

Nunchuck::Nunchuck(char cTypeNunk)
{
    /*   Initialisation du nunchuck
         "bInitialize" est égale à VRAI si l'objet est correctement initialisé   */

    bInitialize = Initialize(cTypeNunk);

    /*  Lecture des informations commandes  :   Passe "bInitialize" à FAUX en cas d'échec   */
    if(bInitialize){
        ReadCommand();
    }
    else {

    }
}

Nunchuck::~Nunchuck()
{
    close(fDevice);
}

bool Nunchuck::Initialize(char cTypeNunk)
{
    int iAddress_I2C = 0x52;

    char cDeviceName[] = PARAM_DEVICENAME_COMMANDE;

    cDeviceName[sizeof(cDeviceName)-2] = cTypeNunk;

    /*  Initialisation des variables et  périphériques (Joystick, Accéléromètre)   */

    bButtonC = false;
    bButtonZ = false;
    cJoystickX = -1;
    cJoystickY = -1;
    iValueJoystickY = -1;
    iValueJoystickX = -1;

    if ((fDevice = open(cDeviceName, O_RDWR)) < 0) {
    /*   Si le périphérique est inéxistant on retourne FAUX   */
            return false;
    }
    else {

    }

    if(ioctl(fDevice, I2C_SLAVE, iAddress_I2C) < 0) {
    /*   Si le nunchuck ne répond pas on retourne FAUX   */
        close(fDevice);
        return false;
    }
    else {

    }

    /*  Si le nunchuck est reconnue, on l'initialise    */

    iSizeBuffer = 0;

    cBufferOut[iSizeBuffer++] = 0xF0;
    cBufferOut[iSizeBuffer++] = 0x55;


    if(write(fDevice, cBufferOut, iSizeBuffer) != iSizeBuffer)	{
    /*   Si il y a erreur d'écriture, on retourne FAUX   */
        close(fDevice);
        return false;
    }
    else {

    }

    iSizeBuffer = 0;

    cBufferOut[iSizeBuffer++] = 0xFB;
    cBufferOut[iSizeBuffer++] = 0x00;


    if(write(fDevice, cBufferOut, iSizeBuffer) != iSizeBuffer)	{
    /*   Si il y a erreur d'écriture, on retourne FAUX   */
        close(fDevice);
        return false;
    }
    else {

    }

    /*  Nunchuck Initialisé est calibré
        On retourne VRAI  */

    return true;
}

void Nunchuck::ReadCommand() {

    iSizeBuffer = 1;

    /*  Ordre de lecture des informations des capteurs   */
    cBufferOut[0] = 0x00;

    if(write(fDevice, cBufferOut, iSizeBuffer) != iSizeBuffer)	{
    /*   Si il y a erreur d'écriture, demande une réinitialisation   */
       bInitialize = false;
       close(fDevice);
       return;
    }
    else {

    }

    iSizeBuffer = 6;

    if(read(fDevice, cBufferIn, iSizeBuffer) != iSizeBuffer)	{
    /*   Si il y a erreur de lecture, demande une réinitialisation   */
       bInitialize = false;
       close(fDevice);
       return;
    }
    else {

    }

    DecodeBufferIn();
}

void Nunchuck::DecodeBufferIn() {

    /*  Données recu sans cryptage  */

    for(int i = 0 ; i < 6 ; i++) {
        //cBufferIn[i] ^= 0x17;
        iData[i]      = (int)cBufferIn[i];
        //iData[i]     += 0x17;
    }


    if(bInitialize) {

        //FILE *file = fopen("/tmp/nunchuckLog", "a");

        /*  Test Bouttons : Si on appui sur le bouton Z, le bouton C est indiqué comme appuyé :
         *
         *Solution -> on ne test pas le bouton C si Z est appuyé    */

        if(iData[5] & 0x01) {                           //Si Boutton Z relaché

            bButtonZ = false;

            iData[5] >>= 1;

            if( iData[5] & 0x01 ) {                     //Si Boutton C relaché
                bButtonC = false;
            }
            else {                                      //Si Boutton C appuyé
                bButtonC = true;
            }
        }                                               //Si Boutton Z appuyé
        else {
            bButtonZ = true;
        }

        /*  Test Joystick axe horizontal (X)    */

        iValueJoystickX = iData[0];

        if(iValueJoystickX > 175) {    //Si Joystick à Droite
            cJoystickX = JDROITE;

            if(iValueJoystickX > 225)
                cJoystickX = JDROITE_MAX;
        }
        else if(iData[0] < 95) {           //Si Joystick à Gauche
            cJoystickX = JGAUCHE;

            if(iValueJoystickX < 50)
                cJoystickX = JGAUCHE_MAX;
        }
        else {                              //Si Joystick au Centre
            cJoystickX = JCENTRE;
        }


        /*  Test Joystick axe vertical (Y)    */

        iValueJoystickY = iData[1];

        if(iData[1] > 175) {    //Si Joystick en Haut
            cJoystickY = JHAUT;

            if(iData[1] > 225)
                cJoystickY = JHAUT_MAX;
        }
        else if(iData[1] < 95) {      //Si Joystick en Bas
            cJoystickY = JBAS;

            if(iData[1] < 50)
                cJoystickY = JBAS_MAX;
        }
        else {                         //Si Joystick au Centre
            cJoystickY = JCENTRE;
        }

        /*  Accéléromètre
            cBufferIn[2] <<= 2;
            cBufferIn[2] |= ((cBufferIn[5] >> 2) & 0x03);
            printf("X-axis: %d\n", cBufferIn[2]);

            cBufferIn[3] <<= 2;
            cBufferIn[3] |= ((cBufferIn[5] >> 4) & 0x03);
            printf("Y-axis: %d\n", cBufferIn[3]);

            cBufferIn[4] <<= 2;
            cBufferIn[4] |= ((cBufferIn[5] >> 6) & 0x03);
            printf("Z-axis: %d\n", cBufferIn[4]);   */


        //fclose(file);
    }



}
