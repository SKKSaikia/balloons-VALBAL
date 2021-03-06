/*
  Stanford Student Space Initiative
  Balloons | VALBAL | December 2017
  Davy Ragland | dragland@stanford.edu

  File: Config.h
  --------------------------
  Global constants specific to each launch.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <string.h>
#include "LasagnaController.h"

/****************************  COMPILE FLAGS  *********************************/
//#define STORAGE_MODE_FLAG // uncomment for power off
#define RESET_EEPROM_FLAG // uncomment for EEPROM reset
// #define HITL_ENABLED_FLAG // uncomment for HITL
//#define RB_DISABLED_FLAG  // uncomment to disable rockblock
//#define WIPE_SD_CARD_YOLO // uncomment to wipe the SD card

#ifndef JOHNSIM
  #include "ConfigHardware.h"
#endif

/****************************  EDITABLE CONSTANTS  ****************************/

static const uint8_t   CUTDOWN_INDEX                         =               99;
static const uint16_t  CUTDOWN_DURATION                      =            10000;

static const uint16_t  PAYLOAD_INDEX                         =              137;

static const uint16_t  GPS_LOCK_TIMEOUT                      =              500;
static const uint16_t  GPS_QUIT_TIMEOUT                      =            10000;

static const uint32_t  GPS_INTERVAL_DEFAULT                  =            15000;
static const uint32_t  RB_INTERVAL_DEFAULT                   =           120000;
static const uint32_t  RB_RESTART_INTERVAL                   =          1800000;
static const uint32_t  RB_DEBUG_INTERVAL                     =            60000;
static const uint16_t  LOOP_INTERVAL                         =               50;

static const uint16_t  DEBUG_ALT                             =             2000;
static const uint16_t  COMMS_BUFFER_SIZE                     =              200;
static const uint32_t  FILE_RESET_INTERVAL                   =         86400000;
static const uint32_t  CONSOLE_BAUD                          =           115200;
static const uint32_t  GPS_BAUD                              =             9600;
static const uint32_t  RB_BAUD                               =            19200;

static const uint32_t CURRENT_NUM_SAMPLES                    =             128;
/***************************  Flight Parameters  ******************************/
static const bool      MANUAL_MODE_DEFAULT                   =            false;
static const uint8_t   REPORT_MODE_DEFAULT                   =                1;
static const uint32_t  QUEUE_APPEND_THRESHOLD                =             1000;

static const float     CHARGER_TEMP_THRESH_HIGH              =              -60;
static const float     CHARGER_TEMP_THRESH_LOW               =              -70;
static const float     SUPER_CAP_VOLTAGE_NOMINAL             =              5.0;

static const float     PRESS_BASELINE_DEFAULT                =         101325.0;
static const float     INCENTIVE_NOISE_DEFAULT               =                0;
static const float     INCENTIVE_THRESHOLD_DEFAULT           =             0.75;
static const float     RE_ARM_DEFAULT                        =                0;
static const float     BALLAST_ARM_ALT_DEFAULT               =          13250.0;
static const float     BALLAST_ALT_LAST_FILLER               =          14000.0;
static const uint32_t  BALLAST_REVERSE_INTERVAL_DEFAULT      =           300000;
static const uint16_t  BALLAST_STALL_CURRENT_DEFAULT         =              120;

static const float     VALVE_SETPOINT_DEFAULT                =          14500.0;
static const uint32_t  VALVE_VENT_DURATION_DEFAULT           =            20000;
static const float     VALVE_ALT_LAST_DEFAULT                =                0;
static const float     VALVE_VELOCITY_DEFAULT                =              1.0;
static const float     VALVE_ALTITUDE_DIFF_DEFAULT           =     1.0 / 1500.0;
static const float     VALVE_LAST_ACTION_DEFAULT             =     1.0 / 1500.0;

static const float     BALLAST_SETPOINT_DEFAULT              =          13500.0;
static const uint32_t  BALLAST_DROP_DURATION_DEFAULT         =            15000;
static const float     BALLAST_ALT_LAST_DEFAULT              =         -90000.0;
static const float     BALLAST_VELOCITY_DEFAULT              =              1.0;
static const float     BALLAST_ALTITUDE_DIFF_DEFAULT         =     1.0 / 1500.0;
static const float     BALLAST_LAST_ACTION_DEFAULT           =     1.0 / 1500.0;

static const uint16_t  VALVE_MOTOR_SPEED_OPEN_DEFAULT        =              255;
static const uint16_t  VALVE_MOTOR_SPEED_CLOSE_DEFAULT       =              255;
static const uint16_t  BALLAST_MOTOR_SPEED_DEFAULT           =              255;
static const uint32_t  VALVE_OPENING_DURATION_DEFAULT        =             2000;
static const uint32_t  VALVE_CLOSING_DURATION_DEFAULT        =             3000;
static const uint16_t  BALLAST_STALL_TIMEOUT                 =             3000;

static const float     DLDT_SCALE_DEFAULT                    =             0.0;

static const float     GPS_MANUAL_MODE_DEFAULT               =             true;
static const float     GPS_MANUAL_MODE_OVERRIDE_DEFAULT      =             true;
static const float     LAT_GPS_MANUAL_DEFAULT                =        37.427538;
static const float     LONG_GPS_MANUAL_DEFAULT               =       122.174461;

static const float     MAX_PRESURE                           =           107500;
static const float     MIN_PRESURE                           =             1131;
static const float     MAX_CONSENSUS_DEVIATION               =              150;
static const uint16_t  MAX_VELOCITY                          =               50;
static const uint16_t  ALTITUDE_STANDARD_DEV                 =                2;
static const uint16_t  ALTITUDE_BUFFER_SIZE                  =             1000;
static const uint16_t  MINIMUM_ALTITUDE_POINTS               =              600;
static const uint16_t  MINIMUM_ASCENT_RATE_POINTS            =              600;
static const uint16_t  VOLTAGE_BUFFER_SIZE                   =               20;

static const float     SPAG_K_DEFAULT                        =          0.00001;
static const float     SPAG_B_DLDT_DEFAULT                   =            0.001;
static const float     SPAG_V_DLDT_DEFAULT                   =            0.001;
static const float     SPAG_RATE_MIN_DEFAULT                 =          0.00001;
static const float     SPAG_RATE_MAX_DEFAULT                 =            0.001;
static const float     SPAG_B_TMIN_DEFAULT                   =                2;
static const float     SPAG_V_TMIN_DEFAULT                   =                2;
static const float     SPAG_H_CMD_DEFAULT                    =            14000;
static const float     SPAG_ASCENT_RATE_THRESH_DEFAULT       =              0.4;
static const float     SPAG_V_SS_ERROR_THRESH_DEFAULT        =             1000;
static const float     SPAG_B_SS_ERROR_THRESH_DEFAULT        =             1000;
static const float     SPAG_KFUSE_DEFAULT                    =                7;
static const float     SPAG_KFUSE_V_DEFAULT                  =              0.5;

static const float     PSC_SLOPE                             =            0.011;
static const float     PSC_INTERCEPT                         =          -0.2419;
static const float     CM_WATER_TO_PA                        =          98.0665;

static const uint8_t   CONTROLLER_INDEX_DEFAULT              =                3;

enum {
  LEGACY_CONTROLLER_INDEX               =                0,
  SPAG_CONTROLLER_INDEX                 =                1,
  SPAG2_CONTROLLER_INDEX                =                2,
  LAS_CONTROLLER_INDEX                  =                3
};

/*****************************  EEPROM ADDRESSES  *****************************/
static const uint8_t   EEPROM_ROCKBLOCK                      =                0;
static const uint8_t   EEPROM_GPS                            =                1;
static const uint8_t   EEPROM_PAYLOAD                        =                2;

static const uint8_t   EEPROM_VALVE_ALT_LAST                 =                4;
static const uint8_t   EEPROM_BALLAST_ALT_LAST               =                8;

static const uint8_t   EEPROM_VALVE_SETPOINT                 =               12;
static const uint8_t   EEPROM_VALVE_VELOCITY_CONSTANT        =               16;
static const uint8_t   EEPROM_VALVE_ALTITUDE_DIFF_CONSTANT   =               20;
static const uint8_t   EEPROM_VALVE_LAST_ACTION_CONSTANT     =               24;

static const uint8_t   EEPROM_BALLAST_SETPOINT               =               28;
static const uint8_t   EEPROM_BALLAST_VELOCITY_CONSTANT      =               32;
static const uint8_t   EEPROM_BALLAST_ALTITUDE_DIFF_CONSTANT =               36;
static const uint8_t   EEPROM_BALLAST_LAST_ACTION_CONSTANT   =               40;

static const uint8_t   EEPROM_LOG_BLOCK_CUR                  =              112;
static const uint8_t   EEPROM_LOG_FILE_NUM                   =              116;

/*****************************  CURRENT SENSOR CONSTANTS  **********************/
static const uint32_t  CURRENT_SENSOR_CLOCK_SPEED            =         1000000; // 16 MHz
static const float     CURRENT_SENSOR_VREF                   =              3.3;
static const uint16_t  CURRENT_SENSOR_MAX_BIP                =            0x7FF;
static const bool      USING_CHANNEL_DIFF_0_1                =            false;
static const bool      USING_CHANNEL_DIFF_2_3                =            false;
static const bool      USING_CHANNEL_DIFF_4_5                =            false;
static const bool      USING_CHANNEL_DIFF_6_7                =            false;
static const bool      USING_CHANNEL_DIFF_8_9                =            true;
static const bool      USING_CHANNEL_DIFF_10_11              =            true;
static const bool      USING_CHANNEL_DIFF_12_13              =            true;
static const bool      USING_CHANNEL_DIFF_14_15              =            true;

/***************************** SHITL stuff ************************************/
#define FSTART 0xAA

/************************* Serial Monitor stuff *******************************/
#define FSTART_SM 0xAB

#endif
