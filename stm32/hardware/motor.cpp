#include "stm32f10x.h"
#include "PWM.h"
extern "C"
{
#include "OLED.h"
}

void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA的时钟
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    PWM_Init();
}

void Motor_SetSpeed(int speed)
{
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;
    OLED_ShowString(2, 1, "Speed:");
    OLED_ShowSignedNum(2, 8, speed, 3);
    if (speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);   // IN1 高电平
        GPIO_ResetBits(GPIOA, GPIO_Pin_5); // IN2 低电平
        PWM_SetCompare3(speed*200);       // 设置PWM占空比
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_4); // IN1 低电平
        GPIO_SetBits(GPIOA, GPIO_Pin_5);   // IN2 高电平
        PWM_SetCompare3(-speed*200);      // 设置PWM占空比
    }
}
