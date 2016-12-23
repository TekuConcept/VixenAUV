/**
 * Created by TekuConcept on 8/4/2016.
 */

#ifndef ARDUINO_FACTORY_H
#define ARDUINO_FACTORY_H

#include <iostream>

#include "Serial.h"
#include "ArduinoMap.h"
#include "ThrusterInterface.h"

class ArduinoFactory {
public:
	ArduinoFactory() : arduino("/dev/ttyUSB0", BAUD) {
		// read ready string, clearing the input buffer
		std::cout << arduino.readString() << std::endl;
		arduino.writeByte(ACKNO); // acknowledge
	}

	void pingArduino() {
		arduino.writeByte(PING_CONTROL);
		std::cout << arduino.readString() << std::endl;
	}

	Drive getEngine() {
		Drive engine(&arduino);
		return engine;
	}

private:
	Serial arduino;
};

#endif