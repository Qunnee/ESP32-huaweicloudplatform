#ifndef __SMG_H__
#define __SMG_H__

#include "tm1637.h"

#define  CLK_PIN   16
#define  DIO_PIN   17

void smg_init(void);

// 功能：数码管显示
// 参数：数码管显示的数据
void smg_display(float value);

#endif 
