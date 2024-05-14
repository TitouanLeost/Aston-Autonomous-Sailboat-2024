#include <time.h>
#include <Observer.h>

Observer obs;
unsigned long last_time = 0;

void setup() {
    Serial.begin(9600);
    obs.init();
    Serial.println("init succesfull");

    last_time = millis();
}


void loop() {
    obs.updateSensors();
    obs.fusion();

    if (millis() - last_time > 100) {
        Serial.print("Yaw (filtered): ");
        Serial.print(obs.cmps().getYaw());
        Serial.print("     Yaw (raw): ");
        Serial.println(obs.cmps().getYawRaw());

        last_time = millis();
    }
}