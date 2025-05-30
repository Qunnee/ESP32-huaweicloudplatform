#ifndef __ADC_H__
#define __ADC_H__

#include "Arduino.h"

#define  ADC_PIN  34
#define  SMOKE_PIN 35
#define  FIRE_PIN  36

// 功能：ADC初始化的函数
void adc_init(void);


/*
 * 功能：读取模拟电压值
 * 参数：
 *    pin : 读取哪个引脚的模拟电压值
 * 返回值：测量的模拟电压值。
*/ 
float read_analog_vol(uint8_t pin);

#endif 