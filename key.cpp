#include "esp32-hal-gpio.h"
#include "key.h"
#include "led.h"

// 按键1对应的中断处理函数，当发生按键中断时，会调用这个中断处理函数
void key1_Handler(void)
{
  if (get_led_state(LED1_PIN) == LED_ON)
  {
    led_onoff(LED1_PIN, LED_OFF);
    led1_state = 0;
  }
  else
  {
    led_onoff(LED1_PIN, LED_ON);
    led1_state = 1;
  }
}

// 按键2对应的中断处理函数，当发生按键中断时，会调用这个中断处理函数
void key2_Handler(void)
{
  if (get_led_state(LED2_PIN) == LED_ON)
  {
    led_onoff(LED2_PIN, LED_OFF);
    led2_state = 0;
  }
  else
  {
    led_onoff(LED2_PIN, LED_ON);
    led2_state = 1;
  }
}

// 按键3对应的中断处理函数，当发生按键中断时，会调用这个中断处理函数
void key3_Handler(void)
{
  if (get_led_state(LED3_PIN) == LED_ON)
  {
    led_onoff(LED3_PIN, LED_OFF);
    led3_state = 0;
  }
  else
  {
    led_onoff(LED3_PIN, LED_ON);
    led3_state = 1;
  }
}

// 按键4对应的中断处理函数，当发生按键中断时，会调用这个中断处理函数
void key4_Handler(void)
{
  if (get_led_state(LED4_PIN) == LED_ON)
  {
    led_onoff(LED4_PIN, LED_OFF);
    led4_state = 0;
  }
  else
  {
    led_onoff(LED4_PIN, LED_ON);
    led4_state = 1;
  }
}
/*
  功能：按键中断初始化
  参数: 无
  返回值：无
*/
void key_it_init(void)
{
  pinMode(KEY1_PIN, INPUT_PULLUP);
  pinMode(KEY2_PIN, INPUT_PULLUP);
  pinMode(KEY3_PIN, INPUT_PULLUP);
  pinMode(KEY4_PIN, INPUT_PULLUP);

  attachInterrupt(KEY1_PIN, key1_Handler, FALLING);
  attachInterrupt(KEY2_PIN, key2_Handler, FALLING);
  attachInterrupt(KEY3_PIN, key3_Handler, FALLING);
  attachInterrupt(KEY4_PIN, key4_Handler, FALLING);
}




