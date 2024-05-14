#include <CMPS12.h>


CMPS12 cmps;

void setup() {
    Serial.begin(9600);
    cmps.init();
}


void loop() {
    cmps.update();
    Serial.print("Angle 8: ");
    Serial.print(cmps.getAngle8());
    Serial.print("   Angle full: ");
    Serial.print(cmps.getAngle());
    Serial.print("   Pitch: ");
    Serial.print(cmps.getPitch());
    Serial.print("   Roll: ");
    Serial.println(cmps.getRoll());
    delay(1000);
}