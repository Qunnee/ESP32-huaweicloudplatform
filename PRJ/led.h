// 防止头文件被重复包含
// #ifndef : 如果没有定义 __LED_H__
// #define : 定义__LED_H__
// #endif : #ifndef 结尾
// __LED_H__ : 将头文件的名字转换得到
#ifndef __LED_H__
#define __LED_H__

// 1. 头文件包含
#include "Arduino.h"

// 声明，可以被其他文件使用
extern uint8_t led1_state ;
extern uint8_t led2_state ;
extern uint8_t led3_state ;
extern uint8_t led4_state ;

// 2. 宏定义:在使用宏定义的位置最终会被替换成对应的值
#define LED1_PIN  15
#define LED2_PIN  2
#define LED3_PIN  0
#define LED4_PIN  4

#define LED_ON    HIGH
#define LED_OFF   LOW

// 3. 函数的声明
/*
  功能：led灯的初始化
  参数：无
  返回值: 无
*/
void led_init(void);

/*
  功能：控制LED灯
  参数：
    @ pin：LED灯对应的引脚编号
    @ value : LED灯的状态
  返回值：无
*/
void led_onoff(uint8_t pin, uint8_t value);

/*
  功能：读取LED灯状态
  参数：
    @ pin : 哪个led灯的引脚
  返回值：LED灯的状态
*/
uint8_t get_led_state(uint8_t pin);

/*
  功能：控制LED灯闪烁
  参数:
    ms ：亮灭时间
  返回值：无
*/
void led_flash(uint32_t ms);

#endif 

