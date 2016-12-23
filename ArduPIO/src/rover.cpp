/**
 * Created by TekuConcept on 12/22/2016.
 */
#include <Arduino.h>
#include "Dummy.h"
#include "MotorDriver.h"
#include "KillController.h"
#include "PingController.h"
#include "Config.h"

#define CONTROLLER_CNT 3u
class IController* controllers[CONTROLLER_CNT];

void setup() {
    Serial.begin(BAUD);
    SerialEx::writeString("Ready!", 6);
    
    controllers[0] = new KillController(controllers, CONTROLLER_CNT);
    controllers[1] = new PingController();
    controllers[2] = new MotorDriver();

    while((!Serial.available())||(Serial.read()==GARBAGE));
}

void loop() {
    if(Serial.available()){
        uint8_t controllerNumber = Serial.read();
        if(controllerNumber < CONTROLLER_CNT)
            controllers[controllerNumber]->execute();
    }
}
