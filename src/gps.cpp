#include "gps.h"

#define GPS_LOW_POWER_COMMAND "$PMTK161,0*28\r\n" // Low power mode for grove GPS module AIR530

unsigned long previousTime; 


bool readGpsData(TinyGPSPlus &gps, HardwareSerial &ss) 
{
    unsigned long startTime = millis();
    while (ss.available() > 0 && (millis() - startTime) < 1000) // While there is data available from the GPS
    {
        if (gps.encode(ss.read())) // If the GPS data is successfully encoded
            return true;
    }

    return false;
}


bool connectGps(TinyGPSPlus &gps, HardwareSerial &ss) {
  ss.begin(GPS_BAUDRATE, SERIAL_8N1, TX_PIN, RX_PIN); // Begin the serial communication with the GPS
  delay(1000);

  int startTime = millis();
  while (ss.available() > 0 || (millis() - startTime) < 1000 ) {
    if (gps.encode(ss.read())) {
      return true;
    }
  }
  return false;
}


void sendGpsLowPowerCommand(HardwareSerial &ss) {
    ss.print(GPS_LOW_POWER_COMMAND);
    delay(100); // Wait for the GPS to process the command
}