/*
  Stanford Student Space Initiative
  Balloons | VALBAL | December 2017
  Davy Ragland | dragland@stanford.edu
  Jonathan Zwiebel | jzwiebel@stanford.edu

  File: data.h
  --------------------------
  Data frame structure.
*/

#ifndef data_H
#define data_H

#include "Config.h"
#include "Heater.h"
#include "Utils.h"
#include "LasagnaController.h"
#include "SpaghettiController.h"
#include "SpaghettiController2.h"

/**************************  CURRENT DATA FRAME  ******************************/
struct DataFrame {
/******************************  PRIMARY DATA  ********************************/
  uint32_t   TIME                            =                                0;
  uint32_t   LOOP_NUMBER                     =                                0; // Useful for checking data integrity
  float      LAT_GPS                         =                                0;
  float      LONG_GPS                        =                                0;
  float      ALTITUDE_BAROMETER              =                                0;
  float      ALTITUDE_GPS                    =                                0;
  float      ALTITUDE_CORRECTED              =                                0;
  float      ASCENT_RATE                     =                                0;
  int32_t    ACTION                          =                                0;
  float      VALVE_INCENTIVE                 =                                0;
  float      BALLAST_INCENTIVE               =                                0;
  bool       VALVE_STATE                     =                            false;
  bool       BALLAST_STATE                   =                            false;
  bool       BALLAST_DIRECTION               =                            false;
  uint32_t   VALVE_QUEUE                     =                                0;
  uint32_t   BALLAST_QUEUE                   =                                0;
  uint32_t   VALVE_TIME_TOTAL                =                                0;
  uint32_t   BALLAST_TIME_TOTAL              =                                0;
  uint32_t   VALVE_NUM_ACTIONS               =                                0;
  uint32_t   BALLAST_NUM_ACTIONS             =                                0;
  uint32_t   VALVE_NUM_ATTEMPTS              =                                0;
  uint32_t   BALLAST_NUM_ATTEMPTS            =                                0;
  uint32_t   BALLAST_NUM_OVERCURRENTS        =                                0;
  bool       CUTDOWN_STATE                   =                            false;
  uint8_t    MAX_CURRENT_CHARGING_LIMIT      =                                0;
  uint8_t    SYSTEM_POWER_STATE              =                                0;

  float      TEMP_INT                        =                                0;
  float      JOULES_TOTAL                    =                                0;
  float      VOLTAGE_PRIMARY                 =                                0;
  float      VOLTAGE_SUPERCAP_AVG            =                                0;
  float      CURRENT_MOTORS                  =                                0;
  float      TEMP_EXT                        =                                0;
  uint32_t   LOOP_TIME_MAX                   =                                0;
  uint32_t   RB_SENT_COMMS                   =                                0;
  uint8_t    RB_RESTARTS                     =                                0;
  uint8_t    RESISTOR_MODE                   =                                0;

  bool       MANUAL_MODE                     =              MANUAL_MODE_DEFAULT;
  uint8_t    REPORT_MODE                     =              REPORT_MODE_DEFAULT;
  bool       SHOULD_REPORT                   =                            false;

/*****************************  SECONDARY DATA  *******************************/
  bool       POWER_STATE_LED                 =                             true;
  bool       POWER_STATE_RB                  =                             true;
  bool       POWER_STATE_GPS                 =                             true;
  bool       POWER_STATE_PAYLOAD             =                            !true;
  uint8_t    NUM_SATS_GPS                    =                                0;
  float      SPEED_GPS                       =                                0;
  float      HEADING_GPS                     =                                0;
  SunsetPredictor::GPSTime GPS_TIME;
  bool SWITCH_TO_MANUAL = false;
  float      ALTITUDE_OFFSET                 =                                0;
  float      ALTITUDE_OFFSET_GAIN            =                             4e-5;

  float      INCENTIVE_NOISE                 =          INCENTIVE_NOISE_DEFAULT;
  float      RE_ARM_CONSTANT                 =                   RE_ARM_DEFAULT;
  float      VALVE_ALT_LAST                  =           VALVE_ALT_LAST_DEFAULT;
  float      BALLAST_ALT_LAST                =         BALLAST_ALT_LAST_DEFAULT;

  uint8_t    CURRENT_CONTROLLER_INDEX        =         CONTROLLER_INDEX_DEFAULT;

  bool       DEBUG_STATE                     =                             true;
  bool       FORCE_VALVE                     =                            false;
  bool       FORCE_BALLAST                   =                            false;

  bool BMP_ENABLE[4] = {true, true, true, true};
  uint32_t BMP_REJECTIONS[4];
  float MAX_CONSENSUS_DEVIATION = 500;
  bool BMP_REJECTION_ENABLED = true;
  float ALTITUDE_PREFILT = 0;
  uint32_t MAX_TIME_WITHOUT_SENSORS = 60000;
  float ERROR_REJECTION_VEL = 10;
  float ERROR_REJECTION_STD = 3.4;
  float ERROR_REJECTION_DT = 0.6;
  uint32_t RB_COOLDOWN = 60000;

/*****************************  TERTIARY DATA  ********************************/
  uint32_t   RB_INTERVAL                     =              RB_INTERVAL_DEFAULT;
  uint32_t   GPS_INTERVAL                    =             GPS_INTERVAL_DEFAULT;

  float      LAT_GPS_MANUAL                  =           LAT_GPS_MANUAL_DEFAULT;
  float      LONG_GPS_MANUAL                 =          LONG_GPS_MANUAL_DEFAULT;
  bool       GPS_MANUAL_MODE                 =          GPS_MANUAL_MODE_DEFAULT;
  bool       GPS_MANUAL_MODE_OVERRIDE        = GPS_MANUAL_MODE_OVERRIDE_DEFAULT;

  float      PRESS_BASELINE                  =           PRESS_BASELINE_DEFAULT;
  float      INCENTIVE_THRESHOLD             =      INCENTIVE_THRESHOLD_DEFAULT;
  float      BALLAST_ARM_ALT                 =          BALLAST_ARM_ALT_DEFAULT;

  uint32_t   BALLAST_REVERSE_INTERVAL        = BALLAST_REVERSE_INTERVAL_DEFAULT;
  uint16_t   BALLAST_STALL_CURRENT           =    BALLAST_STALL_CURRENT_DEFAULT;
  uint16_t   VALVE_MOTOR_SPEED_OPEN          =   VALVE_MOTOR_SPEED_OPEN_DEFAULT;
  uint16_t   VALVE_MOTOR_SPEED_CLOSE         =  VALVE_MOTOR_SPEED_CLOSE_DEFAULT;
  uint16_t   BALLAST_MOTOR_SPEED             =      BALLAST_MOTOR_SPEED_DEFAULT;
  uint32_t   VALVE_OPENING_DURATION          =   VALVE_OPENING_DURATION_DEFAULT;
  uint32_t   VALVE_CLOSING_DURATION          =   VALVE_CLOSING_DURATION_DEFAULT;

  float      VALVE_SETPOINT                  =           VALVE_SETPOINT_DEFAULT;
  uint32_t   VALVE_VENT_DURATION             =      VALVE_VENT_DURATION_DEFAULT;
  uint32_t   VALVE_FORCE_DURATION            =      VALVE_VENT_DURATION_DEFAULT;
  float      VALVE_VELOCITY_CONSTANT         =           VALVE_VELOCITY_DEFAULT;
  float      VALVE_ALTITUDE_DIFF_CONSTANT    =      VALVE_ALTITUDE_DIFF_DEFAULT;
  float      VALVE_LAST_ACTION_CONSTANT      =        VALVE_LAST_ACTION_DEFAULT;

  float      BALLAST_SETPOINT                =         BALLAST_SETPOINT_DEFAULT;
  uint32_t   BALLAST_DROP_DURATION           =    BALLAST_DROP_DURATION_DEFAULT;
  uint32_t   BALLAST_FORCE_DURATION          =    BALLAST_DROP_DURATION_DEFAULT;
  float      BALLAST_VELOCITY_CONSTANT       =         BALLAST_VELOCITY_DEFAULT;
  float      BALLAST_ALTITUDE_DIFF_CONSTANT  =    BALLAST_ALTITUDE_DIFF_DEFAULT;
  float      BALLAST_LAST_ACTION_CONSTANT    =      BALLAST_LAST_ACTION_DEFAULT;

  float     DLDT_SCALE                       =               DLDT_SCALE_DEFAULT;
  bool      USE_ALTITUDE_CORRECTED           =                             true;


/*******************************  EXTRA DATA  *********************************/
  bool       SETUP_STATE                     =                             true;
  bool       SHOULD_CUTDOWN                  =                            false;

  uint32_t   LOOP_TIME                       =                                0;
  uint32_t   LOG_TIME                        =                                0;
  float      RAW_TEMP_1                      =                                0;
  float      RAW_TEMP_2                      =                                0;
  float      RAW_TEMP_3                      =                                0;
  float      RAW_TEMP_4                      =                                0;
  float      RAW_PRESSURE_1                  =                                0;
  float      RAW_PRESSURE_2                  =                                0;
  float      RAW_PRESSURE_3                  =                                0;
  float      RAW_PRESSURE_4                  =                                0;
  float      VOLTAGE_SUPERCAP                =                                0;
  float      CURRENT_TOTAL                   =                                0;
  float      CURRENT_RB                      =                                0;
  float      CURRENT_MOTOR_VALVE             =                                0;
  float      CURRENT_MOTOR_BALLAST           =                                0;
  float      CURRENT_PAYLOAD                 =                                0;

  uint32_t   GPS_LAST                        =                                0;
  uint32_t   GPS_LAST_NEW                    =                                0;
  uint32_t   RB_LAST                         =                                0;
  uint32_t   DATAFILE_LAST                   =                                0;
  uint16_t   COMMS_LENGTH                    =                                0;

  float      RB_HEAT_DUTY                    =                                0;

  int32_t ACTIONS[4] = {0};

  float ESTIMATED_DLDT                       =                                0;
  float SOLAR_ELEVATION                      =                                0;
  float DSEDT                                =                                0;

  bool GEOFENCED_CUTDOWN_ENABLE = true;
  bool IN_CUBA = false;
  uint32_t CUBA_TIMEOUT = 0;
  uint32_t CUBA_MAX_SECONDS = 3600;
  float BB_LAT1 = 18.628752;
  float BB_LAT2 = 24.152548;
  float BB_LON1 = -87.282412;
  float BB_LON2 = -71.779459;

  bool TIMED_CUTDOWN_ENABLE = false;
  uint32_t TIMED_CUTDOWN_MILLIS = 0;

  /* Dead man's timer defaults to 14 hours. It cutds down after unsuccessfully sending a
   * comm for that long. */
  bool DEADMAN_ENABLED = true;
  uint32_t DEADMAN_TIME = 50400000;
  uint32_t TIME_LAST_COMM = 0;

  uint32_t TIME_LAST_CUTDOWN = 0;

  float VOLTAGE_SUPERCAP_MIN = 314;

  bool       POWER_STATE_RADIO =                           !true;

  SpaghettiController::Constants SPAG_CONSTANTS;
  SpaghettiController::State SPAG_STATE;
  SpaghettiController2::Constants SPAG2_CONSTANTS;
  SpaghettiController2::State SPAG2_STATE;
  LasagnaController::Constants LAS_CONSTANTS;
  LasagnaController::State LAS_STATE;
  Heater::Constants HEATER_CONSTANTS;
  uint32_t  ACTION_TIME_TOTALS[8]            =                               {0};
  float     OVERPRESSURE                     =                                 0;
  float     OVERPRESSURE_FILT                =                                 0;
  float     OVERPRESSURE_VREF                =                                 0;
  float     OVERPRESSURE_VREF_FILT           =                                 0;
  uint8_t stuff_to_make_sure_it_goes_above_1024[512];

} __attribute__((packed));

#include <assert.h>

static_assert(sizeof(DataFrame) >= 1024, "ohp dataframe too big");

// template<int s> struct Wow;
// struct foo {
//     int a,b;
// };
// Wow<sizeof(DataFrame)> wow;

#endif
