#include "arm.h"

Servo Joint;
Servo Grab;

void Arm_Init()
{
    Joint.attach(JOINT_PIN);
    Grab.attach(GRAB_PIN);
    Joint.write(90);
    Grab.write(120);
}

void Arm_Up()
{
    Joint.write(0);
}

void Arm_Down()
{
    Joint.write(90);
}

void Arm_Close()
{
    Grab.write(170);
}

void Arm_Open()
{
    Grab.write(120);
}