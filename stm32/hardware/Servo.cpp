#include "stm32f10x.h"
#include "Servo.h"
#include "PWM.h"

void Servo_Init(void)
{
    PWM_Init();
}

void Servo_SetAngle(int angle)
{
    int pulseWidth = ((angle * 2000) / 180) + 500; // 计算对应的脉宽，单位为微秒
    PWM_SetCompare3(pulseWidth); // 设置PWM比较值
}
