/**
 * Created by TekuConcept on 8/3/2016.
 */

#include "C_Thrusters.h"
	
#define MOD_COUNT 6u // thruster modifiers
#define THRUST_COUNT 6u
float    hw_modifiers_[MOD_COUNT];
float    hw_trim_[THRUST_COUNT];
uint16_t hw_thrust_mem_[THRUST_COUNT];
//Servo  hw_servos_[THRUST_COUNT];

void update_pair(uint8_t,uint8_t,uint8_t,uint8_t);

void HW_configure(
	int aPairFirst, int aPairSecond,
	int bPairFirst, int bPairSecond,
	int cPairFirst, int cPairSecond) {
	//hw_servos_[HW_A_FIRST ].attach(aPairFirst );
	//hw_servos_[HW_A_SECOND].attach(aPairSecond);
	//hw_servos_[HW_B_FIRST ].attach(bPairFirst );
	//hw_servos_[HW_B_SECOND].attach(bPairSecond);
	//hw_servos_[HW_C_FIRST ].attach(cPairFirst );
	//hw_servos_[HW_C_SECOND].attach(cPairSecond);
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
	for(int i = 0; i < MOD_COUNT; i++) {
		hw_modifiers_[i] = 0;
	}
	for(int i = 0; i < THRUST_COUNT; i++) {
		//hw_servos_[i].writeMicroseconds(HW_IDLE);
		hw_thrust_mem_[i] = HW_IDLE;
	}
}

void HW_hard_reset() {
	HW_soft_reset();
	for(int i = 0; i < THRUST_COUNT; i++) {
		hw_trim_[i] = 1;
	}
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
	left = hw_modifiers_[linear_mod];
	right = left;
	temp = hw_modifiers_[angular_mod];
	left += temp;
	right -= temp;

	// set safe ranges as a ratio of the current values
	set_safe_ratio(&left, &right);

	HW_set_thruster(hw_left,
		(uint16_t)(HW_IDLE + left *hw_trim_[hw_left ]*HW_DIFF));
	HW_set_thruster(hw_right,
		(uint16_t)(HW_IDLE + right*hw_trim_[hw_right]*HW_DIFF));
}

void HW_set_thruster(uint8_t index, uint16_t value) {
	if(index >= THRUST_COUNT)
		return;
	//hw_servos_[index].writeMicroseconds(value);
	hw_thrust_mem_[index] = value;
}

uint16_t HW_get_thruster(uint8_t index) {
	if(index >= THRUST_COUNT)
		return 0;
	return hw_thrust_mem_[index];
}

void HW_set_trim(uint8_t index, float value) {
	if(index >= THRUST_COUNT)
		return;
	if(value > 1)
		value = 1;
	else if(value < -1)
		value = -1;

	hw_trim_[index] = value;
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
	return hw_trim_[index];
}

void HW_reset_trim() {
	for(int i = 0; i < THRUST_COUNT; i++) {
		hw_trim_[i] = 1;
	}
	update_pair(HW_A_FIRST, HW_A_SECOND, HW_MOD_LIN1, HW_MOD_ANG1);
	update_pair(HW_B_FIRST, HW_B_SECOND, HW_MOD_LIN2, HW_MOD_ANG2);
	update_pair(HW_C_FIRST, HW_C_SECOND, HW_MOD_LIN3, HW_MOD_ANG3);
}