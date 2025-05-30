#include "led.h"
#include "key.h"
#include "ds18b20.h"
#include "smg.h"
#include "relay.h"
#include "beep.h"
#include "motor.h"
#include "adc.h"
#include "WiFi.h"

#include <PubSubClient.h>     // MQTT协议的头文件
// 需要安装PubSubClient第三方库

#include <ArduinoJson.h>      // Json格式字符串处理的头文件
// 需要安装ArduinoJson第三方库


// WiFi 名字和密码，需要使用自己的手机的热点，手机设置为2.4G热点，热点最大允许连接数大于2个
const char* ssid = "zhoukai";   // Wifi热点的名字，尽量不要使用中文的wifi名字
const char* password = "987654321";   // wifi密码

// 华为云的MQTT服务器的物联网设备接入的公网网址和端口号
const char* mqtt_server = "a4aeaed33c.st1.iotda-device.cn-north-4.myhuaweicloud.com";  // 替换为你的华为云MQTT Broker地址
const int mqtt_port = 1883;

// 华为云MQTT 客户端ID  用户名 密码 
// 67d78dceaa00d157701ab54e_ESP32_Device_0_0_2025042808
const char* mqtt_client_id = "67d78dceaa00d157701ab54e_ESP32_Device_0_0_2025042808";             // 替换为你的客户端ID
// 67d78dceaa00d157701ab54e_ESP32_Device
const char* mqtt_username = "67d78dceaa00d157701ab54e_ESP32_Device";                             // 替换为你的用户名
// 8cf66dddf071f23b8b84fce044f4360c1c46b2e302c7bc9d0519b8a06d989ea9
const char* mqtt_password = "8cf66dddf071f23b8b84fce044f4360c1c46b2e302c7bc9d0519b8a06d989ea9";  // 替换为你的密码

// MQTT 客户端的对象
WiFiClient espClient;
PubSubClient client(espClient);


/*
  功能：连接wifi信号的函数
*/
void setup_wifi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);     // 通过串口打印连接wifi的信息

  WiFi.begin(ssid, password);     // 连接wifi信号

  while (WiFi.status() != WL_CONNECTED) {   // 判断wifi是否链接成功，
    delay(500);
    Serial.print(".");    // 连接失败，等待连接成功
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");   
  Serial.println(WiFi.localIP());   // 打印连接wifi成功的信息，并且获取设备的IP地址
}

/*
  功能：ESP32设备连接华为云平台
*/
void reconnect() {
  client.setServer(mqtt_server, mqtt_port);
  client.setKeepAlive (60); //设置心跳时间
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // ESP32客户端订阅华为云下发给ESP32客户端的命令
      // $oc/devices/{device_id}/sys/commands/request_id={request_id}
      client.subscribe("$oc/devices/67d78dceaa00d157701ab54e_ESP32_Device/sys/commands/request_id=%");  // 订阅主题
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


/*
  功能：华为云平台给ESP32发布信息时，就会调用这个回调函数
*/
void callback(char* topic, byte* payload, unsigned int length) {
  char down_command[200] = {0};
  char request_id[50] = {0};
  char cmd_topic[200];
  char *start_addr = NULL;

  // 处理华为云平台下发的信息
  memset(down_command, 0, sizeof(down_command));
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    down_command[i] = (char)payload[i];
  }
  // Serial.print((char *)payload);
  Serial.println();
  // 设备响应云平台
  // $oc/devices/67d78dceaa00d157701ab54e_ESP32_Device/sys/commands/response/request_id={request_id}
  start_addr = strstr(topic, "request_id");
  memset(request_id, 0, sizeof(request_id));
  strncpy(request_id,start_addr+11, 36);
  
  // $oc/devices/{device_id}/sys/commands/response/request_id={request_id}
  sprintf(cmd_topic, "$oc/devices/67d78dceaa00d157701ab54e_ESP32_Device/sys/commands/response/request_id=%s", request_id);
  Serial.println(cmd_topic);

  // ESP32设备给华为云服务器进行响应
  client.publish(cmd_topic, "{\"result_code\": 0,\"\": \"led\",\"paras\": {\"led\": \"success\"}}");

  // 解析华为云平台下发的JSON格式的命令字符串
  // 创建 StaticJsonDocument 对象，分配 200 字节内存
  JsonDocument doc;
  String jsonString = down_command;
  Serial.println(jsonString);
  // 解析 JSON
  DeserializationError error = deserializeJson(doc, jsonString);

  // 检查解析结果
  if (error) {
    Serial.print("JSON 解析失败: ");
    Serial.println(error.c_str());
    return;
  }
  // 获取JSON格式字符中命令的名字
  const char *cmd_string = doc["command_name"];
  // 字符串命令的比较
  if (!strcmp(cmd_string, "led1"))
  {
    bool paras_led1 = doc["paras"]["led1"];
    // 判断LED1灯的命令的状态，进行LED灯的控制
    if (paras_led1 == true) 
    {
      led_onoff(LED1_PIN, LED_ON);
      led1_state = 1;
    }
    else if (paras_led1 == false) 
    {
      led_onoff(LED1_PIN, LED_OFF);
      led1_state = 0;
    }
  }
  else if (!strcmp(cmd_string, "led2"))
  {
    bool paras_led2 = doc["paras"]["led2"];
    if (paras_led2 == true) 
    { 
      led_onoff(LED2_PIN, LED_ON);
      led2_state = 1;
    }
    else if (paras_led2 == false) 
    {
      led_onoff(LED2_PIN, LED_OFF);
      led2_state = 0;
    }
  }
  else if (!strcmp(cmd_string, "led3"))
  {
    bool paras_led3 = doc["paras"]["led3"];
    if (paras_led3 == true) 
    {
      led_onoff(LED3_PIN, LED_ON);
      led3_state = 1;
    }
    else if (paras_led3 == false) 
    {
      led_onoff(LED3_PIN, LED_OFF);
      led3_state = 0;
    }
  }
  else if (!strcmp(cmd_string, "led4"))
  {
    bool paras_led4 = doc["paras"]["led4"];
    if (paras_led4 == true) 
    {
      led_onoff(LED4_PIN, LED_ON);
      led4_state = 1;
    }
    else if (paras_led4 == false) 
    {
      led_onoff(LED4_PIN, LED_OFF);
      led4_state = 0;
    }
  }
  else if (!strcmp(cmd_string, "relay"))
  {
    bool paras_relay = doc["paras"]["relay"];
    if (paras_relay == true) 
    {
      relay_open();
      relay_state = 1;
    }
    else if (paras_relay == false) 
    {
      relay_close();
      relay_state = 0;
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  led_init();   // LED灯的初始化
  key_it_init();    // 按键中断初始化
  ds18b20_init();   // DS18B20初始化
  smg_init();       // 数码管初始化
  Serial.begin(115200, SERIAL_8N1);   // 串口初始化
  relay_init();     // 继电器初始化
  motor_init();     // 电机初始化
  adc_init();       // ADC初始化

  setup_wifi();   // 连接wifi

    
  // 设置MQTT客户端的回调函数，解析华为云下发的命令
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()) {  // ESP32设备连接华为云平台，并通过返回值判断客户端是否连接服务器
    reconnect();              // 客户端连接服务器
  }
  client.loop();

  // 测试DS18B20测量温度，并通过数码管显示
  float tempC = get_ds18b20_temp();   // 读取温度值
  smg_display(tempC);                 // 数码管显示温度

  Serial.print("current env temperature = ");
  Serial.print(tempC);
  Serial.println("℃");

  // 使用ADC读取滑动变阻器的模拟电压值
  float resValue = read_analog_vol(ADC_PIN);
  Serial.print("res voltage Value = ");
  Serial.print(resValue);
  Serial.println("V");
  // 使用ADC读取烟雾传感器的模拟电压值
  float smokeValue = read_analog_vol(SMOKE_PIN);
  Serial.print("smoke voltage Value = ");
  Serial.print(smokeValue);
  Serial.println("V");
  // 使用AD读取火焰传感器的模拟电压值
  float fireValue = read_analog_vol(FIRE_PIN);
  Serial.print("fire voltage Value = ");
  Serial.print(fireValue);
  Serial.println("V");

  // 简单测试继电器是否工作，最终通过云端下发命令控制继电器
  // relay_open();
  // delay(2000);
  // relay_close();
  // delay(2000);
  // 简单测试蜂鸣器是否工作，检测火焰浓度，实现蜂鸣器的报警
  if (fireValue < 0.5)
    beep_open(1000);
  else
    beep_close();
  // 简单测试电机是否可以工作，通过温度自动调节转速
  if (tempC > 25.0)
  {
    run_motor(tempC * 10 - 200);    // 温度每上升1度，控制电机的PWM占空比增加1%
  }
  else 
  {
    run_motor(0);
  }
  /*
    {
    "services": [{
      "service_id":"ESP32_Smart_Device",
      "properties":
      {
        "Temp":temperature,
        "led1":led1_state,
        "led2":led2_state,
        "led3":led3_state,
        "led4":led4_state,
        "relay":relay_state,
        "adc",adcValue,
        "fire":fireVal,
        "beep":beep_State,
        "smoke":smokeValue
      }
    }]
  }*/
  
  // 通过ArduinoJson类，构建JSON格式的字符串
  JsonDocument doc;

  // 准备设备上传到云平台的JSON格式的字符串
  JsonObject services_0 = doc["services"].add<JsonObject>();
  services_0["service_id"] = "ESP32_Smart_Device";

  JsonObject services_0_properties = services_0["properties"].to<JsonObject>();
  services_0_properties["Temp"] = tempC;
  services_0_properties["led1"] = led1_state;
  services_0_properties["led2"] = led2_state;
  services_0_properties["led3"] = led3_state;
  services_0_properties["led4"] = led4_state;
  services_0_properties["relay"] = relay_state;
  services_0_properties["adc"] = resValue;
  services_0_properties["fire"] = fireValue;
  services_0_properties["beep"] = beep_state;
  services_0_properties["smoke"] = smokeValue;
  doc.shrinkToFit();  // optional

  serializeJson(doc, Serial);
  Serial.println();
  // 创建一个缓冲区来存储序列化后的 JSON 字符串
  char jsonBuffer[512];

  // 将 JsonDocument 对象序列化为字符串并存储在 jsonBuffer 中
  serializeJson(doc, jsonBuffer);

  // 打印JSON字符串
  Serial.println(jsonBuffer);

  // ESP32客户服发布信息给华为云服务器
  // $oc/devices//67d78dceaa00d157701ab54e_ESP32_Device/sys/properties/report
  client.publish("$oc/devices/67d78dceaa00d157701ab54e_ESP32_Device/sys/properties/report", jsonBuffer);  // 发布主题
  delay(4000);    // 设置测量温度的时间的间隔
}











