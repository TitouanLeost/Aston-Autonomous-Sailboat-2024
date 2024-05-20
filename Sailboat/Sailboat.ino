#include <time.h>
#include <Observer.h>

Observer obs;
unsigned long last_time = 0;


void anemometerRotation() {obs.ws()->rotation();}


void setup() {
    Serial.begin(9600);
    obs.init();

    attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), anemometerRotation, FALLING);

    last_time = millis();
}


void loop() {
    obs.updateSensors();
    obs.fusion();

    if (millis() - last_time > 1000) {
        Serial.print("Yaw (filtered): ");
        Serial.print(obs.cmps()->getYaw());
        Serial.print("     Yaw (raw): ");
        Serial.print(obs.cmps()->getYawRaw());
        Serial.print("     Pitch: ");
        Serial.print(obs.cmps()->getPitch());
        Serial.print("     Roll: ");
        Serial.println(obs.cmps()->getRoll());

        Serial.print("Satellites: ");
        Serial.print(obs.gps()->getSatellites());
        Serial.print("     Lat: ");
        Serial.print(obs.gps()->getLat());
        Serial.print("     Lon: ");
        Serial.print(obs.gps()->getLon());
        Serial.print("     Course: ");
        Serial.print(obs.gps()->getCourse());
        Serial.print("     Speed: ");
        Serial.print(obs.gps()->getSpeed());
        Serial.print("     Date: ");
        Serial.print(obs.gps()->getDate());
        Serial.print("     Time: ");
        Serial.println(obs.gps()->getTime());

        Serial.print("Wind speed: ");
        Serial.println(obs.ws()->getWindSpeed());

        last_time = millis();
    }

}