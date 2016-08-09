/**
 * Created by TekuConcept on 8/4/2016.
 */

#ifndef THRUSTER_INTERFACE_H
#define THRUSTER_INTERFACE_H

#include "Serial.h"
#include <iostream>

class Drive {
public:
	Drive() {
		Drive(NULL);
	}
	~Drive() {
		kill();
	}

	void move(float value) {
		if(arduino) {
			if(verbose_) std::cout << "moving: " << value;
			const char* data = "\x01\x00\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(value);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void move2(float value) {
		if(arduino) {
			if(verbose_) std::cout << "moving2: " << value;
			const char* data = "\x01\x04\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(value);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void dive(float value) {
		if(arduino) {
			if(verbose_) std::cout << "diving: " << value;
			const char* data = "\x01\x02\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(value);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void yaw(float value) {
		if(arduino) {
			if(verbose_) std::cout << "yawing: " << value;
			const char* data = "\x01\x01\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(value);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void yaw2(float value) {
		if(arduino) {
			if(verbose_) std::cout << "yawing2: " << value;
			const char* data = "\x01\x05\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(value);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void pitch(float value) {
		if(arduino) {
			if(verbose_) std::cout << "pitching: " << value;
			const char* data = "\x01\x03\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(value);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void setForwardTrim(float left, float right) {
		if(arduino) {
			if(verbose_) std::cout << "setting forward trim: " << left << ":" << right;
			const char* data = "\x02\x00\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(left);
			data = "\x02\x01\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(right);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void setDiveTrim(float front, float back) {
		if(arduino) {
			if(verbose_) std::cout << "setting forward trim: " << front << ":" << back;
			const char* data = "\x02\x02\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(front);
			data = "\x02\x03\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(back);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void setStrafeTrim(float left, float right) {
		if(arduino) {
			if(verbose_) std::cout << "setting strafe trim: " << left << ":" << right;
			const char* data = "\x02\x04\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(left);
			data = "\x02\x05\x01";
			arduino->writeData((char*)data, 3);
			arduino->writeFloat(right);
			if(verbose_) std::cout << " ...Finished!" << std::endl;
		}
	}

	void kill() {
		if(arduino) {
			if(verbose_) std::cout << "killing... ";
			const char* data = "\x00\x06";
			arduino->writeData((char*)data, 2);
			if(verbose_) std::cout << "Finished!" << std::endl;
		}
	}

	void debug() {
		if(arduino) {
			std::cout << "debug info..." << std::endl;
			readThrusters();
			readModifiers();
			readTrim();
		}
	}
	
	void verbose(bool flag) {
		verbose_ = flag;
	}

#ifndef SWIG
	Drive(Serial* in) {
		arduino = in;
		verbose_ = false;
	}
#endif

private:
	Serial *arduino;
	bool verbose_;

	void readThrusters() {
		for(int i = 0; i < 6; i++) {
			arduino->writeByte(0); // controller
			arduino->writeByte(i); // thruster
			arduino->writeByte(0); // access mode
			std::cout << "Thruster " << i << ": " << arduino->readShort() << std::endl;
		}
	}

	void readModifiers() {
		for(int i = 0; i < 6; i++) {
			arduino->writeByte(1); // controller
			arduino->writeByte(i); // modifier
			arduino->writeByte(0); // access mode
			std::cout << "Modifier " << i << ": " << arduino->readFloat() << std::endl;
		}
	}

	void readTrim() {
		for(int i = 0; i < 6; i++) {
			arduino->writeByte(2); // controller
			arduino->writeByte(i); // trim index
			arduino->writeByte(0); // access mode
			std::cout << "Trim " << i << ": " << arduino->readFloat() << std::endl;
		}
	}
};

#endif