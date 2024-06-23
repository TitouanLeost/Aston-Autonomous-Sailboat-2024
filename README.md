# Aston Autonomous Sailboat 2024

The purpose of this project is to provide a framework for testing different types of algorithms to **control an autonomous sailboat**. To do this, the code is loaded onto an **Arduino MEGA 2560**. The boat is controlled using two servomotors, one of which adjusts the maximum sail angle while the other controls the rudder angle. A series of sensors (IMU, GPS, anemometer) inform the Arduino of the boat's status.


## Hardware

### Actuators


### Sensors


### Wiring


## Quickstart Guide

### Requirements

The following arduino libraries are required:

* TinyGPSPlus (v1.0.3)
* Adafruit PWM Servo Driver Library (v3.0.2)
* SD (v1.2.4)
* SoftwareSerial *[installed by default with Arduino IDE]*
* Wire *[installed by default with Arduino IDE]*
* SPI *[installed by default with Arduino IDE]*

### Build the Project

```console
git clone https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024.git
```

### Add the Libraries

Copy all the folders inside libraries/ into your Arduino libraries folder:

```console
cd Aston-Autonomous-Sailboat-2024
cp -r libraries/* ~/Arduino/libraries/
```

You can now build the project with Arduino IDE. To do this, open the file [Sailboat.ino](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/Sailboat/Sailboat.ino) and upload it to your Arduino board.


## Detailed Structure of the Code

![Full class diagram](docs/diagrams/out/classDiagram/classDiagram2.png)

## Additional Tools

In the [tools](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools) folder you will find a set of utility codes used for logging data.  

### Reading Log from an SD Card

First of all [read_sd_card.ino](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools/read_sd_card/read_sd_card.ino) allows you to **read a file on an SD card connected to the Arduino board**. This is usefull if you can't load the SD card directly into your computer or if you want to save time. **You will need to fill the name of your file wich will be "LOG/DDMMhhmm.txt"** *(DD: day, MM: month, hh: hour, mm: minute of the beginning of the experiment)*.  
Then, **you can execute [sd_card_reading.py](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools/sd_card_reading.py)** to **save the log** in a file which will be **located in /logs/DDMMYY/hhmmss.txt** *(YY: year, ss: second of the beginning of the experiment)*.  

---

**Here are the complete instructions:**

1. Plug your Arduino MEGA 2560 to your computer.
2. Change the name of the file you want to read in [read_sd_card.ino](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools/read_sd_card/read_sd_card.ino).
3. Upload [read_sd_card.ino](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools/read_sd_card/read_sd_card.ino) to the Arduino board.
4. Once the file is read, close Arduino IDE.
5. Execute [sd_card_reading.py](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools/sd_card_reading.py).
6. Your log file is saved in /logs/DDMMYY/hhmmss.txt.


### Displaying the Logs

To **display different plots of the saved log**, you can **execute [display_log.py](https://github.com/TitouanLeost/Aston-Autonomous-Sailboat-2024/tree/main/tools/display_log.py)**. The images will be **stored as png in /logs/plots/DDMMYY/hhmmss/** *(DD: day, MM: month, YY: year, hh: hour, mm: minute, ss: second of the beginning of the experiment)*.

## Complete Documentation

See the doc on https://titouanleost.github.io/Aston-Autonomous-Sailboat-2024/ 