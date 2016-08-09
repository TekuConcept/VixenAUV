#include "IController.h"
#include "PinMap.h"
#include "SerialTools.h"

class KillSwitchController : public IController {
private:
  volatile int active;
  IController ** list;
  int count, self;
  
public:
  KillSwitchController(IController ** _list_, int _count_, int _self_) {
    list = _list_;
    count = _count_;
    self = _self_;
    pinMode(KILL_LED, OUTPUT);
  }

  void execute() {
    SerialEx::writeByte((uint8_t)active);
  }

  void kill() {
    for(int i = 0; i<count; i++) {
      if(i != self)
        list[i]->kill();
    }
  }

  void isr() {
    noInterrupts();
    // when not active, interrupt pin reads a '1'
    // when active, interrupt pin reads a '0'
    active = !digitalRead(KILL_PIN);
    if(active)
      kill();
    digitalWrite(KILL_LED, active);
    interrupts();
  }
};
