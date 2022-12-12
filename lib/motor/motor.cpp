#include "motor.h"

volatile float TARGET_L = 0; // 定义电机1的日标速度值
volatile float TARGET_R = 0; // 定义电机2的目标速度值
volatile float encoderVal_L;  // 在中断里面使用的全局变量需萎定义成volatile类型
volatile float encoderVal_R;
volatile float velocity_L;
volatile float velocity_R;

volatile float uL = 0;
volatile float LeI;   // 电机1当前时刻的误差e(k)
volatile float LeII;  // 上一时刻的误差e(k-1)
volatile float LeIII; // 上上时刻的误差e(k-2)
volatile int Loutput;

volatile float uR = 0;
volatile float ReI;   // 电机2当前时刻的误差e(k)
volatile float ReII;  // 上一时刻的误差e(k-1)
volatile float ReIII; // 上上时刻的诱差e(k-2)
volatile int Routput;

volatile int counter = 0;
volatile int counter_step = 1;

/*
 @brief 获取电机2的编码器值
 @param 倍率 采用双边缘触发中断，为2倍频
 @param 脉冲数 电机一圈产生13个脉冲信号，减速比为1:30，2倍频，实际转一圈产生13*30=780个脉冲
*/
void getEncoder_L(void)
{
    if (digitalRead(ENCODER_A_L) == LOW)
    {
        if (digitalRead(ENCODER_B_L) == LOW)
            encoderVal_L += FORWARD;
        else
            encoderVal_L -= FORWARD;
    }
    else
    {
        if (digitalRead(ENCODER_B_L) == LOW)
            encoderVal_L -= FORWARD;
        else
            encoderVal_L += FORWARD;
    }
}

/*
 @brief 获取电机2的编码器值
 @param 倍率 采用双边缘触发中断，为2倍频
 @param 脉冲数 电机一圈产生13个脉冲信号，减速比为1:30，2倍频，实际转一圈产生2*13*30=780个脉冲
*/
void getEncoder_R(void)
{
    if (digitalRead(ENCODER_A_R) == LOW)
    {
        if (digitalRead(ENCODER_B_R) == LOW)
            encoderVal_R += FORWARD;
        else
            encoderVal_R -= FORWARD;
    }
    else
    {
        if (digitalRead(ENCODER_B_R) == LOW)
            encoderVal_R -= FORWARD;
        else
            encoderVal_R += FORWARD;
    }
}

/// ---------------------------------------------------------------------------- ///

/*
    @brief 电机1的增量式PID算法，
    @param target 目标速度
    @param curRent 当前速度
*/
int pidcontrol_L(float target, float current)
{
    LeI = target - current;
    float kp = 1.5, TI = 100, TD = 30, T = PERIOD;
    float q0 = kp * (1 + T / TI + TD / T);
    float q1 = -kp * (1 + 2 * TD / T);
    float q2 = kp * TD / T;
    uL = uL + q0 * LeI + q1 * LeII + q2 * LeIII;
    LeIII = LeII;
    LeII = LeI;
    if (uL > 128)
    {
        uL = 128;
    }
    Loutput = uL;
    return (int)Loutput;
}

/*
    @brief 电机2的增量式PID算法
    @param target 目标速度
    @param curRent 当前速度
*/
int pidcontrol_R(float target, float current)
{
  ReI = target - current;
  float kp = 1.5, TI = 100, TD = 30, T = PERIOD;
  float q0 = kp*(1 + T/TI + TD/T);
  float q1 = -kp*(1 + 2*TD/T);
  float q2 = kp*TD/T;
  uR = uR + q0*ReI + q1*ReII + q2*ReIII;
  ReIII =ReII;
  ReII = ReI;
  if (uR > 128)
  {
    uR = 128;
  }
  Routput = uR;
  return (int)Routput;
}

/// ---------------------------------------------------------------------------- ///

/*
    @brief 电机1速度和方向控制
    @param velocity 检测到的速度
*/
void control_L()
{
    velocity_L = -(encoderVal_L / 780) * (1000 / PERIOD) * 3.1415 * 2.0;
    Loutput = pidcontrol_L(TARGET_L, velocity_L);
    analogWrite(PWML, 128 + Loutput);
    encoderVal_L = 0;
}

/*
    @brief 电机2速度和方向控制
*/
void control_R()
{
    velocity_R = (encoderVal_R / 780) * (1000 / PERIOD) * 3.1415 * 2.0;
    Routput = pidcontrol_R(TARGET_R, velocity_R);
    analogWrite(PWMR, 128 + Routput);
    encoderVal_R = 0;
}

/// ---------------------------------------------------------------------------- ///

/*
    @brief 电机1、2的控制封装
*/
void control(void)
{
    //LaiHuiZhuan();
    control_L();
    control_R();
}

/// ---------------------------------------------------------------------------- ///
