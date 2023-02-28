#ifndef _DEBUG

#define _DEBUG

#include <Arduino.h>
#include <motor.h>
#include <MsTimer2.h>
#include <arm.h>

void LaiHuiZhuan(void);
void moveright();
void moveleft();
void moveup();
void movedown();
void movestop();
void mode(char *X);
void bluetooth(char* pX);


#endif