#include "IController.h"

class KillController : public IController {
private:
    IController ** list;
    int count;
  
public:
    KillController(IController ** _list_, int _count_) {
        list = _list_;
        count = _count_;
    }

    void execute() {
        for(int i = 1; i<count; i++) list[i]->kill();
    }

    void kill() { }
};