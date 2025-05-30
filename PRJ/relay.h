#ifndef __RELAY_H__
#define __RELAY_H__ 

#include <Arduino.h>

extern uint8_t relay_state;

#define  RELAY_PIN  32

// 功能：继电器初始化
void relay_init(void);

// 功能：继电器开
void relay_open(void);

// 功能：继电器关闭
void relay_close(void);

#endif 
