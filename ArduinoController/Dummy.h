#include "IController.h"

class Dummy : public IController {
public:
  Dummy() {}
  void execute() {}
  void kill() {}
};

