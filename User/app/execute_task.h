#ifndef __EXECUTE_TASK_H__
#define __EXECUTE_TASK_H__

#include "stm32f4xx_hal.h"

void execute_task(const void* argu);

int32_t getCurrentAngle(int motor);
int32_t getCurrentSpeed(int motor);

void test_moto_init(void);
void test_moto_control(void);

#endif

