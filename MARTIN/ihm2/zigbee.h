#ifndef ZIGBEE_H
#define ZIGBEE_H

#include "uart.h"
#include "typdefUart.h"
#include <QMessageBox>

/* Envoit une trame toutes les 500ms
 *
 * Doit recevoir une trame avant les 500ms suivantes
 */

class ZigBee : public Uart
{
public:
    explicit ZigBee();
    void receive();
    void SendCommand();
    void SendConfig();

    struct droneState    st_DroneState;
    struct droneConfig   st_droneConfig;
    struct flightCommand st_CommandDrone;
    struct droneIMUData  st_DataIMU;
    struct droneGPSData  st_DataGPS;
private:
    bool ConfigZigBee();
    void decodeTrame();
    void GetConfigDrone(uint32_t *param);
    void GetDroneError(droneError *param);
    void GetDroneState(droneFltState *param);
    void GetDroneTime(portTickType *param);

    QMessageBox         MsgBox;
    struct tramZigbee   st_BufferIn;
    struct tramZigbee   st_BufferOut;
    int                 iIndexBufferIn;
    int                 iIndexBufferOut;
    bool                bReadyToSend;
};

#endif // ZIGBEE_H
