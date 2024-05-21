#ifndef GPS_H
#define GPS_H

#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#define GPS_BAUDRATE 9600
#define TX_PIN 1
#define RX_PIN 2

bool readGpsData(TinyGPSPlus &gps, HardwareSerial &ss);
bool connectGps(TinyGPSPlus &gps, HardwareSerial &ss);
void sendGpsLowPowerCommand(HardwareSerial &ss);

#endif