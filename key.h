#ifndef __KEY_H__
#define __KEY_H__

#include "Arduino.h"
#include "led.h"

// 按键对应的引脚的宏定义
#define  KEY1_PIN  14
#define  KEY2_PIN  27
#define  KEY3_PIN  26
#define  KEY4_PIN  25

/*
  功能：按键中断初始化
  参数: 无
  返回值：无
*/
void key_it_init(void);


#endif 