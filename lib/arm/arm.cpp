#include "arm.h"

Servo Joint;
Servo Grab;
Servo Rotate;
volatile int GrabAngle = 110;

void Arm_Init()
{
    Joint.attach(JOINT_PIN);
    Grab.attach(GRAB_PIN);
    Rotate.attach(ROTATE_PIN);
    Joint.write(90);
    Grab.write(120);
    Rotate.write(0);
}

void Arm_Up()
{
    Joint.write(40);
}

void Arm_Down()
{
    Joint.write(90);
}

void Arm_Close()
{
    if (GrabAngle <= 170)
        GrabAngle += 10;
    else
        GrabAngle = 180;
    Grab.write(GrabAngle);
}

void Arm_Open()
{
    if (GrabAngle >= 130)
        GrabAngle -= 10;
    else
        GrabAngle = 120;
    Grab.write(GrabAngle);
}

void Arm_Horizon()
{
    Rotate.write(0);
}

void Arm_Lift()
{
    Rotate.write(90);
}