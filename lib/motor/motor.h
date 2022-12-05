#ifndef _MOTOR

#define _MOTOR

#include <Arduino.h>
#include <MsTimer2.h>

// 进入中断的时间间隔，单位为ms
#define PERIOD 100

// 电机1的编码器A项接Arduino 的2中断口，用子编码器计数
#define ENCODER_A_L 2
#define ENCODER_B_L 4
// 电机2的编码器A项接Arduino的3中断口，用于编码器计数
#define ENCODER_A_R 3
#define ENCODER_B_R 5

// 用于电机1的PWM输出，调节电机速度
#define PWML 9
// 用于电机2的PwM输出，调节电机速度
#define PWMR 10

void getEncoder_L(void);
void getEncoder_R(void);

int pidcontrol_L(float target, float current);
int pidcontrol_R(float target, float current);

void control_L();
void control_R();
void control(void);


#endif