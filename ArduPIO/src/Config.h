/**
 * Created by TekuConcept on 12/22/2016.
 */
#ifndef CONFIG_H
#define CONFIG_H

// Pin Map
#define ENA 5
#define ENB 6
#define MOTOR_INPUT1 8
#define MOTOR_INPUT2 7
#define MOTOR_INPUT3 12
#define MOTOR_INPUT4 13
#define SERVO1 9
#define SERVO2 10

// Serial
#define BAUD 115200
#if defined(__AVR_ATmega328P__)
    #define UNO
    #define GARBAGE 240
#elif defined(__AVR_ATSAM3X8E__)
    #define DUE
    #define GARBAGE 0
#endif

#endif