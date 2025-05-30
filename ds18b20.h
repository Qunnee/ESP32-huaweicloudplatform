#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "OneWire.h"
#include "DallasTemperature.h"

#define  DS18B20_PIN  13

void ds18b20_init();

float get_ds18b20_temp(void);

#endif 