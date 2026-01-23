#include "stm32f10x.h"
#include "Servo.h"
#include "PWM.h"

void Servo_Init(void)
{
    PWM_Init();
    PWM_SetCompare1(1500); // 设置初始位置为中间位置，假设PWM周期为20ms，占空比为7.5%
}

void Servo_SetAngle(int angle)
{
    int pulseWidth = angle / 180 * 2000 + 500; // 计算对应的脉宽，单位为微秒
    PWM_SetCompare1(pulseWidth); // 设置PWM比较值
}
