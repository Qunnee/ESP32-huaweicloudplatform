#include "smg.h"

TM1637  mysmg = TM1637(CLK_PIN, DIO_PIN);

void smg_init(void)
{
  mysmg.init();
  mysmg.set();
}

// 功能：数码管显示
// 参数：数码管显示的数据
void smg_display(float value)
{
  float disData = value;
  uint32_t data = disData * 100;    // 将小数扩大100被  
  uint8_t smgSeg[4];
  smgSeg[0] = data / 1000;    // 提取千位
  smgSeg[1] = data % 1000 / 100;  // 提取百位
  smgSeg[2] = data % 100 / 10;    // 提取十位
  smgSeg[3] = data % 10;    // 提取各位

  for (int i = 0; i < 4; i++)
  {
    if (i == 1)
    {
      mysmg.point(true);
      mysmg.display(i, smgSeg[i]);
      mysmg.point(false);
    }
    else
    {
      mysmg.display(i, smgSeg[i]);
    }
  }
}