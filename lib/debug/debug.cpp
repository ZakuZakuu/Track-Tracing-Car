#include "motor.h"

extern Servo Joint;
extern Servo Grab;
extern int counter, counter_step;
extern float TARGET_L, TARGET_R;

void bluetooth(char* pX)
{
    /*if (Serial.available()) {
        *pX = Serial.read();
        Serial3.print(*pX);
    }*/

  if (Serial3.available()) {
        *pX = Serial3.read();
        Serial.print(*pX);
        mode(pX);
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


void mode(char *X)
{
    switch (*X)
    {
    case 'r':
        TARGET_L = 5;
        TARGET_R = -5;
        *X = '0';
        break;
    case 'l':
        TARGET_L = -5;
        TARGET_R = 5;
        *X = '0';
        break;
    case 'u':
        TARGET_L = 10;
        TARGET_R = 10;
        *X = '0';
        break;
    case 'd':
        TARGET_L = -10;
        TARGET_R = -10;
        *X = '0';
        break;
    case 's':
        TARGET_L = 0;
        TARGET_R = 0;
        *X = '0';
        break;

    //todo 修改下面的代码，不使用Servo库
    case 'I':
        pinMode(PWML, INPUT);
        Joint.write(0);
        pinMode(PWML, OUTPUT);
        break;
    case 'L':
        pinMode(PWML, INPUT);
        Joint.write(90);
        pinMode(PWML, OUTPUT);
        break;
    case 'g':
        pinMode(PWML, INPUT);
        Grab.write(120);
        pinMode(PWML, OUTPUT);
        break;
    case 'h':
        pinMode(PWML, INPUT);
        Grab.write(180);
        pinMode(PWML, OUTPUT);
        break;
    default:
        break;
    }
}