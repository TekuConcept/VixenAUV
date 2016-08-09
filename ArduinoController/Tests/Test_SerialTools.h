#ifndef TEST_SERIAL_TOOLS_H
#define TEST_SERIAL_TOOLS_H
#include "../IController.h"
#include "../SerialTools.h"

class TestSerialTools : public IController {
public:
	void execute() {
		SerialEx::writeString("arduino", 7);
		SerialEx::writeFloat(3.14159f);
		SerialEx::writeDouble(2.71828);
		SerialEx::writeInt(-2);
		SerialEx::writeUInt(2u);
		SerialEx::writeShort(-1);
		SerialEx::writeUShort(1u);

		float    _0 = SerialEx::readFloat();
		double   _1 = SerialEx::readDouble();
		int32_t  _2 = SerialEx::readInt();
		uint32_t _3 = SerialEx::readUInt();
		int16_t  _4 = SerialEx::readShort();
		uint16_t _5 = SerialEx::readUShort();
		Serial.print("A-Float: ");  Serial.println(_0);
		Serial.print("A-Double: "); Serial.println(_1);
		Serial.print("A-Int: ");    Serial.println(_2);
		Serial.print("A-UInt: ");	Serial.println(_3);
		Serial.print("A-Short: ");  Serial.println(_4);
		Serial.print("A-UShort: "); Serial.println(_5);
		SerialEx::writeString("", 0);
	}
	void kill() {}
};

#endif