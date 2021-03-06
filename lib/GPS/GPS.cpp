/*
  Stanford Student Space Initiative
  Balloons | VALBAL | September 2017
  Davy Ragland | dragland@stanford.edu
  Aria Tedjarati | atedjara@stanford.edu
  Jonathan Zwiebel | jzwiebel@stanford.edu

  File: GPS.cpp
  --------------------------
  Implimentation of GPS.h
*/

#include "GPS.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the Ublox NEO-M8Q GPS module.
 */
bool GPS::init(bool shouldStartup) {
  bool success = false;
  pinMode(GPS_ENABLE_PIN, OUTPUT);
  digitalWrite(GPS_ENABLE_PIN, LOW);
  Serial.println("low");
  Serial.println(shouldStartup);
  delay(2000);
  Serial1.begin(GPS_BAUD);
  if (shouldStartup) {
    success = restart();
  }
  return success;
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: restart
 * -------------------
 * This function restarts the GPS.
 */
bool GPS::restart() {
  bool success = false;
  EEPROM.write(EEPROMAddress, false);
  digitalWrite(GPS_ENABLE_PIN, HIGH);
  Serial.println("bootup");
  uint32_t t0 = millis();
  while (millis()-t0 < 1000) {
    if (Serial1.available()) {
      Serial.print((char)Serial1.read());
    }
  }
  Serial.println();
  Serial.println("done");
  delay(1000);
  EEPROM.write(EEPROMAddress, true);
  delay(1000);
  while (Serial1.available()) Serial1.read();
  if (GPS_MODE == 1) success = setGPSMode(gpsonly, sizeof(gpsonly)/sizeof(uint8_t), GPS_LOCK_TIME);
  success = setGPSMode(flightMode, sizeof(flightMode)/sizeof(uint8_t), GPS_LOCK_TIME);
  return success;
}

void GPS::lowpower() {
  if (GPS_MODE == 1) setGPSMode(pms, sizeof(pms)/sizeof(uint8_t), GPS_LOCK_TIME);
}

/*
 * Function: hotstart
 * -------------------
 * This function hotstarts the GPS.
 */
void GPS::hotstart() {
  Serial1.println("$PUBX,00*33");
  delay(1000);
}

/*
 * Function: shutdown
 * -------------------
 * This function shutsdown the GPS.
 */
void GPS::shutdown() {
  digitalWrite(GPS_ENABLE_PIN, LOW);
  EEPROM.write(EEPROMAddress, false);
}

/*
 * Function: getLatitude
 * -------------------
 * This function returns the current latitude.
 */
float GPS::getLatitude() {
  return tinygps.location.lat();
}

/*
 * Function: getLongitude
 * -------------------
 * This function returns the current longitude.
 */
float GPS::getLongitude() {
  return tinygps.location.lng();
}

/*
 * Function: getAltitude
 * -------------------
 * This function returns the current altitude in meters.
 */
float GPS::getAltitude() {
  return tinygps.altitude.meters();
}

/*
 * Function: getSpeed
 * -------------------
 * This function returns the current speed in mph.
 */
float GPS::getSpeed() {
  return tinygps.speed.mph();
}

/*
 * Function: getCourse
 * -------------------
 * This function returns the current heading in degrees.
 */
float GPS::getCourse() {
  return tinygps.course.deg();
}

/*
 * Function: getSats
 * -------------------
 * This function returns the number of satelites detected.
 */
uint8_t GPS::getSats() {
  return tinygps.satellites.value();
}

/*
 * Function: getYear
 * -------------------
 * This function returns the GPS year.
 * Returns 2000 with no lock
 */
int GPS::getYear() {
  return tinygps.date.year();
}

/*
 * Function: getMonth
 * -------------------
 * This function returns the GPS month.
 * Returns 0 with no lock.
 */
int GPS::getMonth() {
  return tinygps.date.month();
}

/*
 * Function: getDay
 * -------------------
 * This function returns the GPS day.
 * Returns 0 with no lock.
 */
int GPS::getDay() {
  return tinygps.date.day();
}

/*
 * Function: getHour
 * -------------------
 * This function returns the GPS hour.
 * Returns 0 with no lock.
 */
int GPS::getHour() {
  return tinygps.time.hour();
}

/*
 * Function: getMinute
 * -------------------
 * This function returns the GPS minute.
 * Returns 0 with no lock
 */
int GPS::getMinute() {
  return tinygps.time.minute();
}

/*
 * Function: getSecond
 * -------------------
 * This function returns the GPS second.
 * Returns 0 with no lock
 */
int GPS::getSecond() {
  return tinygps.time.second();
}

/*
 * Function: smartDelay
 * -------------------
 * This function pauses the main thread while
 * still communicating with the comms interface.
 */
void GPS::smartDelay(uint32_t ms) {
  uint32_t startt = millis();
  do {
    while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
      tinygps.encode(c);
    }
  } while (millis() - startt < ms);
}

/*********************************  HELPERS  **********************************/
bool GPS::setGPSMode(uint8_t* MSG, uint8_t len, uint16_t GPS_LOCK_TIME){
  Serial.println("Setting uBlox mode: ");
  uint32_t startTime = millis();
  uint8_t gps_set_sucess = 0;
  while(!gps_set_sucess) {
    if(millis() - startTime > GPS_TIMEOUT_TIME) return false;
    sendUBX(MSG, len);
    gps_set_sucess = getUBX_ACK(MSG);
  }
  smartDelay(GPS_LOCK_TIME);
  return true;
}

/*
 * Function: sendUBX
 * -------------------
 * This function sends a byte array of UBX protocol to the GPS.
 */
void GPS::sendUBX(uint8_t* MSG, uint8_t len) {
  Serial.println("Sending UBX");
  for(int i = 0; i < len; i++) {
    Serial1.write(MSG[i]);
    Serial.print(MSG[i], HEX);
  }
  Serial1.println();
}

/*
 * Function: getUBX_ACK
 * -------------------
 * This function calculates the expected UBX ACK packet and parses the UBX response from GPS.
 */
bool GPS::getUBX_ACK(uint8_t* MSG) {
  uint8_t  b;
  uint8_t  ackByteID = 0;
  uint8_t  ackPacket[10];
  uint32_t startTime = millis();
  Serial.print(" * Reading ACK response: ");

  ackPacket[0] = 0xB5;	 // header
  ackPacket[1] = 0x62;	 // header
  ackPacket[2] = 0x05;	 // class
  ackPacket[3] = 0x01;	 // id
  ackPacket[4] = 0x02;	 // length
  ackPacket[5] = 0x00;   // space
  ackPacket[6] = MSG[2]; // ACK class
  ackPacket[7] = MSG[3]; // ACK id
  ackPacket[8] = 0;      // CK_A
  ackPacket[9] = 0;      // CK_B

  for (uint8_t i = 2; i < 8; i++) {
    ackPacket[8] = ackPacket[8] + ackPacket[i];
    ackPacket[9] = ackPacket[9] + ackPacket[8];
  }

  while (millis() - startTime < 3000) {
    if (ackByteID > 9) {
      Serial.println(" (SUCCESS!)");
      return true;
    }
    if (Serial1.available()) {
      b = Serial1.read();
      if (b == ackPacket[ackByteID]) {
        ackByteID++;
        Serial.print(b, HEX);
      }
      else {
        Serial.print("[");
        Serial.print(b, HEX);
        Serial.print("]");
        ackByteID = 0;
      }
    }
  }
  Serial.println(" (FAILED!)");
  return false;
}
