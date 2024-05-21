#ifndef SD_H
#define SD_H

#include <SD.h>
#include <SPI.h>
#include <TinyGPSPlus.h>

#define SDCARD_CSPIN 12 
#define SDCARD_MISO 39
#define SDCARD_MOSI 14
#define SDCARD_CLK 40

extern SPIClass sdCardSPI;
extern bool sdcardMounted;

bool openSdCard();
void closeSdCard();
void saveGpsDataToSdCard(TinyGPSPlus &gps);

#endif