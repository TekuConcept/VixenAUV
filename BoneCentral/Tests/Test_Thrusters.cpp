/**
 * Created by TekuConcept on 8/3/2016.
 */

#include "Serial.h"
#define SUCCESS 0

void readThrusters(Serial *arduino) {
	for(int i = 0; i < 6; i++) {
		arduino->writeByte(0); // controller
		arduino->writeByte(i); // thruster
		arduino->writeByte(0); // access mode
		std::cout << "thruster " << i << ": " << arduino->readShort() << std::endl;
	}
}

void readModifiers(Serial *arduino) {
	for(int i = 0; i < 6; i++) {
		arduino->writeByte(1); // controller
		arduino->writeByte(i); // modifier
		arduino->writeByte(0); // access mode
		std::cout << "modifier " << i << ": " << arduino->readFloat() << std::endl;
	}
}

void readAll(Serial *arduino) {
    readThrusters(arduino);
    readModifiers(arduino);
}

void move(Serial *arduino, float value) {
    std::cout << "Move Modifier... " << std::flush;
	const char* data = "\x01\x00\x01";
	arduino->writeData((char*)data, 3);
	arduino->writeFloat(value);
	std::cout << "Finished!" << std::endl << std::flush;
}

void dive(Serial *arduino, float value) {
    std::cout << "Dive Modifier... " << std::flush;
	const char* data = "\x01\x02\x01";
    arduino->writeData((char*)data, 3);
	arduino->writeFloat(value);
	std::cout << "Finished!" << std::endl << std::flush;
}

void move2(Serial *arduino, float value) {
    std::cout << "Move2 Modifier... " << std::flush;
	const char* data = "\x01\x04\x01";
    arduino->writeData((char*)data, 3);
	arduino->writeFloat(value);
	std::cout << "Finished!" << std::endl << std::flush;
}

void yaw(Serial *arduino, float value) {
    std::cout << "Yaw Modifier... " << std::flush;
	const char* data = "\x01\x01\x01";
    arduino->writeData((char*)data, 3);
	arduino->writeFloat(value);
	std::cout << "Finished!" << std::endl << std::flush;
}

void pitch(Serial *arduino, float value) {
    std::cout << "Pitch Modifier... " << std::flush;
	const char* data = "\x01\x03\x01";
    arduino->writeData((char*)data, 3);
	arduino->writeFloat(value);
	std::cout << "Finished!" << std::endl << std::flush;
}

void yaw2(Serial *arduino, float value) {
    std::cout << "Yaw2 Modifier... " << std::flush;
	const char* data = "\x01\x05\x01";
    arduino->writeData((char*)data, 3);
	arduino->writeFloat(value);
	std::cout << "Finished!" << std::endl << std::flush;
}

void resetModifiers(Serial *arduino) {
	const char* data = "\x01\x06";
	arduino->writeData((char*)data, 2);
}

int main() {
	Serial arduino;

	std::cout << arduino.readString() << std::endl;
	std::cout << "- BEGIN TEST -" << std::endl;
	arduino.writeByte(1);

	// test successful thruster initialization
	readThrusters(&arduino);

	// test successful modifier initialization
	readModifiers(&arduino);
	
	// test move modifier
	move(&arduino, 1.0f);
	readAll(&arduino);
	
    // test dive modifier
	dive(&arduino, 1.0f);
	readAll(&arduino);
	
	// test strafe modifier
	move2(&arduino, 1.0f);
	readAll(&arduino);
	
	// reset modifiers
	resetModifiers(&arduino);
	
	// test yaw modifier
	yaw(&arduino, 1.0f);
	readAll(&arduino);
	
    // test pitch modifier
	pitch(&arduino, 1.0f);
	readAll(&arduino);
	
	// test yaw2 modifier
	yaw2(&arduino, 1.0f);
	readAll(&arduino);
	
	// reset modifiers
	resetModifiers(&arduino);
	
	// test forward blend
	move(&arduino, 1.0f);
	yaw(&arduino, 1.0f);
	readAll(&arduino);
	
	// test dive blend
	dive(&arduino, 1.0f);
	pitch(&arduino, 1.0f);
	readAll(&arduino);
	
	// test strafe blend
    move2(&arduino, 1.0f);
    yaw2(&arduino, 1.0f);
    readAll(&arduino);
    
    // reset modifiers
    resetModifiers(&arduino);

	std::cout << "- END OF TEST -" << std::endl;
}