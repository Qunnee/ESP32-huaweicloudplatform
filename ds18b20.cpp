

#include "ds18b20.h"

OneWire  myWire(DS18B20_PIN);   // 实例化一个单总线的对象
DallasTemperature   ds18b20(&myWire);

void ds18b20_init()
{
  ds18b20.begin();    // 初始化
}

float get_ds18b20_temp(void)
{
  // 1. 请求温度的测量
  ds18b20.requestTemperatures();
  delay(1000);
  // 2. 读取测量的温度值
  float temp = ds18b20.getTempCByIndex(0);


  return temp;
}