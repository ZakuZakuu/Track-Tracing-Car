#include "trace.h"

int Sig_M = 1;
int Sig_L1 = 1;
int Sig_L2 = 1;
int Sig_R1 = 1;
int Sig_R2 = 1;
int last=0;

int Sig_L3 = 1;
int Sig_L4 = 1;
int Sig_R3 = 1;
int Sig_R4 = 1;


void Trace_Init()
{
    pinMode(Det_M, INPUT);
    pinMode(Det_L1, INPUT);
    pinMode(Det_L2, INPUT);
    pinMode(Det_R1, INPUT);
    pinMode(Det_R2, INPUT);

    pinMode(Det_L3, INPUT);
    pinMode(Det_L4, INPUT);
    pinMode(Det_R3, INPUT);
    pinMode(Det_R4, INPUT);
}

void Detect()
{
    Sig_M = digitalRead(Det_M);
    Sig_L1 = digitalRead(Det_L1);
    Sig_L2 = digitalRead(Det_L2);
    Sig_R1 = digitalRead(Det_R1);
    Sig_R2 = digitalRead(Det_R2);

    Sig_L3 = digitalRead(Det_L3);
    Sig_L4 = digitalRead(Det_L4);
    Sig_R3 = digitalRead(Det_R3);
    Sig_R4 = digitalRead(Det_R4);
}