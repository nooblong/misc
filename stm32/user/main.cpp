#include "stm32f10x.h" // Device header
extern "C"
{
#include "Delay.h"
#include "OLED.h"
}

#include "Servo.h"
#include "Key.h"
#include "motor.h"

int key;
float angle = 0;
float speed = 0;

int main(void)
{
	OLED_Init(); // OLED初始化

	Motor_Init(); // 电机初始化
	Key_Init();   // 按键初始化
	Motor_SetSpeed(50); // 设置电机速度为50%
	OLED_ShowString(1, 1, "Running");
	while (1)
	{
		key = Key_GetNum(); // 获取按键值
		OLED_ShowString(3, 1, "Key:");
		OLED_ShowNum(3, 5, key, 1);
		if (key == 1)
		{
			speed += 20;
			if (speed > 100)
			{
				speed = -100;
			}
		}
		Motor_SetSpeed(speed); // 设置电机速度
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
