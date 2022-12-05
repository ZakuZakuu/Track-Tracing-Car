#include <Arduino.h>
#include <motor.h>

extern float velocity_L;
extern float velocity_R;

void setup()
{
    TCCR1B = TCCR1B & B11111000 | B00000001;    // 修改PWM输出频率

    pinMode(PWML, OUTPUT);
    pinMode(INL2, OUTPUT);
    pinMode(INL1, OUTPUT);

    pinMode(PWMR, OUTPUT);
    pinMode(INR2, OUTPUT);
    pinMode(INR1, OUTPUT);

    pinMode(ENCODER_A_L, INPUT);
    pinMode(ENCODER_B_L, INPUT);

    pinMode(ENCODER_A_R, INPUT);
    pinMode(ENCODER_B_R, INPUT);

    attachInterrupt(0, getEncoder_L, CHANGE);
    attachInterrupt(1, getEncoder_R, CHANGE);
    Serial.begin(9600);
    MsTimer2::set(PERIOD, control);
    MsTimer2::start();
}

void loop()
{
    //监测速度
    Serial.print("velocity_L: ");
    Serial.print(velocity_L);
    Serial.print("\t");
    Serial.print("velocity_R: ");
    Serial.print(velocity_R);
    Serial.print("\t\n");
}