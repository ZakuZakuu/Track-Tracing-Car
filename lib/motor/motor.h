#ifndef _MOTOR

#define _MOTOR

#include <Arduino.h>
#include <MsTimer2.h>

#define PERIOD 100

#define ENCODER_A_L 2 // 电机1的编码器A项接Arduino 的2中断口，用子编码器计数
#define ENCODER_B_L 4
#define ENCODER_A_R 3 // 电机2的编码器A项接Arduino的3中断口，用于编码器计数
#define ENCODER_B_R 5

#define PWML 9  // 用于电机1的PWM输出，调节电机速度
#define INL1 12 // 11和12引脚用于电机1的转动方向控制
#define INL2 11

#define PWMR 10 // 用于电机2的PwM输出，调节电机速度
#define INR1 6  // 6和8引脚用于电机2的转动方向控制
#define INR2 8

void getEncoder_L(void);
void getEncoder_R(void);

int pidcontrol_L(float target, float current);
int pidcontrol_R(float target, float current);

void control_L();
void control_R();
void control(void);

#endif