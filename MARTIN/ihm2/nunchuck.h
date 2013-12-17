#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

/*  Constantes port I2C */

#define PARAM_DEVICENAME_COMMANDE    "/dev/i2c-X";
#define PARAM_DRONE                  '1'
#define PARAM_CAMERA                 '2'

#define JCENTRE                            0
#define JDROITE                            1
#define JGAUCHE                            2
#define JHAUT                              4
#define JBAS                               8
#define JDROITE_MAX                       16
#define JGAUCHE_MAX                       32
#define JHAUT_MAX                         64
#define JBAS_MAX                          127


class Nunchuck
{
public:
    Nunchuck(char cTypeNunk);
    ~Nunchuck();

    void    ReadCommand();

    bool    bInitialize;

    /*  Etat commandes  */

    int              iValueJoystickX;
    int              iValueJoystickY;
    bool             bButtonZ;
    bool             bButtonC;
    char             cJoystickX;
    char             cJoystickY;

private:
    void DecodeBufferIn();

    /*  Initialisation  */

    bool    Initialize(char cTypeNunk);

    /*   Variable : Port I2C  */

    int     fDevice;
    char    cBufferIn[6];
    char    cBufferOut[2];
    int     iSizeBuffer;


    int    iData[6];
};

#endif // NUNCHUCK_H
