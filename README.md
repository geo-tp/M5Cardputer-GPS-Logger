# M5Cardputer GPS Logger

This project is a GPS logger using the M5Cardputer platform. It reads GPS data, displays it on the screen, and optionally saves the data to an SD card. The device operates in two modes: NORMAL mode and SLEEP mode. The SLEEP mode conserves power while still logging GPS data.

- <b>NORMAL:</b> Displays the GPS data on the screen every 3 seconds while saving the GPS data to the SD card every minute (can be turned off).

- <b>SLEEP:</b> Saves the GPS data to the SD card every minute before entering light sleep mode. The Cardputer's screen is turned off, and it appears to be OFF.

## Installation

- <b>M5Burner</b> : Search into M5CARDPUTER section and simply burn it
- <b>Old school</b> : Build or take the firmware.bin from the github release and flash it


## Usage 


- You will need a UART GPS module connected to the M5Cardputer and an inserted SD card.
This has been tested with the [Grove GPS module](https://wiki.seeedstudio.com/Grove-GPS-Air530/)

- Select NORMAL or SLEEP mode

- The GPS data will be saved in the file `gps_data.csv` at the root of the SD card.

## Controls

For NORMAL mode
- <b> OK </b> Toggles SD card  on/off.
- <b>S</b> Toggles screen on/off.
- <b>- and =</b> Adjusts brightness.