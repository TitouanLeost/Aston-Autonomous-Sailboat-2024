#include <SD.h>
#include <SPI.h>


String filename = "TEST.TXT";  // Put the name of the file you want to read here
File myFile;

int pinCS = 53;

void setup() {
      
    Serial.begin(31250);
    pinMode(pinCS, OUTPUT);

    // SD Card Initialization
    if (!SD.begin()){
        Serial.println("SD card initialization failed");
        return;
    }
    
    // Reading the file
    myFile = SD.open(filename);
    if (myFile) {
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        Serial.write("END");
        myFile.close();
    }
    else {
        Serial.print("error opening "); Serial.println(filename);
    }
}
  

void loop() {
  // empty
}
