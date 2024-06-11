#include <time.h>

#include <Observer.h>
#include <Supervisor.h>
#include <Controller.h>
#include <Logger.h>
#include <RCReceiver.h>

Observer obs;
Supervisor sp;
Controller ctrl;
Logger logger;
RCReceiver rc;

unsigned long last_time = 0;


void anemometerRotation() {obs.ws()->rotation();}
void checkRC() {rc.checkRC();}


void setup() {
    Serial.begin(9600);
    obs.init();
    rc.init();
    sp.init(&obs, &ctrl, &rc);
    ctrl.init();
    // logger.init(&obs);

    pinMode(RUDDER_CH_PIN, INPUT);
    pinMode(SAIL_CH_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), anemometerRotation, FALLING);
    attachInterrupt(digitalPinToInterrupt(RUDDER_CH_PIN), checkRC, CHANGE);

    last_time = millis();
}


void loop() {
    obs.updateSensors();
    rc.update();
    sp.updateMission();
    ctrl.updateServos();
    // logger.update();

    // Serial.println(rc.isReceiving());
    // Serial.print("Rudder: "); Serial.print(rc.getCmdRudder()); Serial.print("     Sail: "); Serial.println(rc.getCmdSail());

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