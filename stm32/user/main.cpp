#include "stm32f10x.h" // Device header
extern "C"
{
#include "Delay.h"
#include "OLED.h"
}

#include "Servo.h"
#include "Key.h"

int key;
float angle = 0;

int main(void)
{
	/*模块初始化*/
	OLED_Init(); // OLED初始化
	Servo_Init();		// 舵机初始化
	Key_Init();		// 按键初始化
	while (1)
	{
		key = Key_GetNum(); // 获取按键值
		if (key == 1)
		{
			angle += 30;
			if (angle > 180)
			{
				angle = 0;
			}
			
		}
		Servo_SetAngle(angle); // 设置舵机角度
		OLED_ShowString(1, 1, "Angle:");
		OLED_ShowNum(1, 7, angle, 3);
	}
}
