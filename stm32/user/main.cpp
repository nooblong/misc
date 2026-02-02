#include "stm32f10x.h" // Device header
extern "C"
{
#include "Delay.h"
#include "OLED.h"
}

#include "Servo.h"
#include "Key.h"
#include "motor.h"
#include "PWM.h"
#include "IC.h"

int key;
float angle = 0;
float speed = 0;

int main(void)
{
	OLED_Init(); // OLED初始化
	Motor_Init(); // 电机初始化
	Key_Init();   // 按键初始化
	PWM_Init(); // PWM初始化
	IC_Init(); // 输入捕获初始化
	OLED_ShowString(1, 1, "Running");

	PWM_SetCompare1(5);   // 设置PWM占空比，50%
	OLED_ShowString(2, 1, "F:");
	OLED_ShowString(3, 1, "Duty:00%");
	while (1)
	{
		OLED_ShowNum(2, 3, IC_GetFreq(), 7); // 显示输入捕获频率
		OLED_ShowNum(3, 6, getDuty(), 2);     // 显示占空比
	
		key = Key_GetNum(); // 获取按键值
		if (key == 1)
		{
			speed += 20;
			if (speed > 100)
			{
				speed = -100;
			}
		}
		OLED_ShowString(4, 1, "Speed:");
    	OLED_ShowSignedNum(4, 8, speed, 3);
		Motor_SetSpeed(speed / 10); // 设置电机速度
	}
	

	// Servo_Init();		// 舵机初始化
	// Key_Init();		// 按键初始化
	// while (1)
	// {
	// 	key = Key_GetNum(); // 获取按键值
	// 	if (key == 1)
	// 	{
	// 		angle += 30;
	// 		if (angle > 180)
	// 		{
	// 			angle = 0;
	// 		}
			
	// 	}
	// 	Servo_SetAngle(angle); // 设置舵机角度
	// 	OLED_ShowString(1, 1, "Angle:");
	// 	OLED_ShowNum(1, 7, angle, 3);
	// }
}
