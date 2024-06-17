#include <time.h>

#include <Observer.h>
#include <Supervisor.h>
#include <Controller.h>
#include <Logger.h>
#include <RCReceiver.h>

Observer obs;
Controller ctrl;
Supervisor sp;
Logger logger;
RCReceiver rc;

unsigned long last_time = 0;


void anemometerRotation() {obs.ws()->rotation();}
void checkRC() {rc.checkRC();}


void setup() {
    Serial.begin(9600);

    rc.init();
    attachInterrupt(digitalPinToInterrupt(RUDDER_CH_PIN), checkRC, CHANGE);
    delay(2000);
    // This bloc of code is used to wait for the RC receiver to be ready.
    // The first two while loops are passed when the RC Receiver is wired on the Arduino board.
    // The last two while loops are passed when the remote controller is switched on then off.
    // It allows to wired all the sensors on the board directly in the boat and then launch the program only when the user is ready.
    while(!rc.isReceiving());
    while(rc.isReceiving());
    while(!rc.isReceiving());
    while(rc.isReceiving());

    obs.init();
    ctrl.init(&obs);
    sp.init(&obs, &ctrl, &rc);
    logger.init(&obs, &ctrl, &rc);

    attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), anemometerRotation, FALLING);

    last_time = millis();
}


void loop() {
    obs.updateSensors();
    sp.updateMission();
    ctrl.updateServos();
    logger.update();

    if (millis() - last_time > 200) {
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
        Serial.print(obs.gps()->getLat(), 6);
        Serial.print("     Lon: ");
        Serial.print(obs.gps()->getLon(), 6);
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
        Serial.print("     Wind direction (filtered): ");
        Serial.print(obs.wd()->getWindDirection());
        Serial.print("     Wind direction (raw): ");
        Serial.print(obs.wd()->getRawWindDirection());
        Serial.print("     True wind direction: ");
        Serial.println(obs.getTrueWindAngle());

        Serial.println("------------------------------- \n");

        last_time = millis();
    }

}