#include "esp32-hal-gpio.h"
#include "motor.h"

// 功能：电机初始化
void motor_init(void)
{
  pinMode(MOTOR_PIN, OUTPUT);
  // PWM通道和GPIO引脚绑定，指定PWM的频率
  ledcAttachChannel(MOTOR_PIN, 1000, 8, 1);
}


// 功能：电机运行
// 参数：duty : PWM占空比   范围为 0% - 100%
void run_motor(uint32_t duty)
{
  if (duty > 100) duty = 100;
  ledcWriteChannel(1, 255 * duty / 100);
}
