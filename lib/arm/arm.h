#ifndef _ARM

#define _ARM
#include <Arduino.h>
#include<Servo_Hardware_PWM.h>

void Arm_Init();
void Arm_Up();
void Arm_Down();
void Arm_Close();
void Arm_Open();
void Arm_Horizon();
void Arm_Lift();

#define JOINT_PIN 10
#define GRAB_PIN 9
#define ROTATE_PIN 8

#endif