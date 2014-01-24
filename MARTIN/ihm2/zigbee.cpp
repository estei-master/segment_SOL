#include "zigbee.h"

ZigBee::ZigBee()
{
    if(bInitialize) {

        bInitialize = ConfigZigBee();
        st_CommandDrone.cTransX = 0;
        st_CommandDrone.cTransY = 0;
        st_CommandDrone.cTransZ = 0;
        st_CommandDrone.cRotZ = 0;
        st_DataIMU.xUpdateTime = 0;
        st_DataGPS.xUpdateTime = 0;
        st_DroneState.eErrorMask = DRN_ERR_NONE;
        st_DroneState.eFltState = STATE_STARTING;
        bReadyToSend = false;
    }
    else {
        //Erreur d'init UART
    }
}

bool ZigBee::ConfigZigBee()
{
    Serial_Send(param_ENTRE_CONFIG, 3);

    Serial_Read(cRecevBuff, 2);      //Reçoit la confirmation

    if(cRecevBuff[0] != 'o' || cRecevBuff[1] != 'k') {
        return false;               //Si pas de confirmation, on quite
    }

    Serial_Send(param_ADRESSE_EMET_H, 4);             //Demande l'adresse de l'émetteur (MSBs)

    Serial_Read(cRecevBuff, 4);

    printf("adresse du module : %X %X %X %X ",cRecevBuff[0],cRecevBuff[1],cRecevBuff[2],cRecevBuff[3]);

    Serial_Send(param_ADRESSE_EMET_L, 4);             //Demande l'adresse de l'émetteur (LSBs)

    Serial_Read(cRecevBuff, 4);

    printf("%X %X %X %X\n",cRecevBuff[0],cRecevBuff[1],cRecevBuff[2],cRecevBuff[3]);

    Serial_Send(param_ADRESSE_DEST_H, 4);             //Demande l'adresse du recepteur (MSBs)

    Serial_Read(cRecevBuff, 4);

    if(strncmp(cRecevBuff, HISTORY_DEST_H, 4) != 0) {
//        return false;
        //Si différente, on tape dedans...
    }

    Serial_Send(param_ADRESSE_DEST_L, 4);             //Demande l'adresse du recepteur (LSBs)

    Serial_Read(cRecevBuff, 4);

    if(strncmp(cRecevBuff, HISTORY_DEST_H, 4) != 0) {
//        return false;
        //Si différente, on tape dedans...
    }

    Serial_Send(param_QUITE_CONFIG, 4);             //Quite la Config

    Serial_Read(cRecevBuff, 2);      //Reçoit la confirmation

    if(cRecevBuff[0] != 'o' || cRecevBuff[1] != 'k') {
        return false;               //Si pas de confirmation, on quite
    }

    return true;
}

void ZigBee::receive()
{
    if( (st_BufferIn.lengthData = (char)Serial_Read(st_BufferIn.Data, 95)) < 0) {// !! SA ASSURER QU'IL PEUT LIRE MOINS DE 95 OCTETS
        return;
    }

    if(st_BufferIn.lengthData == 0) {
        printf("HELLO\n");
        return;
    }
    bReadyToSend = true;
    decodeTrame();
}

void ZigBee::SendCommand()
{
    /* Envoit les infos Commandes au drone
     * Et demande de retourner son status
     */

    if(bReadyToSend) {

        iIndexBufferOut = 0;
        st_BufferOut.lengthData = 0;

        st_BufferOut.Data[iIndexBufferOut++] = (char)(PARAM_CMD_DRONE);
        st_BufferOut.Data[iIndexBufferOut++] = (char)(st_CommandDrone.cTransX);
        st_BufferOut.Data[iIndexBufferOut++] = (char)(st_CommandDrone.cTransY);
        st_BufferOut.Data[iIndexBufferOut++] = (char)(st_CommandDrone.cTransZ);
        st_BufferOut.Data[iIndexBufferOut++] = (char)(st_CommandDrone.cRotZ);
        st_BufferOut.lengthData++;

        st_BufferOut.Data[iIndexBufferOut++] = (char)(PARAM_CMD_ID);
        st_BufferOut.Data[iIndexBufferOut++] = (char)(CMD_GET_STATUS);
        st_BufferOut.lengthData++;

        char *tmp = (char*)malloc((size_t)(iIndexBufferOut+1));

        tmp[0] = st_BufferOut.lengthData;
        memcpy(&tmp[1],st_BufferOut.Data, iIndexBufferOut);

        if(Serial_Send(tmp, iIndexBufferOut+1 ) < 0) {
            //ERREUR D'ECRITURE!!
        }
        free(tmp);
        bReadyToSend = false;
    }
}

void ZigBee::SendConfig()
{
    bReadyToSend = false;
}

void ZigBee::decodeTrame()
{
    iIndexBufferIn = 0;

    for(int i = 0 ; i < st_BufferIn.lengthData ; i++) {

        switch(st_BufferIn.Data[iIndexBufferIn++]) {

        case PARAM_DRONE_CONFIG_ulMaxAngle:
            GetConfigDrone(&(st_droneConfig.ulMaxAngle));
            break;
        case PARAM_DRONE_CONFIG_ulTakeoffAltitude:
            GetConfigDrone(&(st_droneConfig.ulTakeoffAltitude));
            break;
        case PARAM_DRONE_CONFIG_ulMinAltitude:
            GetConfigDrone(&(st_droneConfig.ulMinAltitude));
            break;
        case PARAM_DRONE_CONFIG_ulCritBatteryLvl:
            GetConfigDrone(&(st_droneConfig.ulCritBatteryLvl));
            break;
        case PARAM_DRONE_CONFIG_ulCritObstacleDist:
            GetConfigDrone(&(st_droneConfig.ulCritObstacleDist));
            break;
        case PARAM_DRONE_CONFIG_ulCritZigbeeSignalLvl:
            GetConfigDrone(&(st_droneConfig.ulCritZigbeeSignalLvl));
            break;
        case PARAM_DRONE_CONFIG_xBatteryMonitoringPeriod:
            GetConfigDrone(&(st_droneConfig.xBatteryMonitoringPeriod));
            break;
        case PARAM_DRONE_CONFIG_xDetectObstaclePeriod:
            GetConfigDrone(&(st_droneConfig.xDetectObstaclePeriod));
            break;
        case PARAM_DRONE_CONFIG_xZigbeeReceivePeriod:
            GetConfigDrone(&(st_droneConfig.xZigbeeReceivePeriod));
            break;
        case PARAM_DRONE_CONFIG_xFlightCtrlPeriod:
            GetConfigDrone(&(st_droneConfig.xFlightCtrlPeriod));
            break;
        case PARAM_DRONE_CONFIG_xGPSReceivePeriod:
            GetConfigDrone(&(st_droneConfig.xGPSReceivePeriod));
            break;
        case PARAM_DRONE_CONFIG_xVideoTogglePeriod:
            GetConfigDrone(&(st_droneConfig.xVideoTogglePeriod));
            break;
        case PARAM_DRONE_CONFIG_xIMUDataTimeout:
            st_droneConfig.xIMUDataTimeout = st_BufferIn.Data[iIndexBufferIn++];
            break;
        case PARAM_DRONE_CONFIG_xZigbeeCmdTimeout:
            st_droneConfig.xZigbeeCmdTimeout = st_BufferIn.Data[iIndexBufferIn++];
            break;
        case PARAM_DRONE_CONFIG_xZigbeeReceiveTimeout:
            st_droneConfig.xZigbeeReceiveTimeout = st_BufferIn.Data[iIndexBufferIn++];
            break;
        case PARAM_DRONE_CONFIG_xTelemeterTimeout:
            st_droneConfig.xTelemeterTimeout = st_BufferIn.Data[iIndexBufferIn++];
            break;
        case PARAM_DRONE_CONFIG_xBatteryTimeout:
            st_droneConfig.xBatteryTimeout = st_BufferIn.Data[iIndexBufferIn++];
            break;
        case PARAM_DRONE_CONFIG_xGPSTimeout:
            st_droneConfig.xGPSTimeout = st_BufferIn.Data[iIndexBufferIn++];
            //printf("\n%d\n",st_droneConfig.xGPSTimeout);
            break;
        case PARAM_DRONE_ERROR:
            GetDroneError(&(st_DroneState.eErrorMask));
            //ERREUR A TRAITER?
            //Ici, si erreur mineur-> on demande si elle doit être ignoré
                                   // et on stock pour la prochaine émission
            break;
        case PARAM_FLY_STATE:
            GetDroneState(&(st_DroneState.eFltState));
            if(st_DroneState.eFltState == STATE_STARTING)
                bReadyToSend = false;
            break;
        case PARAM_IMU_xUpdateTime:
            GetDroneTime(&(st_DataIMU.xUpdateTime));
            break;
        case PARAM_GPS_xUpdateTime:
            GetDroneTime(&(st_DataGPS.xUpdateTime));
            break;
        default:
            break;
        }
    }
}

void ZigBee::GetConfigDrone(uint32_t *param)
{
    *param = 0;

    for(int j = 0 ; j < 4 ; j++)
        *param = (uint32_t)( (*param)*256 + (uint32_t)st_BufferIn.Data[ (3-j) + iIndexBufferIn ] );
    iIndexBufferIn += 4;
}

void ZigBee::GetDroneError(droneError *param)
{
    *param = (droneError)0;

    for(int j = 0 ; j < 2 ; j++)
        *param = (droneError)( (*param)*256 + (droneError)st_BufferIn.Data[ (1-j) + iIndexBufferIn ] );
    iIndexBufferIn += 2;
}

void ZigBee::GetDroneState(droneFltState *param)
{
    *param = (droneFltState)st_BufferIn.Data[iIndexBufferIn++];
}

void ZigBee::GetDroneTime(portTickType *param) {

    *param = 0;

    for(int j = 0 ; j < 4 ; j++)
        *param = (portTickType)( (*param)*256 + (portTickType)st_BufferIn.Data[ (3-j) + iIndexBufferIn ] );
    iIndexBufferIn += 4;
}
