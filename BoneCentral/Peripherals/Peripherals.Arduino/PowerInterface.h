/**
 * Created by TekuConcept on 8/4/2016.
 */

#ifndef POWER_INTERFACE_H
#define POWER_INTERFACE_H

#include "Serial.h"
#include "ArduinoMap.h"

#include <string>
#include <chrono>
#include <thread>

#ifndef SWIG
#	if !defined(NODE_MAJOR) && !defined(NODE_MINOR)
#	error NODE_MAJOR And NODE_MINOR Not Defined
#	elif (NODE_MAJOR == 0) && (NODE_MINOR < 12)
#	error Node Version Must Be >= v0.12.X
#	endif
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#		include <node.h>
#		include <v8.h>
#		include <uv.h>
#	pragma GCC diagnostic pop

typedef struct WorkerPacket {
	uv_work_t request;
	v8::Persistent<v8::Function> callback;
	Serial* arduino;
	std::string result;
	void (*execute)(Serial*, std::string&);
} WorkerPacket;
#endif

class Power {
public:
	Power();
	~Power();

	// escs
	void turnOnEscs();
	void turnOffEscs();

	// lights
	void turnOnHeadlights();
	void turnOffHeadlights();

	// voltage
	float getBatteryVoltage();

	// led
	void runLED();
	
	// debug
	void verbose(bool flag);

#ifndef SWIG
	Power(Serial* in);
	void waitStart(const v8::FunctionCallbackInfo<v8::Value> &args);
#endif

private:
	Serial *arduino;
	bool verbose_;
};

#endif