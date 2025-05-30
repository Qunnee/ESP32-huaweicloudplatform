#include "beep.h"

uint8_t beep_state = 0;

// 功能：打开蜂鸣器
// 参数：freq : 驱动蜂鸣器的频率
// 返回值：无
void beep_open(uint32_t freq)
{
  // freq频率大于2000，则让频率最大为2000
  if (freq > 2000)
    freq = 2000;    
  tone(BEEP_PIN, freq);
  beep_state = 1;
}

// 功能：关闭蜂鸣器
// 参数：无
// 返回值：无
void beep_close(void)
{
  noTone(BEEP_PIN);
  beep_state = 0;
}
