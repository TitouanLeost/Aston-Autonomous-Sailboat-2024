#include <time.h>
#include <Observer.h>
#include <Controller.h>

Observer obs;
Controller ctrl;
unsigned long last_time = 0;


void anemometerRotation() {obs.ws()->rotation();}


void setup() {
    Serial.begin(9600);
    obs.init();
    delay(5000);
    ctrl.init();
    delay(1000);

    attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), anemometerRotation, FALLING);

    last_time = millis();
}


void loop() {
    obs.updateSensors();
    obs.fusion();

    if (millis() - last_time > 500) {
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
        Serial.print(obs.ws()->getWindSpeed());
        Serial.print("     Wind direction: ");
        Serial.println(obs.wd()->getWindDirection());

        last_time = millis();
    }

}