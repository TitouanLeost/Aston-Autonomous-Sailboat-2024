#include <time.h>

#include <Observer.h>
#include <Supervisor.h>
#include <Controller.h>
#include <Logger.h>

Observer obs;
Supervisor sp;
CONTROLLER ctrl;
Logger logger;

unsigned long last_time = 0;


void anemometerRotation() {obs.ws()->rotation();}


void setup() {
    Serial.begin(9600);
    obs.init();
    sp.init(&obs, &ctrl);
    ctrl.init();
    logger.init(&obs);

    attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), anemometerRotation, FALLING);

    last_time = millis();
    // while(millis() - last_time < 5000) {
    //     obs.updateSensors();
    //     logger.update();
    // }
    // logger.close();
    // Serial.println("finished");
}


void loop() {
    obs.updateSensors();
    sp.updateMission();
    ctrl.updateServos();
    logger.update();

    // if (millis() - last_time > 200) {
    //     Serial.print("Yaw (filtered): ");
    //     Serial.print(obs.cmps()->getYaw());
    //     Serial.print("     Yaw (raw): ");
    //     Serial.print(obs.cmps()->getYawRaw());
    //     Serial.print("     Pitch: ");
    //     Serial.print(obs.cmps()->getPitch());
    //     Serial.print("     Roll: ");
    //     Serial.println(obs.cmps()->getRoll());

        // Serial.print("Satellites: ");
        // Serial.print(obs.gps()->getSatellites());
        // Serial.print("     Lat: ");
        // Serial.print(obs.gps()->getLat());
        // Serial.print("     Lon: ");
        // Serial.print(obs.gps()->getLon());
        // Serial.print("     Course: ");
        // Serial.print(obs.gps()->getCourse());
        // Serial.print("     Speed: ");
        // Serial.print(obs.gps()->getSpeed());
        // Serial.print("     Date: ");
        // Serial.print(obs.gps()->getDate());
        // Serial.print("     Time: ");
        // Serial.println(obs.gps()->getTime());

        // Serial.print("Wind speed: ");
        // Serial.print(obs.ws()->getWindSpeed());
        // Serial.print("     Wind direction: ");
        // Serial.println(obs.wd()->getWindDirection());

    //     Serial.println("------------------------------- \n");

    //     last_time = millis();
    // }

}