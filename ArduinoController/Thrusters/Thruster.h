/**
 * Created by TekuConcept on 8/3/2016.
 */

#ifndef THRUSTER_H
#define THRUSTER_H

#include "../SerialTools.h"
#include "../IController.h"
#include "C_Thrusters.h"

class Thruster : public IController {
public:
  Thruster() {}
  
  void execute() {
    // Serial.println("Thruster Executed!");
    while(Serial.available() < 1);
    // select thruster and access mode
    uint8_t index = Serial.read();
    if(index == HW_SOFT_RESET) {
      HW_soft_reset();
      return;
    }
    else if(index == HW_HARD_RESET) {
      HW_hard_reset();
      return;
    }

    while(Serial.available() < 1);
    uint8_t rdwr = Serial.read();
    if(rdwr == HW_RD) {
      #ifdef DEBUG
      Serial.println(HW_get_thruster(index));
      #else
      SerialEx::writeUShort(HW_get_thruster(index));
      #endif
    }
    else {
      while(Serial.available() < 2);
      uint16_t value = SerialEx::readUShort();
      HW_set_thruster(index, value);
    }
  }
  
  void kill() {
    HW_soft_reset();
  }
};

#endif