#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Arduino.h"

#define MOTOR_PIN  33

// 功能：电机初始化
void motor_init(void);


// 功能：电机运行
// 参数：duty : PWM占空比   范围为 0% - 100%
void run_motor(uint32_t duty);


#endif 
