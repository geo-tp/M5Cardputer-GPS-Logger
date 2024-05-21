#include "sd.h"

#define SAVE_FILE_PATH "/gps_data.csv"


SPIClass sdCardSPI;
bool sdCardMounted = false;


bool openSdCard() {
    sdCardSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CSPIN);
    delay(10);

    if (!SD.begin(SDCARD_CSPIN, sdCardSPI)) {
        sdCardMounted = false;
        return false;
    } else {
        sdCardMounted = true;
    }

    return sdCardMounted;
}


void closeSdCard() {
    SD.end();
    sdCardSPI.end();
}


void saveGpsDataToSdCard(TinyGPSPlus &gps) // Function to save the GPS data to a CSV file
{
    File file = SD.open(SAVE_FILE_PATH, FILE_APPEND); // Open the file for appending
    if (file) {
        file.printf("%.8f,%.8f,%.2f,%d,%02d/%02d/%02d,%02d:%02d:%02d\n",
                    gps.location.lat(),
                    gps.location.lng(),
                    gps.speed.kmph(),
                    gps.satellites.value(),
                    gps.date.day(),
                    gps.date.month(),
                    gps.date.year(),
                    gps.time.hour(),
                    gps.time.minute(),
                    gps.time.second());
        file.close();
        delay(300);
    }
}
