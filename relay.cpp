#include "esp32-hal-gpio.h"

#include "relay.h"

// 记录继电器的状态
uint8_t relay_state = 0;

// 功能：继电器初始化
void relay_init(void)
{
  pinMode(RELAY_PIN, OUTPUT);
}

// 功能：继电器开
void relay_open(void)
{
  digitalWrite(RELAY_PIN, HIGH); 
}

// 功能：继电器关闭
void relay_close(void)
{
  digitalWrite(RELAY_PIN, LOW);
}