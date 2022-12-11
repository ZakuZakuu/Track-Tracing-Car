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

void moveright()
{
    TARGET_L = 5;
    TARGET_R = 0;
}

void moveleft()
{
    TARGET_L = 0;
    TARGET_R = 5;
}

void moveup()
{
    TARGET_L = 5;
    TARGET_R = 5;
}

void movedown()
{
    TARGET_L = -5;
    TARGET_R = -5;
}

void movestop()
{
    TARGET_L = 0;
    TARGET_R = 0;
}

void mode(char X)
{
    switch (X)
    {
    case 'r':
        moveright();
        break;
    case 'l':
        moveleft();
        break;
    case 'u':
        moveup();
        break;
    case 'd':
        movedown();
        break;
    case 's':
        movestop();
        break;
    default:
        break;
    }
}