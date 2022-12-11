#include "arm.h"

Servo Joint;
Servo Grab;

inline void Arm_Init()
{
    Joint.attach(JOINT_PIN);
    Grab.attach(GRAB_PIN);
}

inline void Arm_Up()
{
    Joint.write(0);
}

inline void Arm_Up()
{
    Joint.write(90);
}

inline void Arm_Close()
{
    Grab.write(180);
}

inline void Arm_Close()
{
    Grab.write(120);
}