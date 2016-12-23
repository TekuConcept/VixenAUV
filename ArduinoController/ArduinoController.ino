/**
 * ArduinoController will successfully compile on Arduino IDE 1.6.7
 * with AVR 1.6.9 and SAM 32-bit 1.6.7
 */

#if defined(__AVR_ATmega328P__)
#define UNO
#define GARBAGE 240
#elif defined(__AVR_ATSAM3X8E__)
#define DUE
#define GARBAGE 0
#endif

#include "Accessories/LedController.h"
#include "Accessories/LightController.h"
#include "Accessories/PingController.h"
#include "Accessories/VoltageController.h"
#include "KillSwitchController.h"
#include "EscController.h"
#include "StartController.h"
#include "Dummy.h"

#include "PinMap.h"
#include "Thrusters/ThrusterController.h"

#define KILL_ADDR 9
#define CONTROLLER_CNT 10u
class IController* controllers[CONTROLLER_CNT];

void setup() {
  Serial.begin(115200);
  SerialEx::writeString("Ready!", 6);

  HW_configure(
    LEFT_FORWARD, RIGHT_FORWARD,
    LEFT_STRAFE,  RIGHT_STRAFE,
    FRONT_DIVE,   BACK_DIVE
  );
  controllers[0] = new Thruster();
  controllers[1] = new ThrusterModifier();
  controllers[2] = new ThrusterTuner();
  controllers[3] = new EscController();
  controllers[4] = new LedController();
  controllers[5] = new PingController();
  controllers[6] = new LightController();
  controllers[7] = new VoltageController();
  controllers[8] = new StartController();

  controllers[KILL_ADDR] =
      new KillSwitchController(controllers, CONTROLLER_CNT, KILL_ADDR);
  attachInterrupt(
    digitalPinToInterrupt(KILL_PIN), 
    [](){((KillSwitchController*)controllers[KILL_ADDR])->isr();},
    CHANGE
  );
  
  // At baud rates around 115200, RX buffer gets filled with
  // garbage in the beginning. To fix this, we just clear it
  // before proceeding. Luckilly the guarbage is consistant!
  // The host will give an ACKNO to begin thus exiting  this
  // infinite loop.
  while((!Serial.available())||(Serial.read()==GARBAGE));
}

void loop() {
  if(Serial.available()){
    uint8_t controllerNumber = Serial.read();
    if(controllerNumber < CONTROLLER_CNT)
      // only execute if a command exists
      controllers[controllerNumber]->execute();
  }
}
