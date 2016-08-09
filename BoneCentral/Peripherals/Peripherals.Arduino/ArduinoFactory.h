/**
 * Created by TekuConcept on 8/4/2016.
 */

#ifndef ARDUINO_FACTORY_H
#define ARDUINO_FACTORY_H

#include "ThrusterInterface.h"
#include "PowerInterface.h"
#include "Serial.h"
#include "ArduinoMap.h"
#include <iostream>

class ArduinoFactory {
public:
	ArduinoFactory() {
		// read ready string, clearing the input buffer
		std::cout << arduino.readString() << std::endl;
		arduino.writeByte(1); // acknowledge
	}

	void pingArduino() {
		arduino.writeByte(PING_CONTROL);
		std::cout << arduino.readString() << std::endl;
	}

	Drive getEngine() {
		Drive engine(&arduino);
		return engine;
	}

	Power getPowerGrid() {
		Power grid(&arduino);
		return grid;
	}

private:
	Serial arduino;
};

#endif