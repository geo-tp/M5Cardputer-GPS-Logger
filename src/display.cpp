#include "display.h"

const int lineSpacing = 20; // Set the line spacing for the display
const int leftMargin = 10; // Set the left margin for the display
const int infoAreaTop = 0; // Top position of the GPS info area
const int infoAreaHeight = 100; // Height of the GPS info area
int lastSecond = -1;
int brightness = M5Cardputer.Display.getBrightness();


void displayWelcomeScreen() {
    M5Cardputer.Display.setRotation(1);

    M5Cardputer.Display.drawRect(20, 20, 200, 40, TFT_LIGHTGRAY);
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.setCursor(32, 28);
    M5Cardputer.Display.setTextSize(3.4);
    M5Cardputer.Display.printf("GPS to SD"); 
   
    M5Cardputer.Display.setTextSize(1.2);
    M5Cardputer.Display.setCursor(20,70);
    M5Cardputer.Display.setTextColor(TFT_ORANGE);
    M5Cardputer.Display.printf("Save GPS data");
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.printf(" to your SD card");
    M5Cardputer.Display.setCursor(26, 85);
    M5Cardputer.Display.printf("in a .csv file");
    M5Cardputer.Display.setTextColor(TFT_ORANGE);
    M5Cardputer.Display.printf(" every minute");
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    delay(1000);
}

void displaySaveState(bool isSdSaving) {
    M5Cardputer.Display.fillRect(180, infoAreaHeight, M5Cardputer.Display.width(), M5Cardputer.Display.height(), TFT_BLACK); // Reset area

    M5Cardputer.Display.drawRect(20, 104, 150, 1, TFT_DARKGRAY); // delimiter

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(20, 110);
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.printf("Log on SD each min [ ok ]");

    if (isSdSaving) {
        M5Cardputer.Display.drawRect(178, 103, 35, 27, TFT_GREEN);
        M5Cardputer.Display.setCursor(189, 113);
        M5Cardputer.Display.setTextColor(TFT_GREEN);
        M5Cardputer.Display.printf("ON");
    } else {
        M5Cardputer.Display.drawRect(178, 103, 35, 27, TFT_RED);
        M5Cardputer.Display.setCursor(187, 113); 
        M5Cardputer.Display.setTextColor(TFT_RED);
        M5Cardputer.Display.printf("OFF");
    }
    M5Cardputer.Display.setCursor(20,  122);
        M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.printf("Turn off the screen [ S ]");
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY); 
}


void displaySelectionScreen(bool isSleepMode) {
    M5Cardputer.Display.clear();
    M5Cardputer.Display.setTextSize(1.5);
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.setCursor(70, 10);
    M5Cardputer.Display.printf("Select Mode:");
    M5Cardputer.Display.setTextSize(3);

    // Draw Normal Mode Button
    if (isSleepMode == false) {
        M5Cardputer.Display.fillRect(20, 30, 200, 40, TFT_LIGHTGRAY);
        M5Cardputer.Display.drawRect(20, 30, 200, 40, TFT_BLACK);
        M5Cardputer.Display.setTextColor(TFT_BLACK);
    } else {
        M5Cardputer.Display.fillRect(20, 30, 200, 40, TFT_BLACK);
        M5Cardputer.Display.drawRect(20, 30, 200, 40, TFT_LIGHTGRAY);
        M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    }
    M5Cardputer.Display.setCursor(70, 40);
    M5Cardputer.Display.printf("Normal");

    // Draw Sleep Mode Button
    if (isSleepMode == true) {
        M5Cardputer.Display.fillRect(20, 80, 200, 40, TFT_LIGHTGRAY);
        M5Cardputer.Display.drawRect(20, 80, 200, 40, TFT_BLACK);
        M5Cardputer.Display.setTextColor(TFT_BLACK);
    } else {
        M5Cardputer.Display.fillRect(20, 80, 200, 40, TFT_BLACK);
        M5Cardputer.Display.drawRect(20, 80, 200, 40, TFT_LIGHTGRAY);
        M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    }
    M5Cardputer.Display.setCursor(77, 90);
    M5Cardputer.Display.printf("Sleep");
}


void displayNormalScreen(TinyGPSPlus &gps) {
    int currentLine = 0;
    int margin = 20;
    int spacing = 17;

    int currentSecond = gps.time.second();

    // Vérifier si 3 secondes se sont écoulées depuis la dernière exécution
    if ((currentSecond < lastSecond && (currentSecond + 60 - lastSecond) < 3) || 
        (currentSecond >= lastSecond && (currentSecond - lastSecond) < 3)) {
        
        if (lastSecond != -1) // if -1, it's the first render
            return;
    }

    lastSecond = currentSecond;

    M5Cardputer.Display.fillRect(0, infoAreaTop, M5Cardputer.Display.width(), infoAreaHeight, TFT_BLACK); // Clear the info area
    M5Cardputer.Display.setTextSize(2);

    M5Cardputer.Display.setCursor(margin, spacing * currentLine++);
    M5Cardputer.Display.printf("Lat: %.8f", gps.location.lat()); // Print the latitude to the LCD

    M5Cardputer.Display.setCursor(margin, spacing * currentLine++);
    M5Cardputer.Display.printf("Long: %.8f", gps.location.lng()); // Print the longitude to the LCD

    M5Cardputer.Display.setCursor(margin, spacing * currentLine++); 
    M5Cardputer.Display.printf("Speed: %.2f km/h", gps.speed.kmph()); // Print the speed to the LCD

    M5Cardputer.Display.setCursor(margin, spacing * currentLine++);
    M5Cardputer.Display.printf("Satellites: %d", gps.satellites.value()); // Print the number of satellites to the LCD

    M5Cardputer.Display.setCursor(margin, spacing * currentLine++);
    M5Cardputer.Display.printf("Date: %02d/%02d/%02d", gps.date.day(), gps.date.month(), gps.date.year()); // Print the date to the LCD

    int hour = gps.time.hour() - 4; // Adjust the hour for the time zone
    if (hour < 0)
        hour += 24; // If the hour is negative, add 24

    M5Cardputer.Display.setCursor(margin, spacing * currentLine++);
    M5Cardputer.Display.printf("Time: %02d:%02d:%02d", hour, gps.time.minute(), gps.time.second()); // Print the time to the LCD
}


void displaySleepScreen() {
    M5Cardputer.Display.drawRect(15, 15, 210, 40, TFT_LIGHTGRAY);
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.setCursor(23, 23);
    M5Cardputer.Display.setTextSize(3.4);
    M5Cardputer.Display.printf("Sleep Mode"); 
   
    M5Cardputer.Display.setTextSize(1.5);
    M5Cardputer.Display.setCursor(42, 70); 
    M5Cardputer.Display.printf("Press");

    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.fillRect(91, 68, 27, 15, TFT_DARKGRAY);
    M5Cardputer.Display.printf(" OK ");

    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.printf("to start");

    M5Cardputer.Display.setTextSize(1); 
    M5Cardputer.Display.setCursor(26, 92);
    M5Cardputer.Display.printf("Save position on SD every 1 min");

    M5Cardputer.Display.fillRect(10, 108, 220, 15, TFT_RED);
    M5Cardputer.Display.setCursor(15, 112);
    M5Cardputer.Display.printf("The Cardputer will appear to be off");
}


void displayStartSleepScreen(bool gpsState) {
    M5Cardputer.Display.clear();
    M5Cardputer.Display.drawRect(1, 1, 239, 134, TFT_RED); // Red frame all over the screen
    M5Cardputer.Display.setTextSize(1);

    if (!gpsState)  {
        displayNoGps();
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setCursor(30, 77);
        M5Cardputer.Display.println("We can't proceed without a GPS");
        M5Cardputer.Display.setCursor(32, 92); 
        M5Cardputer.Display.println("Please plug it in to continue");
        return;
    }

    M5Cardputer.Display.setCursor(27, 60);
    M5Cardputer.Display.println("Cardputer will enter sleep mode");
    M5Cardputer.Display.setCursor(21, 73); 
    M5Cardputer.Display.println("Logging the position every minute");
    delay(1000);

    M5Cardputer.Display.setTextSize(3);
    M5Cardputer.Display.setCursor(73, 90);
    for (int i = 0; i < 5; i++) {
        M5Cardputer.Display.printf(".");
        delay(1000);
    }
    delay(3000);
    displayClear();
    M5Cardputer.Display.sleep(); // Turn off the display
    delay(1000);
}


void displayDecrementBrightness() {
        brightness -= 30;
        if (brightness < 0) brightness = 0;
        M5Cardputer.Display.setBrightness(brightness);
}


void displayIncrementBrightness() {
        brightness += 30;
        if (brightness > 255) brightness = 255;
        M5Cardputer.Display.setBrightness(brightness);
}


void displayGpsState(bool state) {
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.setTextSize(1.1);
    M5Cardputer.Display.setCursor(153, 105);
    M5Cardputer.Display.printf("GPS : ");

    if (state) {
        M5Cardputer.Display.setTextColor(TFT_GREEN);
        M5Cardputer.Display.printf("OK");
    } else {
        M5Cardputer.Display.setTextColor(TFT_RED);
        M5Cardputer.Display.printf("NO");
    }
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
}


void displaySdCardState(bool state) {
    M5Cardputer.Display.fillRect(35, 104, 220, 30, TFT_BLACK);
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
    M5Cardputer.Display.setTextSize(1.1);
    M5Cardputer.Display.setCursor(36, 105);
    M5Cardputer.Display.printf("SD Card : ");

    if (state) {
        M5Cardputer.Display.setTextColor(TFT_GREEN);
        M5Cardputer.Display.printf("MOUNTED");
    } else {
        M5Cardputer.Display.setTextColor(TFT_RED);
        M5Cardputer.Display.printf("   IS NOT MOUNTED");
    }

    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
}


void displayClear() {
    M5Cardputer.Display.clear();
}

void displayNoGps() {
    M5Cardputer.Display.setTextSize(3);
    M5Cardputer.Display.setTextColor(TFT_RED);
    M5Cardputer.Display.setCursor(65, 45);
    M5Cardputer.Display.printf("NO GPS");
    M5Cardputer.Display.setTextColor(TFT_LIGHTGRAY);
}