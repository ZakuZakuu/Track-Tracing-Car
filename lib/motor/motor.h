#ifndef _MOTOR

#define _MOTOR

#include <Arduino.h>
#include <MsTimer2.h>
#include <debug.h>
#include <math.h>

#define PERIOD 50

#define FORWARD 1 // 旋转方向，正为1，反为-1

#define ENCODER_A_L 2 // 电机1的编码器A项接Arduino的2引脚（中断口0），用子编码器计数
#define ENCODER_B_L 4
#define ENCODER_A_R 3 // 电机2的编码器A项接Arduino的3引脚（中断口1），用于编码器计数
#define ENCODER_B_R 5

#define PWML 11 // 用于电机1的PWM输出，调节电机速度
#define PWMR 12 // 用于电机2的PwM输出，调节电机速度

void getEncoder_L(void);
void getEncoder_R(void);

int pidcontrol_L(float target, float current);
int pidcontrol_R(float target, float current);

void control_L();
void control_R();
void control(void);

#endif