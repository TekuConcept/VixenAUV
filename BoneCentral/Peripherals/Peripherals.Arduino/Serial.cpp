//
// Created by Nathan Copier on 1/28/2016.
// Refactored by TekuConcept on 8/3/2016.
//

#include "Serial.h"

std::mutex Serial::serialLock_;

Serial::Serial() {
    std::system("stty -F /dev/ttyACM0 cs8 115200 ignbrk \
        -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon \
        -iexten -echo -echoe -echok -echoctl -echoke noflsh \
        -ixon -crtscts");
    input_ = std::make_shared<std::ifstream>("/dev/ttyACM0");
    output_ = std::make_shared<std::ofstream>("/dev/ttyACM0");
}

Serial::~Serial() {
    input_->close();
    output_->close();
}

std::string Serial::readString() {
    std::lock_guard<std::mutex> guard(serialLock_);
    std::stringstream ss;
    char c;
    do{
        // NOTE: if the program halts here
        // it is because the arduino didn't
        // write anything to the stream.
        c = input_->get();
        ss << c;
    }while(c != '\0');
    
    return ss.str();
}

float Serial::readFloat() {
    float result = 0;
    readData((char*)&result, 4);
    return result;
}

double Serial::readDouble() {
    double result = 0;
#ifdef DUE
    readData((char*)&result, 8);
#else
    float data = 0;
    readData((char*)&data, 4);
    result = (double)data;
#endif
    return result;
}

int Serial::readInt() {
    int result = 0;
    readData((char*)&result, 4);
    return result;
}

unsigned int Serial::readUInt() {
    unsigned int result = 0;
    readData((char*)&result, 4);
    return result;
}

short Serial::readShort() {
    short result = 0;
    readData((char*)&result, 2);
    return result;
}

unsigned short Serial::readUShort() {
    unsigned short result = 0;
    readData((char*)&result, 2);
    return result;
}

void Serial::readData(char* ptr, size_t size) {
    std::lock_guard<std::mutex> guard(serialLock_);
    input_->read(ptr, size);
}




void Serial::writeFloat(float value) {
    writeData((char*)&value, 4);
}

void Serial::writeDouble(double value) {
#ifdef DUE
    writeData((char*)&value, 8);
#else
    float val2 = (float)value;
    writeData((char*)&val2, 4);
#endif
}

void Serial::writeInt(int value) {
    writeData((char*)&value, 4);
}

void Serial::writeUInt(unsigned int value) {
    writeData((char*)&value, 4);
}

void Serial::writeShort(short value) {
    writeData((char*)&value, 2);
}

void Serial::writeUShort(unsigned short value) {
    writeData((char*)&value, 2);
}

void Serial::writeByte(unsigned char value) {
    writeData((char*)&value, 1);
}

void Serial::writeData(char* ptr, size_t size) {
    std::lock_guard<std::mutex> guard(serialLock_);
    output_->write(ptr, size);
    output_->flush();
}