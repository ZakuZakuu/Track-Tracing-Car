#include "motor.h"

extern int counter, counter_step;
extern float TARGET_L, TARGET_R;

void bluetooth(char* pX)
{
  if (Serial.available()) {
    *pX = Serial.read();
    Serial3.print(*pX);
  }

  if (Serial3.available()) {
    *pX = Serial3.read();
    Serial.print(*pX);
  }
}

void LaiHuiZhuan()
{
if (counter < 30 && counter > -30)
    {
        counter += counter_step;
        TARGET_L = counter;
        TARGET_R = counter;
    }
    else
    {
        counter_step = -counter_step;
        counter += counter_step;
        TARGET_L = counter;
        TARGET_R = counter;
    }
}


void mode(char X)
{
    switch (X)
    {
    case 'r':
        TARGET_L += 2.5;
        TARGET_R -= 2.5;
        break;
    case 'l':
        TARGET_L -= 2.5;
        TARGET_R += 2.5;
        break;
    case 'u':
        TARGET_L += 5;
        TARGET_R += 5;
        break;
    case 'd':
        TARGET_L -= 5;
        TARGET_R -= 5;
        break;
    case 's':
        TARGET_L = 0;
        TARGET_R = 0;
        break;
    case '1':
        break;
    case '2':
        break;
    case '3':
        break;
    default:
        break;
    }
}