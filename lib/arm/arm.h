#ifndef _ARM

#define _ARM
#include <Arduino.h>
#include<Servo_Hardware_PWM.h>

void Arm_Init();
void Arm_Up();
void Arm_Dowm();
void Arm_Close();
void Arm_Open();


#define JOINT_PIN 10
#define GRAB_PIN 9
#define ROTATE_PIN 8

#endif