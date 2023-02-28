#include "motor.h"
#include "debug.h"
#include "trace.h"

extern Servo Joint;
extern Servo Grab;
extern Servo Rotate;
extern int counter, counter_step;
extern float TARGET_L, TARGET_R;

extern int Sig_M;
extern int Sig_L1;
extern int Sig_L2;
extern int Sig_R1;
extern int Sig_R2;

int Arm_Position = 1;

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
        Arm_Up();
        break;
    case '2':
        Arm_Down();
        break;
    case '3':
        Arm_Open();
        break;
    case '4':
        Arm_Close();
        break;
    case '5':
        if (Arm_Position)
        {
            Arm_Lift();
            Arm_Position = 0;
        }
        else
        {
            Arm_Horizon();
            Arm_Position = 1;
        }
        break;
    case '6':
        /// 循迹模式
        
        break;

    default:
        break;
    }

    if (*X != '6')
        *X = '0';
}