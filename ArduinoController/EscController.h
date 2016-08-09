#include "IController.h"
#include "PinMap.h"

#define ESC_COUNT 6
class EscController : public IController {
private:
  const uint8_t GPIO_PINS[ESC_COUNT] =
    {ESC1, ESC2, ESC3, ESC4, ESC5, ESC6};
public:
  EscController() {
    for(int i = 0; i < ESC_COUNT; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    for(int i = 0; i < ESC_COUNT; i++) {
      digitalWrite(GPIO_PINS[i], !(toggle&(1 << i)));
    }
  }
  void kill() {
    for(int i = 0; i < ESC_COUNT; i++) {
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
};
