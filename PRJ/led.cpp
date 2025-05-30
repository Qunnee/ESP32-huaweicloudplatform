#include "esp32-hal-gpio.h"
#include "led.h"

// 定义变量存储LED灯的状态，0，表示灭   1，表示亮
uint8_t led1_state = 0;
uint8_t led2_state = 0;
uint8_t led3_state = 0;
uint8_t led4_state = 0;


/*
  功能：led灯的初始化
  参数：无
  返回值: 无
*/
void led_init(void)
{
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
}

/*
  功能：控制LED灯
  参数：
    @ pin：LED灯对应的引脚编号
    @ value : LED灯的状态
  返回值：无
*/
void led_onoff(uint8_t pin, uint8_t value)
{
  digitalWrite(pin, value);
}

/*
  功能：读取LED灯状态
  参数：
    @ pin : 哪个led灯的引脚
  返回值：LED灯的状态
*/
uint8_t get_led_state(uint8_t pin)
{
  if (digitalRead(pin))   // 读取LED灯引脚输出电平的状态
  {
    return LED_ON;
  }
  else
  {
    return LED_OFF;
  }
}

/*
  功能：控制LED灯闪烁
  参数:
    ms ：亮灭时间
  返回值：无
*/
void led_flash(uint32_t ms)
{
  uint8_t led_array[4] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

  for (int i = 0; i < 4; i++)
  {
    led_onoff(led_array[i], LED_ON);
    delay(ms);
    led_onoff(led_array[i], LED_OFF);
    delay(ms);
  }
}



