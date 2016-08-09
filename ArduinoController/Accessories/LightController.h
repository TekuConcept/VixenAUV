#include "../IController.h"
#include "../PinMap.h"

class LightController : public IController {
private:
public:
  LightController() {
    pinMode(LIGHT_PIN, OUTPUT);
    digitalWrite(LIGHT_PIN, HIGH);
  }
  void execute() {
    while(!Serial.available());
    digitalWrite(LIGHT_PIN, !Serial.read());
  }
  void kill() {
    //digitalWrite(LIGHT_PIN, HIGH);
  }
};
