/**
 * Created by TekuConcept on 8/4/2016.
 */

#ifndef THRUSTER_INTERFACE_H
#define THRUSTER_INTERFACE_H

#include "Serial.h"
#include <iostream>

#define MSG(x) if(verbose_) std::cout << x
#define MSGN(x) if(verbose_) std::cout << x << std::endl

class Drive {
public:
	Drive() {
		Drive(NULL);
	}
	~Drive() {
		kill();
	}

	void move(float value) {
		_move = value;
		MSG("moving: " << value);
		_setMotor(_move, _rotate);
	}

	void yaw(float value) {
		_rotate = value;
		MSG("yawing: ");
		_setMotor(_move, _rotate);
	}

	void kill() {
		if(arduino) {
			MSG("killing... ");
			const char* data = "\x00";
			arduino->writeData((char*)data, 1);
			MSGN("Finished!");
		}
	}

	void debug() {
		MSGN("debug info...");
		readThrusters();
	}
	
	void verbose(bool flag) {
		verbose_ = flag;
	}

#ifndef SWIG
	Drive(Serial* in) {
		arduino = in;
		verbose_ = false;
		_move = 0.0f;
		_rotate = 0.0f;
	}
#endif

private:
	float _move,_rotate;
	Serial *arduino;
	bool verbose_;

	void readThrusters() {
		if(arduino) {
			const char* data = "\x02\x00";
			arduino->writeData((char*)data, 2);
			MSGN("Left  Motor: " << arduino->readFloat());
			MSGN("Right Motor: " << arduino->readFloat());
		}
	}
	
	void _setMotor(float move, float rotate) {
		if(arduino) {
			const char* data = "\x02\x01";
			arduino->writeData((char*)data, 2);
			arduino->writeFloat(_move);
			arduino->writeFloat(_rotate);
			MSGN(" ...Finished!");
		}
	}
};

#endif