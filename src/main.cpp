#include <Arduino.h>
#include <motor.h>
#include <trace.h>
#include <arm.h>
#include <SoftwareSerial.h>

char X='6';                              //定义一个变量存数据。

extern float TARGET_L;
extern float TARGET_R;
extern float velocity_L;
extern float velocity_R;
extern int Sig_M;
extern int Sig_L1;
extern int Sig_L2;
extern int Sig_R1;
extern int Sig_R2;
extern int last;

extern int Sig_L3;
extern int Sig_L4;
extern int Sig_R3;
extern int Sig_R4;

int Trace_On = 0;

void setup()
{
    TCCR1B = TCCR1B & B11111000 | B00000001;    // 修改PWM输出频率
    TCCR1C = TCCR1C & B11111000 | B00000001;    // 修改PWM输出频率

    pinMode(PWML, OUTPUT);
    pinMode(PWMR, OUTPUT);

    pinMode(ENCODER_A_L, INPUT);
    pinMode(ENCODER_B_L, INPUT);

    pinMode(ENCODER_A_R, INPUT);
    pinMode(ENCODER_B_R, INPUT);

    Arm_Init();
    Trace_Init();

    attachInterrupt(0, getEncoder_L, CHANGE);
    attachInterrupt(1, getEncoder_R, CHANGE);
    Serial.begin(9600);
    MsTimer2::set(PERIOD, control);
    MsTimer2::start();

    Serial.println("BT is ready!");//
    Serial3.begin(9600);//bluetooth

}

void loop()
{
    Detect();
    
    /*
    Serial.print("velocity_L: ");
    Serial.print(velocity_L);
    Serial.print("\t");
    Serial.print("velocity_R: ");
    Serial.print(velocity_R);
    Serial.print("\t\n");
    Serial.print("mode: ");
    Serial.print(X);
    Serial.print(" Det_M: ");
    Serial.print(Sig_M);
    Serial.print("\t\n");
    */

    Serial.print("M");
    Serial.print(Sig_M);
    Serial.print("  L1 ");
    Serial.print(Sig_L1);
    Serial.print("  L2 ");
    Serial.print(Sig_L2);
    Serial.print("  R1 ");
    Serial.print(Sig_R1);
    Serial.print("  R2 ");
    Serial.print(Sig_R2);
    Serial.print("  L3 ");
    Serial.print(Sig_L3);
    Serial.print("  L4 ");
    Serial.print(Sig_L4);
    Serial.print("  R3 ");
    Serial.print(Sig_R3);
    Serial.print("  R4 ");
    Serial.print(Sig_R4);
    Serial.println("  ");

    if (X == '6')
    {
        Trace_On = !Trace_On;
        X = '0';
    }

    if (Trace_On)
    {
        //! 注意:实际车头的方向与我们定义的相反！！
        /// 停止
        double v=3;
        int t=1;
        if ((Sig_M == 1 && Sig_L1 == 1 && Sig_R1 == 1 && Sig_L2 == 1 && Sig_R2 == 1))
        {
            TARGET_L = 0;
            TARGET_R = 0;
        }
        /// 慢速转向
        else if ((Sig_M == 0 && Sig_R1 == 0 && Sig_L1 == 1 && Sig_L2 == 0 && Sig_R2 == 0) || (Sig_M == 1 && Sig_R1 == 0 && Sig_L1 == 1 && Sig_L2 == 0 && Sig_R2 == 0))
        {
            TARGET_L = v;
            TARGET_R = -2*v;
            delay(t);
        }
        else if ((Sig_M == 0 && Sig_R1 == 1 && Sig_L1 == 0 && Sig_L2 == 0 && Sig_R2 == 0) || (Sig_M == 1 && Sig_R1 == 1 && Sig_L1 == 0 && Sig_L2 == 0 && Sig_R2 == 0))
        {
            TARGET_L = -2*v;
            TARGET_R = v;
            delay(t);
        }
        /// 快速转向
        else if ((Sig_M == 0 && Sig_R1 == 0 && Sig_L1 == 1 && Sig_L2 == 1 && Sig_R2 == 0) || (Sig_M == 0 && Sig_R1 == 0 && Sig_L1 == 0 && Sig_L2 == 1 && Sig_R2 == 0))
        {
            TARGET_L = 6*v;
            TARGET_R = -6*v;
            delay(t);
        }
        else if ((Sig_M == 0 && Sig_R1 == 1 && Sig_L1 == 0 && Sig_L2 == 0 && Sig_R2 == 1) || (Sig_M == 0 && Sig_R1 == 0 && Sig_L1 == 0 && Sig_L2 == 0 && Sig_R2 == 1))
        {
            TARGET_L = -6*v;
            TARGET_R = 6*v;
            delay(t);
        }
        /// 直角转向
        else if (Sig_M == 1 && Sig_L1 == 1 && Sig_L2 == 1)
        {
            TARGET_L = 8*v;
            TARGET_R = -8*v;
            last=1;
            delay(t);
        }
        else if (Sig_M == 1 && Sig_R1 == 1 && Sig_R2 == 1)
        {
            TARGET_L = -8*v;
            TARGET_R = 8*v;
            last=-1;
            delay(t);
        }
        /// 直行
        else if ((Sig_M == 1 && Sig_R1 == 0 && Sig_L1 == 0 && Sig_L2 == 0 && Sig_R2 == 0) || (Sig_M == 1 && Sig_R1 == 1 && Sig_L1 == 1 && Sig_L2 == 0 && Sig_R2 == 0) || (Sig_M == 0 && Sig_L1 == 0 && Sig_R1 == 0 && Sig_L2 == 0 && Sig_R2 == 0))
        {
            TARGET_L = -2*v;
            TARGET_R = -2*v;
        }
        else if (Sig_M == 0 && Sig_R1 == 0 && Sig_L1 == 0 && Sig_L2 == 0 && Sig_R2 == 0)
        {
            TARGET_L = 15*last;
            TARGET_R = -15*last;
        }
    }
    else
    {
        bluetooth(&X);
    }
}
