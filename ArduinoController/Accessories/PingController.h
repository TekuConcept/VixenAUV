#include "../IController.h"
#include "../SerialTools.h"

class PingController : public IController {
public:
  void execute() {
    while(Serial.available())
    {
      Serial.print(Serial.read());
    }
    SerialEx::writeString("I'm Here!", 9);
  }
  void kill() { }
};
