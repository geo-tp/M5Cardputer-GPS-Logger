#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Cardputer.h>
#include <TinyGPSPlus.h>

void displayNormalScreen(TinyGPSPlus &gps);
void displaySaveState(bool isSdSaving);
void displayWelcomeScreen();
void displaySleepScreen();
void displaySelectionScreen(bool isSleepMode);
void displayStartSleepScreen(bool gpsState);
void displayDecrementBrightness();
void displayIncrementBrightness();
void displayGpsState(bool state);
void displaySdCardState(bool state);
void displayClear();
void displayNoGps();

#endif