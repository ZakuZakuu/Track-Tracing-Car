#include "motor.h"

volatile float TARGET_L = 20; // 定义电机1的日标速度值
volatile float TARGET_R = 20; // 定义电机2的目标速度值
volatile float encoderVal_L;  // 在中断里面使用的全局变量需萎定义成volatile类型
volatile float encoderVal_R;
volatile float velocity_L;
volatile float velocity_R;

volatile float uL = 0;
volatile float uR = 0;

volatile float Lel;   // 电机1当前时刻的误差e(k)
volatile float Lell;  // 上一时刻的误差e(k-1)
volatile float Lelll; // 上上时刻的误差e(k-2)
volatile int Loutput;

volatile float Rel;   // 电机2当前时刻的误差e(k)
volatile float Rell;  // 上一时刻的误差e(k-1)
volatile float Relll; // 上上时刻的诱差e(k-2)
volatile int Routput;

/*
 @brief 获取电机1的编码器值
*/
void getEncoder_L(void)
{
    if (digitalRead(ENCODER_A_L) == LOW)
    {
        if (digitalRead(ENCODER_B_L) == LOW)
        {
            encoderVal_L--;
        }
        else
        {
            encoderVal_L++;
        }
    }
    else
    {
        if (digitalRead(ENCODER_B_L) == LOW)
        {
            encoderVal_L++;
        }
        else
        {
            encoderVal_L--;
        }
    }
}

/*
 @brief 获取电机2的编码器值
*/
void getEncoder_R(void)
{
    if (digitalRead(ENCODER_A_R) == LOW)
    {
        if (digitalRead(ENCODER_B_R) == LOW)
        {
            encoderVal_R--;
        }
        else
        {
            encoderVal_R++;
        }
    }
    else
    {
        if (digitalRead(ENCODER_B_R) == LOW)
        {
            encoderVal_R++;
        }
        else
        {
            encoderVal_R--;
        }
    }
}

/// ---------------------------------------------------------------------------- ///

/*
    @brief 电机1的PID算法
    @param target 目标速度
    @param current 当前速度
*/
int pidcontrol_L(float target, float current)
{
    Lel = target - current;
    float kp = 6, TI = 100, TD = 15, T = PERIOD;
    float q0 = kp * (1 + T / TI + TD / T);
    float q1 = -kp * (1 + 2 * TD / T);
    float q2 = kp * TD / T;
    uL = uL + q0 * Lel + q1 * Lell + q2 * Lelll;
    Lelll = Lell;
    Lell = Lel;
    if (uL > 255)
    {
        uL = 255;
    }
    Loutput = uL;
    return (int)Loutput;
}

/*
    @brief 电机2的PID算法
    @param target 目标速度
    @param current 当前速度
*/
int pidcontrol_R(float target, float current)
{
    Rel = target - current;
    float kp = 6, TI = 100, TD = 15, T = PERIOD;
    float q0 = kp * (1 + T / TI + TD / T);
    float q1 = -kp * (1 + 2 * TD / T);
    float q2 = kp * TD / T;
    uR = uR + q0 * Rel + q1 * Rell + q2 * Relll;
    Relll = Rell;
    Rell = Rel;
    if (uR > 255)
    {
        uR = 255;
    }
    Routput = uR;
    return (int)Routput;
}

/// ---------------------------------------------------------------------------- ///

/*
    @brief 电机1速度和方向控制
*/
void control_L()
{
    velocity_L = (encoderVal_L / 780) * 3.1415 * 2.0 * (1000 / PERIOD);

    Loutput = pidcontrol_L(TARGET_L, velocity_L);
    if (Loutput > 0)
    {
        analogWrite(PWML, 128 + 0.5*Loutput);
    }
    else
    {
        analogWrite(PWML, 128 - 0.5*Loutput);
    }
    encoderVal_L = 0;
}

/*
    @brief 电机2速度和方向控制
*/
void control_R()
{
    velocity_R = (encoderVal_R / 780) * 3.1415 * 2.0 * (1000 / PERIOD);

    Loutput = pidcontrol_R(TARGET_R, velocity_R);
    if (Routput > 0)
    {
        analogWrite(PWMR, 128 + 0.5*Routput);
    }
    else
    {
        analogWrite(PWMR, 128 + 0.5*Routput);
    }
    encoderVal_R = 0;
}

/// ---------------------------------------------------------------------------- ///

/*
    @brief 电机1、2的控制封装
*/
void control(void)
{
    control_L();
    control_R();
}

/// ---------------------------------------------------------------------------- ///
