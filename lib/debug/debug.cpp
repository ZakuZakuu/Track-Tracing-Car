#include "motor.h"

extern Servo Joint;
extern Servo Grab;
extern Servo Rotate;
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

    case '1':
        Joint.write(0);
        break;
    case '2':
        Joint.write(90);
        break;
    case '3':
        Grab.write(120);
        break;
    case '4':
        Grab.write(180);
        break;
    case '5':
        Rotate.write(0);
        break;
    case '6':
        Rotate.write(90);
        break;
    default:
        break;
    }
}