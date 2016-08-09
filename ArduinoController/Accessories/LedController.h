#include "../IController.h"
#include "../PinMap.h"

class LedController : public IController {
public:
  LedController() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(250);
      digitalWrite(LED_PIN, LOW);
      delay(250);
    }
  }
  void kill() {
    digitalWrite(LED_PIN, LOW);
  }
};
