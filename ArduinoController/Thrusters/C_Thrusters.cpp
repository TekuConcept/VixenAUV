/**
 * Created by TekuConcept on 8/3/2016.
 */

#include "C_Thrusters.h"
	
#define MOD_COUNT 6u // thruster modifiers
#define THRUST_COUNT 6u

typedef struct hw_thruster {
	Servo servo;
	uint16_t value;
	float trim;
} hw_thruster;

float       hw_modifiers_[MOD_COUNT];
hw_thruster hw_thrusters_[THRUST_COUNT];

void update_pair(uint8_t,uint8_t,uint8_t,uint8_t);

void HW_configure(
	int aPairFirst, int aPairSecond,
	int bPairFirst, int bPairSecond,
	int cPairFirst, int cPairSecond) {

	hw_thrusters_[HW_A_FIRST ].servo.attach(aPairFirst);
	hw_thrusters_[HW_A_SECOND].servo.attach(aPairSecond);
	hw_thrusters_[HW_B_FIRST ].servo.attach(bPairFirst );
	hw_thrusters_[HW_B_SECOND].servo.attach(bPairSecond);
	hw_thrusters_[HW_C_FIRST ].servo.attach(cPairFirst );
	hw_thrusters_[HW_C_SECOND].servo.attach(cPairSecond);
	HW_hard_reset();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - *\
 *            Thruster Modifier Functions            *
\* - - - - - - - - - - - - - - - - - - - - - - - - - */

void HW_set_modifier(uint8_t index, float value) {
	if(index >= MOD_COUNT)
		return;

	if(value > 1)
		value = 1;
	else if(value < -1)
		value = -1;
	hw_modifiers_[index] = value;

	// update thrust output
	switch(index) {
	case HW_MOD_LIN1:
	case HW_MOD_ANG1:
		update_pair(HW_A_FIRST, HW_A_SECOND, HW_MOD_LIN1, HW_MOD_ANG1);
		break;
	case HW_MOD_LIN2:
	case HW_MOD_ANG2:
		update_pair(HW_B_FIRST, HW_B_SECOND, HW_MOD_LIN2, HW_MOD_ANG2);
		break;
	case HW_MOD_LIN3:
	case HW_MOD_ANG3:
		update_pair(HW_C_FIRST, HW_C_SECOND, HW_MOD_LIN3, HW_MOD_ANG3);
		break;
	}
}

float HW_get_modifier(uint8_t index) {
	if(index >= MOD_COUNT)
		return -2;
	return hw_modifiers_[index];
}

/**
 * Warning: This does not guarantee the thrusters
 *          will turn off because of offset and
 *          trim values.
 */
void HW_reset_modifiers() {
	for(int i = 0; i < MOD_COUNT; i++) {
		hw_modifiers_[i] = 0;
	}
	update_pair(HW_A_FIRST, HW_A_SECOND, HW_MOD_LIN1, HW_MOD_ANG1);
	update_pair(HW_B_FIRST, HW_B_SECOND, HW_MOD_LIN2, HW_MOD_ANG2);
	update_pair(HW_C_FIRST, HW_C_SECOND, HW_MOD_LIN3, HW_MOD_ANG3);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - *\
 *              Core Thruster Functions              *
\* - - - - - - - - - - - - - - - - - - - - - - - - - */

void HW_soft_reset() {
	DMSG("HW Soft Reset")
	for(int i = 0; i < MOD_COUNT; i++) {
		hw_modifiers_[i] = 0;
	}
	for(int i = 0; i < THRUST_COUNT; i++) {
		hw_thrusters_[i].servo.writeMicroseconds(HW_IDLE);
		hw_thrusters_[i].value = HW_IDLE;
	}
}

void HW_hard_reset() {
	DMSG("HW Hard Reset")
	for(int i = 0; i < THRUST_COUNT; i++) {
		hw_thrusters_[i].servo.writeMicroseconds(HW_IDLE);
		hw_thrusters_[i].value = HW_IDLE;
		hw_thrusters_[i].trim = 1;
	}
	DMSG(hw_thrusters_[0].value);
}

void set_safe_ratio(float* a, float* b) {
	if(*a >  1)	{
		*b /= *a;
		*a = 1;
	}
	else if(*a < -1) {
		*b /= -*a;
		*a = -1;
	}
	else if(*b >  1) {
		*a /= *b;
		*b = 1;
	}
	else if(*b < -1) {
		*a /= -*b;
		*b = -1;
	}
}

void update_pair(uint8_t hw_left, uint8_t hw_right,
	uint8_t linear_mod, uint8_t angular_mod) {
	float left = 0, right = 0, temp = 0;

	// blend move and yaw
	left   = hw_modifiers_[linear_mod];
	right  = left;
	temp   = hw_modifiers_[angular_mod];
	left  += temp;
	right -= temp;

	// set safe ranges as a ratio of the current values
	set_safe_ratio(&left, &right);

	HW_set_thruster(hw_left,
		(uint16_t)(HW_IDLE + left *hw_thrusters_[hw_left ].trim*HW_DIFF));
	HW_set_thruster(hw_right,
		(uint16_t)(HW_IDLE + right*hw_thrusters_[hw_right].trim*HW_DIFF));
}

void HW_set_thruster(uint8_t index, uint16_t value) {
	if(index >= THRUST_COUNT)
		return;
	hw_thrusters_[index].servo.writeMicroseconds(value);
	hw_thrusters_[index].value = value;
}

uint16_t HW_get_thruster(uint8_t index) {
	if(index >= THRUST_COUNT)
		return 0;
	return hw_thrusters_[index].value;
}

void HW_set_trim(uint8_t index, float value) {
	if(index >= THRUST_COUNT)
		return;
	if(value > 1)
		value = 1;
	else if(value < -1)
		value = -1;

	hw_thrusters_[index].trim = value;
	switch(index) {
	case HW_A_FIRST:
	case HW_A_SECOND:
		update_pair(HW_A_FIRST, HW_A_SECOND, HW_MOD_LIN1, HW_MOD_ANG1);
		break;
	case HW_B_FIRST:
	case HW_B_SECOND:
		update_pair(HW_B_FIRST, HW_B_SECOND, HW_MOD_LIN2, HW_MOD_ANG2);
		break;
	case HW_C_FIRST:
	case HW_C_SECOND:
		update_pair(HW_C_FIRST, HW_C_SECOND, HW_MOD_LIN3, HW_MOD_ANG3);
		break;
	}
}

float HW_get_trim(uint8_t index) {
	if(index >= THRUST_COUNT)
		return -2;
	return hw_thrusters_[index].trim;
}

void HW_reset_trim() {
	for(int i = 0; i < THRUST_COUNT; i++) {
		hw_thrusters_[i].trim = 1;
	}
	update_pair(HW_A_FIRST, HW_A_SECOND, HW_MOD_LIN1, HW_MOD_ANG1);
	update_pair(HW_B_FIRST, HW_B_SECOND, HW_MOD_LIN2, HW_MOD_ANG2);
	update_pair(HW_C_FIRST, HW_C_SECOND, HW_MOD_LIN3, HW_MOD_ANG3);
}