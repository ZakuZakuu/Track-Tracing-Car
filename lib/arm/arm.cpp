#include "arm.h"

Servo Joint;
Servo Grab;

void Arm_Init()
{
    Joint.attach(JOINT_PIN);
    Grab.attach(GRAB_PIN);
    Joint.write(0);
    Grab.write(180);
}

void Arm_Up()
{
    Joint.write(0);
}

void Arm_Dowm()
{
    Joint.write(90);
}

void Arm_Close()
{
    Grab.write(180);
}

void Arm_Open()
{
    Grab.write(120);
}