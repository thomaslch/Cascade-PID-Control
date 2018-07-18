#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "cmsis_os.h"
#include "calibrate.h"
#include "pid.h"
#include "sys.h"



extern uint8_t test_servo;

int16_t angular_velocity[4] = {0};
int16_t output[4]={0};

float m_target = 45;
int16_t current_angle = 0;

float angular_kp = 30;
float angular_ki = 0;
float angular_kd = 0;

float speed_kp = 10;
float speed_ki = 0;
float speed_kd = 0;

pid_t m_pid_angular_velocity[4] = {0};

int rc_min = 0;
int rc_max = 0x294;

int angle_min = 0x1D;
int angle_max = 0x1AB0;

void execute_task(const void* argu){
		pid_init(&pid_wheel_spd[0], 7000, 0, angular_kp, angular_ki, angular_kd);
		pid_init(&m_pid_angular_velocity[0], 7000, 0, speed_kp, speed_ki, speed_kd);
	
		while(1){
			// map rc from 0-360, put it in target
			m_target = rc.ch1*360/660;
			//m_target = rc.ch1*2;
			
			
			current_angle = getCurrentAngle(0);
			
			
			angular_velocity[0] = pid_calc(&pid_wheel_spd[0], getCurrentAngle(0), m_target);
			output[0] = pid_calc(&m_pid_angular_velocity[0], getCurrentSpeed(0), angular_velocity[0]);
			//output[0] = pid_calc(&m_pid_angular_velocity[0], getCurrentSpeed(0), m_target);
			
			
			
			send_chassis_moto_current(&output[0]);
			

			
			osDelay(5);
  }
}

int32_t getCurrentAngle(int motor){
	return (moto_chassis[motor].total_angle/19);
}

int32_t getCurrentSpeed(int motor){
	return (moto_chassis[motor].speed_rpm);
}
