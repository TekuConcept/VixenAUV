/**
 * Created by TekuConcept on 12/22/2016.
 */
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "IController.h"
#include "SerialTools.h"
#include "Config.h"

#define MOTOR_STOP    {\
    digitalWrite(MOTOR_INPUT1,LOW ); digitalWrite(MOTOR_INPUT2,LOW );\
    digitalWrite(MOTOR_INPUT3,LOW ); digitalWrite(MOTOR_INPUT4,LOW );\
}


class MotorDriver : public IController {
public:
    MotorDriver() {
        pinMode(ENA,OUTPUT);
        pinMode(ENB,OUTPUT);
        pinMode(MOTOR_INPUT1,OUTPUT);
        pinMode(MOTOR_INPUT2,OUTPUT);
        pinMode(MOTOR_INPUT3,OUTPUT);
        pinMode(MOTOR_INPUT4,OUTPUT);
    }
    
    void execute() {
        while(Serial.available() < 1);
        uint8_t rw = Serial.read(); // 0 read 1 write
        
        if(rw == 0) {
            SerialEx::writeFloat(_l);
            SerialEx::writeFloat(_r);
        }
        else {
            float move = SerialEx::readFloat();
            float yaw  = SerialEx::readFloat();
            
            // convert from floats to blended floats
            float l, r, s, _m, _y;
            _m = (move > 0) ? move : -move;
            _y = ( yaw > 0) ?  yaw : -yaw;
            // find unit scalar
            if (_m == 0 || _y == 0) s = 1;
            else if (_m == 1)       s = 1 + _y;
            else if (_y == 1)       s = 1 + _m;
            else                    s = 1 + (_m + _y) / 2.0F;
            // calculate unit magnitudes
            l = (move - yaw)/s;
            r = (move + yaw)/s;
            _l = l; _r = r;
            
            // convert from blended floats to motor functions
            runMotors(l, r);
        }
    }
    
    void kill() {
        MOTOR_STOP;
    }

private:
    float _l, _r;
    void runMotors(float left, float right) {
        const int SCALE = 165;
        const float DELTA = 0.05F;
        int lstate, rstate;

        // get vector direction
        if (inRange(left, DELTA))   lstate = 0;
        else if (left > 0)          lstate = 1;
        else                        lstate = -1;
        if (inRange(right, DELTA))  rstate = 0;
        else if (right > 0)         rstate = 1;
        else                        rstate = -1;
        
        int lres, rres;
        lres = (lstate *  left) * SCALE + 90;
        rres = (rstate * right) * SCALE + 90;
        
        MOTOR_STOP;
        analogWrite(ENB,lres);
        analogWrite(ENA,rres);
        if(lstate > 0)      { digitalWrite(MOTOR_INPUT3,LOW ); digitalWrite(MOTOR_INPUT4,HIGH); }
        else if(lstate < 0) { digitalWrite(MOTOR_INPUT3,HIGH); digitalWrite(MOTOR_INPUT4,LOW ); }
        else                { digitalWrite(MOTOR_INPUT3,LOW ); digitalWrite(MOTOR_INPUT4,LOW ); }
        if(rstate > 0)      { digitalWrite(MOTOR_INPUT1,LOW ); digitalWrite(MOTOR_INPUT2,HIGH); }
        else if(rstate < 0) { digitalWrite(MOTOR_INPUT1,HIGH); digitalWrite(MOTOR_INPUT2,LOW ); }
        else                { digitalWrite(MOTOR_INPUT1,LOW ); digitalWrite(MOTOR_INPUT2,LOW ); }
    }
    bool inRange(float value, float delta) {
        return (value <= delta) && (value >= -delta);
    }
};

#endif