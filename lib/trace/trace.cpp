#include "trace.h"

int Sig_M = 1;
int Sig_L1 = 1;
int Sig_L2 = 1;
int Sig_R1 = 1;
int Sig_R2 = 1;

void Trace_Init()
{
    pinMode(Det_M, INPUT);
    pinMode(Det_L1, INPUT);
    pinMode(Det_L2, INPUT);
    pinMode(Det_R1, INPUT);
    pinMode(Det_R2, INPUT);
}

void Detect()
{
    Sig_M = digitalRead(Det_M);
    Sig_L1 = digitalRead(Det_L1);
    Sig_L2 = digitalRead(Det_L2);
    Sig_R1 = digitalRead(Det_R1);
    Sig_R2 = digitalRead(Det_R2);
}