#include "../IController.h"
#include "../PinMap.h"
#include "../SerialTools.h"

#define R1 30000.0
#define R2  7500.0

class VoltageController : public IController {  
  public:
    VoltageController() {
      pinMode(VOLT_PIN, INPUT);
    }
    
    void execute() {
      int value = analogRead(VOLT_PIN);
      /*
       * Measured Values for Calibration
       * P1 = (11.32, 700); P2 = (8.38, 517)
       *
       * Solve for the linear function: x = (y-b)/m
       * voltage = (2.94 * value + 13.56) / 183
       */
      SerialEx::writeFloat((2.94 * value + 13.56) / 183);
    }
    
    void kill() {
      
    }
};

