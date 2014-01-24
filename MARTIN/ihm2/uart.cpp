
//#include <termios.h>
#include "uart.h"

Uart::Uart()
{
    tcflush(fd, TCIOFLUSH);
    bInitialize = Serial_Open(param_UART_FILE, B9600);
}

Uart::~Uart()
{
    Serial_Close();
}

bool Uart::Serial_Open(const char *serial_Name, speed_t baudrate)
{
    struct termios serCfg;

	memset(&serCfg, 0, sizeof(serCfg));

    if((fd = open(serial_Name, O_RDWR | O_NOCTTY | O_NDELAY )) < 0) {
        printf("Failed to open serial port");
        return false;
	}
    else if(tcgetattr(fd, &serCfg) != 0) {
            printf("Failed to get configuration");
            return false;
    }

	cfsetispeed(&serCfg, baudrate);
	cfsetospeed(&serCfg, baudrate);
	cfmakeraw(&serCfg);

    if(tcsetattr(fd, TCSANOW, &serCfg) != 0) {
        printf("Failed to set configuration");
        return false;
	}
    return true;
}
int Uart::Serial_Send(char *string, int len)
{
    if(bInitialize) {
        return write(fd, string,len);
    }
    else {
        return -1;
    }
}

int Uart::Serial_Read(char *buff, int len)
{
    if(bInitialize) {
        return read(fd, buff, len);
    }
    else {
        return -1;
    }
}

bool Uart::Serial_Close()
{
        if(close (fd) < 0)
        {
            return false;
		}
		else
            return true;
}
/*
int Serial_SendChar(int *fd, char ch)
{

	int bytes_sent;
	char a[1];
	a[0] = ch;
	bytes_sent = write(*fd, a, 1);
	if(bytes_sent < 0)
	{
        printf("Failed to send data");
        return -1;
	}
	else
		return 0;
}
*/
