#ifndef TYPDEFUART_H
#define TYPDEFUART_H
/*  ATTENTION !! enum : seul les 16 bits de poids faibles sont transmits !!
 *
 */

#include <fcntl.h>

typedef unsigned int  uint32_t;
typedef uint32_t      portTickType;
//typedef char          int8_t;
typedef unsigned char uint8_t;

struct tramZigbee {
    char lengthData;
    char Data[72];
	//CRC ?
};

enum zigbeeCommandId
{
CMD_REBOOT,
CMD_SHUTDOWN,
CMD_VIDEO_ENABLE,
CMD_VIDEO_DISABLE,
CMD_FLT_TAKEOFF,
CMD_FLT_LANDING,
CMD_FLT_AUTOTUNING, /* changer automatiquement les paramètres de
l'asservissement moteur (PID) */
CMD_RESET_AUTOTUNING, /* Retour au défaut */
CMD_SET_CONFIG, /* Configuration depuis la base… voir droneConfig */
CMD_RESET_CONFIG,
CMD_GET_CONFIG, /* Récupération de la config actuelle */
CMD_GET_STATUS, /* Statut du drone (voir droneState, droneIMUData,
droneZigbeeData, droneGPSData, droneTelemeterData, droneBatteryData) */
CMD_FLT_MANEUVER,
/* Ignore minor error */
CMD_ERR_IGNORE
};

enum tramDataId {       //Manque les structure GPS IMU TELEMETER
    PARAM_DRONE_CONFIG_ulMaxAngle,
    PARAM_DRONE_CONFIG_ulTakeoffAltitude,
    PARAM_DRONE_CONFIG_ulMinAltitude,
    PARAM_DRONE_CONFIG_ulCritBatteryLvl,
    PARAM_DRONE_CONFIG_ulCritObstacleDist,
    PARAM_DRONE_CONFIG_ulCritZigbeeSignalLvl,
    PARAM_DRONE_CONFIG_xBatteryMonitoringPeriod,
    PARAM_DRONE_CONFIG_xDetectObstaclePeriod,
    PARAM_DRONE_CONFIG_xZigbeeReceivePeriod,
    PARAM_DRONE_CONFIG_xFlightCtrlPeriod,
    PARAM_DRONE_CONFIG_xGPSReceivePeriod,
    PARAM_DRONE_CONFIG_xVideoTogglePeriod,
    PARAM_DRONE_CONFIG_xIMUDataTimeout,
    PARAM_DRONE_CONFIG_xZigbeeCmdTimeout,
    PARAM_DRONE_CONFIG_xZigbeeReceiveTimeout,
    PARAM_DRONE_CONFIG_xTelemeterTimeout,
    PARAM_DRONE_CONFIG_xBatteryTimeout,
    PARAM_DRONE_CONFIG_xGPSTimeout,
	PARAM_CMD_ID,
    PARAM_CMD_DRONE, /*		Commande de Vol(X,Y,Z,R)	*/
    /*	PARAM_FLY_TransX,	*/
    /*	PARAM_FLY_TransY,	*/
    /*	PARAM_FLY_TransZ,	*/
    /*	PARAM_FLY_RotZ,		*/
    PARAM_FLY_STATE,
    PARAM_DRONE_ERROR,
    PARAM_IMU_xUpdateTime,
    PARAM_GPS_xUpdateTime,
    PARAM_TELM_xUpdateTime,
    PARAM_BAT_ulPowerLvl,
    PARAM_BAT_xUpdateTime
};


/*la configuration contient (pour le moment ;-)) les éléments suivants
(les types de donnée sont par défaut) :*/
struct droneConfig
{
/* Maximum pitch/roll angle (horizontal reference) - akin to maximum
horizontal speed. */
uint32_t ulMaxAngle;
/* Preset altitude for automatic takeoff */
uint32_t ulTakeoffAltitude;
/* Minimal flight height (based on telemeters) */
uint32_t ulMinAltitude;
/* Reference altitude, set at takeoff */
uint32_t ulRefAltitude;
/* Battery level to activate automatic landing */
uint32_t ulCritBatteryLvl;
/* Distance to activate obstacle avoidance */
uint32_t ulCritObstacleDist;
/* Critical drone-base link level - yet unused */
uint32_t ulCritZigbeeSignalLvl;
/* Task periods */
portTickType xBatteryMonitoringPeriod; /* portTickType = uint32_t */
portTickType xDetectObstaclePeriod;
portTickType xZigbeeReceivePeriod; /* Période de tâche de comm
drone/base */
portTickType xFlightCtrlPeriod;
portTickType xGPSReceivePeriod;
portTickType xVideoTogglePeriod;
/* Timeouts for data validity */
uint8_t xIMUDataTimeout;
uint8_t xZigbeeCmdTimeout;
uint8_t xZigbeeReceiveTimeout;
uint8_t xTelemeterTimeout;
uint8_t xBatteryTimeout;
uint8_t xGPSTimeout;
};

//Le mouvement en "argument" de CMD_FLT_MANEUVER :
/* Command as received from the base */
struct flightCommand
{
/* Translations */
int8_t cTransX; /* Forward/backward */
int8_t cTransY; /* Lateral translation (left when +) */
int8_t cTransZ; /* Vertical translation (up when +) */
/* Yaw */
int8_t cRotZ; /* Yaw (counter-clockwise when +) */
};

//Champs contenus dans le statut :
/* Mutually exclusive drone states behavior. */
enum droneFltState
{
/* Initialization phase */
STATE_STARTING,
/* Initialization successful */
STATE_GROUND_RDY,
/* Error while landed */
STATE_GROUND_ERR,
/* Must be landed */
STATE_TAKEOFF,
/* Normal flight, stationary flight if no flight command received */
STATE_FLIGHT,
/* PID parameters autotuning */
STATE_AUTOTUNING,
/* Error while flying - triggers emergency landing */
STATE_FLIGHT_ERR,
/* Must be flying */
STATE_LANDING
};
//(Diagramme d'état en pièce jointe pour éclaircir)

//Codes d'erreur. Les timeouts sont plus graves que les données invalides.
//En fait, trop de données invalides à la suite entraîne un timeout.
//Il s'agit de masques afin de réduire leur empreinte mémoire (un seul
//uint32_t pour toutes les combinaisons possibles).
/* Mainly used for status transmission - Used as a mask */
enum droneError
{
/* Everything is shiny */
DRN_ERR_NONE = 0x00,
/* Timeout of telemeter data */
DRN_ERR_TLM_TOUT = 0x01,
/* Data out of valid range */
DRN_ERR_TLM_INVAL = 0x02,
/* Timeout of IMU data */
DRN_ERR_IMU_TOUT = 0x04,
/* Data out of valid range */
DRN_ERR_IMU_INVAL = 0x08,
/* Timeout of GPS data */
DRN_ERR_GPS_TOUT = 0x10,
/* Data out of valid range */
DRN_ERR_GPS_INVAL = 0x20,
/* Timeout of telemeter data */
DRN_ERR_CMD_TOUT = 0x40,
/* Timeout of battery level */
DRN_ERR_BATT_TOUT = 0x80,
/* Data out of valid range */
DRN_ERR_BATT_INVAL = 0x100,
/* Timeout of base-drone communication data */
DRN_ERR_RX_TOUT = 0x200,
/* Initialization errors */
DRN_ERR_CONFIG = 0x400,
DRN_ERR_CMD = 0x800,
DRN_ERR_INIT = 0x8000
/* No video error because we don't have much to do with it */
};

//État du drone, stocke son état de vol (machine d'état) et les codes
//d'erreurs actuelles
struct droneState
{
/* Drone state */
enum droneFltState eFltState;
/* Error codes for transmission */
enum droneError eErrorMask;
};

/* Orientation du drone (pitch, yaw, roll) et date de mise à jour (en
multiples du systick : 50ms pour le moment)*/
struct droneIMUData
{
//struct IMUData xIMUData;
/* Time of last update */
portTickType xUpdateTime;
};

struct droneGPSData
{
/* GPS data */
//struct GPSData xGPSData;
/* Time of last update */
portTickType xUpdateTime;
};

//Distances mesurées par chaque télémètres
/* Telemeter distances, identifiers of telemeters having detected an
obstacle
and time of last update */
struct droneTelemeterData
{
/* Measured distances */
//struct telemeterData xTelemeterData;
/* Time of last update */
portTickType xUpdateTime;
};

struct droneBatteryData
{
uint32_t ulPowerLvl;
/* Time of last update */
portTickType xUpdateTime;
};
#endif // TYPDEFUART_H
