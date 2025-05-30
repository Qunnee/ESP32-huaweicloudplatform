#ifndef __BEEP_H__
#define __BEEP_H__

#include "Arduino.h"


extern uint8_t beep_state ;

#define BEEP_PIN   12

// 功能：打开蜂鸣器
// 参数：freq : 驱动蜂鸣器的频率
// 返回值：无
void beep_open(uint32_t freq);

// 功能：关闭蜂鸣器
// 参数：无
// 返回值：无
void beep_close(void);


#endif 

