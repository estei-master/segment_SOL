#ifndef UART_H
#define UART_H
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <termios.h>

#define param_UART_FILE           (const char*)"/dev/ttyS0"
#define param_ENTRE_CONFIG        (char*)"+++"
#define param_QUITE_CONFIG        (char*)"ATCN"
#define param_ADRESSE_DEST_H      (char*)"ATDH" //Controle commenté
#define param_ADRESSE_DEST_L      (char*)"ATDL"
#define param_ADRESSE_EMET_H      (char*)"ATSH"
#define param_ADRESSE_EMET_L      (char*)"ATSL"
#define HISTORY_DEST_H            (const char*)"1234"
#define HISTORY_DEST_L            (const char*)"1234"

class Uart
{
public:
    Uart();
    ~Uart();
    //int Serial_SendChar(int *fd, char ch);

    bool bInitialize;
protected:
    bool Serial_Close();
    bool Serial_Open(const char *serial_Name, speed_t baudrate);
    int Serial_Read(char *buff, int len);
    int Serial_Send(char *string, int len);

    char cSendBuff[12];
    char cRecevBuff[12];
private:

    int  fd;
};

#endif
