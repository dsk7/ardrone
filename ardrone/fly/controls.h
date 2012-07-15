#ifndef _CONTROLS_H
#define _CONTROLS_H

#include "../attitude/attitude.h"


struct setpoint_struct {
	float pitch; //radians  
	float roll; //radians     
	float yaw; //radians   
	float h; //meters
};


struct control_limits_struct {
	float pitch_roll_max; //radians     
	float h_max; //m
	float h_min; //m
	float throttle_hover; //hover throttle setting
	float throttle_min; //min throttle (while flying)
	float throttle_max; //max throttle (while flying)
};


enum FlyState {
	Landed=1,
	Launching=10,
	Flying=11,
	Landing=12,
	Error=20
} flyState;


const char *stateName(enum FlyState state);


struct drone_state_struct {
	struct att_struct att;
	enum FlyState flyState;
	struct setpoint_struct setpoint;
	struct control_limits_struct control_limits;
};

void switchState(struct drone_state_struct *dronestate, enum FlyState newState);

struct control_strategy_struct {
	/** called once */
	void (*init)();
	/** called every time new attitude data is available, should write desired motor speeds to the float-array */
	void (*calculateMotorSpeeds)(struct drone_state_struct *, float[4]);
	/** should write upto maxLen (second parm) bytes into the char * and return number of bytes written (including \0) */
	unsigned int (*getLogText)(char *,unsigned int);
};

#define LOAD_STRATEGY(targetStruct, name) \
		targetStruct.init=  pid_strategy_init; \
		targetStruct.calculateMotorSpeeds=  pid_strategy_calculateMotorSpeeds;\
		targetStruct.getLogText=  pid_strategy_getLogText;
	




#endif


