/**
 * Created by TekuConcept on 8/3/2016.
 */

#ifndef MOVE_MODIFIER_H
#define MOVE_MODIFIER_H

#include "../SerialTools.h"
#include "../IController.h"
#include "C_Thrusters.h"

class ThrusterModifier : public IController {
public:
	ThrusterModifier() {}

	void execute() {
		// Serial.println("ThrusterModifier Executed!");
		while(Serial.available() < 1);
		
		// If the modifier calls for a reset
		// then reset the system and return.
		uint8_t index = Serial.read();
		if(index == HW_MOD_RESET) {
			HW_reset_modifiers();
			return;
		}

		while(Serial.available() < 1);

		// How are we going to access the modifier?
		uint8_t rdwr  = Serial.read();
		if(rdwr == HW_RD) {
			// Read current modifier value.
			// Serial.println(HW_get_modifier(index));
			SerialEx::writeFloat(HW_get_modifier(index));
		}
		else{
			while(Serial.available() < 4);
			// Update the current modifier with a new value.
			// (this also updates the thrusters' output)
			float value  = SerialEx::readFloat();
			HW_set_modifier(index, value);
		}
	}

	void kill() {}
};

#endif