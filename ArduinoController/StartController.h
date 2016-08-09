#include "IController.h"
#include "SerialTools.h"

class StartController : public IController {
private:
  bool armed;
public:
  void execute() {
    armed = true;
  }
  void kill() {
    if(armed) {
      SerialEx::writeString("Begin!", 6);
      armed = false;
    }
  }
};
