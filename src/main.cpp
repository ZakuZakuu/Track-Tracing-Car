#include <Arduino.h>
#include <motor.h>
#include <trace.h>
#include <arm.h>
#include <SoftwareSerial.h>

char X;                              //定义一个变量存数据。

extern float TARGET_L;
extern float TARGET_R;
extern float velocity_L;
extern float velocity_R;

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
    /*
    Serial.print("velocity_L: ");
    Serial.print(velocity_L);
    Serial.print("\t");
    Serial.print("velocity_R: ");
    Serial.print(velocity_R);
    Serial.print("\t\n");
    */
}
