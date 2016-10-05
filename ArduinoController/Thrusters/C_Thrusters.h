/**
 * Created by TekuConcept on 8/3/2016.
 */

#ifndef C_THRUSTERS_H
#define C_THRUSTERS_H

#include <Arduino.h>
#include <Servo.h>

//#define DEBUG
#ifdef DEBUG
	#define DMSG(msg) Serial.println(msg);
#else
	#define DMSG(msg) (void)(msg);
#endif

#define HW_MOD_LIN1  0
#define HW_MOD_ANG1  1
#define HW_MOD_LIN2  2
#define HW_MOD_ANG2  3
#define HW_MOD_LIN3  4
#define HW_MOD_ANG3  5
#define HW_MOD_RESET 6
#define HW_RD 0
#define HW_WR 1
#define HW_DIFF 500
#define HW_IDLE 1500
#define HW_FORWARD 2000
#define HW_REVERSE 1000
#define HW_A_FIRST    0
#define HW_A_SECOND   1
#define HW_B_FIRST    2
#define HW_B_SECOND   3
#define HW_C_FIRST    4
#define HW_C_SECOND   5
#define HW_SOFT_RESET 6
#define HW_HARD_RESET 7
#define HW_TRIM_RESET 6

void HW_configure(
	int aPairFirst, int aPairSecond,
	int bPairFirst, int bPairSecond,
	int cPairFirst, int cPairSecond);

void     HW_set_modifier(uint8_t index, float value);
float    HW_get_modifier(uint8_t index);
void     HW_reset_modifiers();

void     HW_set_thruster(uint8_t index, uint16_t value);
uint16_t HW_get_thruster(uint8_t index);
void     HW_soft_reset(); // stops thrust and resets modifiers
void     HW_hard_reset(); // resets all values to startup defaults

void     HW_set_trim(uint8_t index, float value);
float    HW_get_trim(uint8_t index);
void     HW_reset_trim();

#endif