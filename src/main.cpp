#include <Arduino.h>
#include <motor.h>
#include <trace.h>
#include <arm.h>
#include <SoftwareSerial.h>

#define STR -14
#define LOW_F -12
#define LOW_L -8
#define MID_F -12
#define MID_L -2
#define FST_F -10
#define FST_L 0
#define EXT_F -10
#define EXT_L 8

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
int startPoint = 0;

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
    //MsTimer2::set(PERIOD, control);
    //MsTimer2::start();

    Serial.println("BT is ready!");//
    Serial3.begin(9600);//bluetooth

    analogWrite(PWML, 128);
    analogWrite(PWMR, 128);

    while(millis() < 3000){}
    Arm_Close();
    while(millis() < 5000){}
    Arm_Up();
    while(millis() < 7000){}

    analogWrite(PWML, 128 - 30);
    analogWrite(PWMR, 128 - 30);
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

   //! 注意:实际车头的方向与我们定义的相反！！
    /// 直行

    if (Sig_M == 1)
    {
        TARGET_L = STR;
        TARGET_R = STR;
    }
    /// 慢速转向
    if ((Sig_L1 == 1))
    {
        TARGET_L = LOW_L;
        TARGET_R = LOW_F;
    }
    if (Sig_R1 == 1)
    {
        TARGET_L = LOW_F;
        TARGET_R = LOW_L;
    }
    /// 中速转向
    if (Sig_L2 == 1)
    {
        TARGET_L = MID_L;
        TARGET_R = MID_F;
    }
    if (Sig_R2 == 1)
    {
        TARGET_L = MID_F;
        TARGET_R = MID_L;
    }
    
    ///快速转向
    if (Sig_L3 == 1)
    {
        TARGET_L = FST_L;
        TARGET_R = FST_F;
    }
    if (Sig_R3 == 1)
    {
        TARGET_L = FST_F;
        TARGET_R = FST_L;
    }
    ///极速转向
    if (Sig_L4 == 1)
    {
        TARGET_L = EXT_L;
        TARGET_R = EXT_F;
    }
    if (Sig_R4 == 1)
    {
        TARGET_L = EXT_F;
        TARGET_R = EXT_L;
    }
    
    /*/// 直角转向
    if (Sig_M == 1 && Sig_L1 == 1 && Sig_L2 == 1)
    {
        TARGET_L = 10;
        TARGET_R = -10;
    }
    if (Sig_M == 1 && Sig_R1 == 1 && Sig_R2 == 1)
    {
        TARGET_L = -10;
        TARGET_R = 10;
    }*/

    analogWrite(PWML, 128 + TARGET_L*5);
    analogWrite(PWMR, 128 + TARGET_R*5);
    
    /// 停止
    if ((Sig_M == 1 && Sig_L1 == 1 && Sig_L2 == 1&& Sig_R1 == 1 && Sig_R2 == 1) && millis() > 20000)
    {
        startPoint = millis();
        
        analogWrite(PWML, 128 + 30);
        analogWrite(PWMR, 128 - 30);

        delay(1500);
        
        analogWrite(PWML, 128);
        analogWrite(PWMR, 128);
        Arm_Down();
        
        delay(1500);
        
        Arm_Open();
        
        while(1){}
    }
        
}
