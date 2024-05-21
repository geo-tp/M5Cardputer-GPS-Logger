#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include "display.h"
#include "sd.h"
#include "gps.h"


TinyGPSPlus gps; // Create a TinyGPSPlus object
HardwareSerial ss(2); // Create a HardwareSerial object on UART2

unsigned long previousMillis = millis(); // Stores the last time the data was saved
const long interval = 60000; // Interval for saving data (1 minute)
const long gpsInterval = 10000; // Interval to let the GPS get data

bool isSdSaving = true; // Flag to track whether SD saving is active
bool isScreenOn = false; // Flag to track whether screen is active 
bool isSleepMode = false; // Flag to set the mode : NORMAL or SLEEP


void handleModeSelection() {
      while (true) {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isChange()) {
          if (M5Cardputer.Keyboard.isPressed()) {

            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
            if (status.enter) {
                break;
            }
            
            else if (M5Cardputer.Keyboard.isKeyPressed(';')) {
                isSleepMode = (isSleepMode == 0) ? 1 : 0;
                displaySelectionScreen(isSleepMode);
              } 
            
            else if (M5Cardputer.Keyboard.isKeyPressed('.')) 
                isSleepMode = (isSleepMode == 1) ? 0 : 1;
                displaySelectionScreen(isSleepMode);
            } 
            
            delay(100);
        }
    }
}


void normalMode() {

  readGpsData(gps, ss);
  displayNormalScreen(gps);

  // Gérer les changements de l'état du clavier
  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

      // Save on SD On/Off
      if (status.enter) {
        isSdSaving = !isSdSaving;
        displaySaveState(isSdSaving);
      }

      // Screen On/Off
      else if (M5Cardputer.Keyboard.isKeyPressed('s')) {
        isScreenOn = !isScreenOn;
        if (isScreenOn) {
          M5Cardputer.Display.sleep();
        } else {
          M5Cardputer.Display.wakeup();
        }
      }

      else if (M5Cardputer.Keyboard.isKeyPressed('-')) {
          displayDecrementBrightness();
      }

      else if (M5Cardputer.Keyboard.isKeyPressed('=')) {
        displayIncrementBrightness();
      }

      delay(200); // Avoid 2 very close inputs
    }
  }

  // Sauvegarder les données GPS si l'option de sauvegarde est activée
  if (isSdSaving) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Mettre à jour l'heure de la dernière sauvegarde
      saveGpsDataToSdCard(gps);
    }
  }
}


void sleepMode() {
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            if (status.enter) {
              bool gpsState;
              do { // We can't run without a GPS module
                gpsState = connectGps(gps, ss);
                displayStartSleepScreen(gpsState);
                delay(1000);
              } while (!gpsState);

              // The Sleep mode loop that lasts forever
              while (true) {
                unsigned long startMillis = millis();
                while (millis() - startMillis < gpsInterval) { // We let time to get data
                  readGpsData(gps, ss);
                }
                saveGpsDataToSdCard(gps);
                esp_light_sleep_start();  
              }
            }
        }
    }
}


/* ###################################################################################################  */


void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg);
  M5.Power.begin();

  displayWelcomeScreen();

  bool sdState = openSdCard();
  displaySdCardState(sdState);

  while (!sdState) { // We cant run without a SD card
    sdState = openSdCard(); 
    displaySdCardState(sdState);
    delay(1000);
  }

  bool gpsState = connectGps(gps, ss);
  displayGpsState(gpsState);
  
  delay(4000);

  displaySelectionScreen(isSleepMode);
  handleModeSelection();

  displayClear();

  if (isSleepMode) {
    sendGpsLowPowerCommand(ss); // Low power for grove GPS AIR530
    esp_sleep_enable_timer_wakeup(interval * 1000 - gpsInterval * 1000 ); // Enable timer wakeup in us
    displaySleepScreen();
  } else {
    if (!gpsState) {
      isSdSaving = false;
    }
    displaySaveState(isSdSaving);
  }
}


void loop() {
  M5Cardputer.update();

  if (isSleepMode) {
    sleepMode();
  } else {
    normalMode();
  }
}
