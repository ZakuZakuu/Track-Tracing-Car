#ifndef _ARM

#define _ARM
#include <Arduino.h>
#include <Servo.h>

void Arm_Init();
void Arm_Up();
void Arm_Dowm();
void Arm_Close();
void Arm_Open();


#define JOINT_PIN 6
#define GRAB_PIN 7

#endif