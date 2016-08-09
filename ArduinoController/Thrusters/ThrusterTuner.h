/**
 * Created by TekuConcept on 8/3/2016.
 */

#ifndef THRUSTER_TUNER_H
#define THRUSTER_TUNER_H

#include "../SerialTools.h"
#include "../IController.h"
#include "C_Thrusters.h"

class ThrusterTuner : public IController {
public:
	ThrusterTuner() {}

	void execute() {
		// Serial.println("ThrusterTuner Executed!");
		while(Serial.available() < 1);
		uint8_t index = Serial.read();

		if(index == HW_TRIM_RESET) {
			HW_reset_trim();
			return;
		}

		while(Serial.available() < 1);
		uint8_t rdwr = Serial.read();
		if(rdwr == HW_RD) {
			// Serial.println(HW_get_trim(index));
			SerialEx::writeFloat(HW_get_trim(index));
		}
		else {
			while(Serial.available() < 4);
			float value = SerialEx::readFloat();
			HW_set_trim(index, value);
		}
	}

	void kill() {}
};

#endif