#include "esp32-hal-adc.h"

#include "adc.h"
// 功能：ADC初始化的函数
void adc_init(void)
{
  analogReadResolution(12);  // 设置ADC位数
}


/*
 * 功能：读取模拟电压值
 * 参数：无
 * 返回值：测量的模拟电压值。
*/ 
float read_analog_vol(uint8_t pin)
{
  int adc_value = analogRead(pin);

  float analogValue = adc_value * 3.3 / 4095;

  return analogValue;
}
