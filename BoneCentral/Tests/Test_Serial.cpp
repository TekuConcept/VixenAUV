#include "Serial.h"
#define SUCCESS 0

int main() {
    Serial arduino;
    
    std::cout << arduino.readString() << std::endl << std::flush;
    arduino.writeByte(0);
    std::cout << "String... ";
    std::cout << arduino.readString() << std::endl << std::flush;
    std::cout << "Float... ";
    std::cout << arduino.readFloat() << std::endl << std::flush;
    std::cout << "Double... ";
    std::cout << arduino.readDouble() << std::endl << std::flush;
    std::cout << "Int... ";
    std::cout << arduino.readInt() << std::endl << std::flush;
    std::cout << "Unsigned Int... ";
    std::cout << arduino.readUInt() << std::endl << std::flush;
    std::cout << "Short... ";
    std::cout << arduino.readShort() << std::endl << std::flush;
    std::cout << "Unsigned Short... ";
    std::cout << arduino.readUShort() << std::endl << std::flush;
    std::cout << "- END OF READ TEST -\n" << std::endl << std::flush;
    
    arduino.writeFloat(3.14);
    arduino.writeDouble(2.72);
    arduino.writeInt(-2);
    arduino.writeUInt(2u);
    arduino.writeShort(-1);
    arduino.writeUShort(1u);
    std::cout << "Result: \n";
    std::cout << arduino.readString() << std::endl << std::flush;
    std::cout << "- END OF WRITE TEST -\n" << std::endl;
    
    return SUCCESS;
}