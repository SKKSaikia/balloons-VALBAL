/*
  Stanford Student Space Initiative
  Balloons | VALBAL | February 2017
  Davy Ragland | dragland@stanford.edu
  Michal Adamkiewicz | mikadam@stanford.edu

  File: Sensors.cpp
  --------------------------
  Implimentation of Sensors.h
*/

#include "Sensors.h"

/**********************************  SETUP  ***********************************/
/*
  function: init
  ---------------------------------
  This function initializes the sensor hardware.
*/
bool Sensors::init() {
  bool sucess = true;
  if (!bme1.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    sucess = false;
  }
  if (!bme2.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    sucess = false;
  }
  if (!bme3.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    sucess = false;
  }
  if (!bme4.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    sucess = false;
  }
  // Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
  // Wire.setDefaultTimeout(5 * 1000);
  // int8_t ack = 0;
  // ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CHANNEL_ENABLE_REG, LTC2991_ENABLE_ALL_CHANNELS);
  // ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_V1234_REG, 0x00);
  // ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_V5678_REG, 0x00);
  // ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_PWM_Tinternal_REG, LTC2991_REPEAT_MODE);
  return sucess;
}

/********************************  FUNCTIONS  *********************************/
/*
  function: getTime
  ---------------------------------
  This function returns the time as a fixed length string.
*/
uint32_t Sensors::getTime() {
  return millis();
}

/*
  function: getVoltage
  ---------------------------------
  This function gets the battery voltage.
*/
double Sensors::getVoltage() {
  return (double)analogRead(VBAT_PIN) * 1.2 * 4.0 / (double)pow(2, 12);
}

/*
  function: getCurrent
  ---------------------------------
  This function gets the total current draw.
*/
double Sensors::getCurrent() {
  double currentMonitor = (double)analogRead(BATT_CURRENT) / (double)pow(2, 12) * 1.2 * 4.0 / 0.496;
  double externalCurrentMonitor = (double)analogRead(EXTERNAL_CURRENT) / (double)pow(2, 12) * 1.2 * 4.0 / 0.496;
  return currentMonitor + externalCurrentMonitor;
}

/*
  function: getCurrentGPS
  ---------------------------------
  This function gets the GPS current draw.
*/
double Sensors::getCurrentGPS() {
  return 0;
}

/*
  function: getCurrentRB
  ---------------------------------
  This function gets the RockBLOCK current draw.
*/
double Sensors::getCurrentRB() {
  return 0;
}

/*
  function: getCurrentMotors
  ---------------------------------
  This function gets the motor current draw.
*/
double Sensors::getCurrentMotors() {
  return 0;
}

/*
  function: getCurrentPayload
  ---------------------------------
  This function gets the payload current draw.
*/
double Sensors::getCurrentPayload() {
  return 0;
}

/*
  function: getTempIn
  ---------------------------------
  This function returns a sensor fused reading.
*/
double Sensors::getTemp() {
  double temp_1 = bme1.readTemperature();
  double temp_2 = bme2.readTemperature();
  double temp_3 = bme3.readTemperature();
  double temp_4 = bme4.readTemperature();
  return (temp_1 + temp_2 + temp_3 + temp_4) / 4;
}

/*
  function: getPressure
  ---------------------------------
  This function returns a sensor fused reading.
*/
double Sensors::getPressure() {
  double press_1 = bme1.readPressure();
  double press_2 = bme2.readPressure();
  double press_3 = bme3.readPressure();
  double press_4 = bme4.readPressure();
  return (press_1 + press_2 + press_3 + press_4) / 4;
}

/*
  function: getAltitude
  ---------------------------------
  This function returns a sensor fused reading.
*/
double Sensors::getAltitude() {
  altitudeLast = altitudeCurr;
  double altitude_1 = bme1.readAltitude(1013.25);
  double altitude_2 = bme2.readAltitude(1013.25);
  double altitude_3 = bme3.readAltitude(1013.25);
  double altitude_4 = bme4.readAltitude(1013.25);
  altitudeCurr = (altitude_1 + altitude_2 + altitude_3 + altitude_4) / 4;
  return altitudeCurr;
}

/*
  function: getAscentRate
  ---------------------------------
  This function returns the current ascent rate.
*/
double Sensors::getAscentRate() {
  ASCENT_RATE_BUFFER[ascentRateIndex] = (altitudeCurr - altitudeLast) / ((millis() - ascentRateLast) / 1000.0);
  ascentRateLast = millis();
  ascentRateIndex++;
  ascentRateIndex %= BUFFER_SIZE;
  float ascentRateTotal = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) ascentRateTotal += ASCENT_RATE_BUFFER[i];
  return  ascentRateTotal / BUFFER_SIZE;
}
