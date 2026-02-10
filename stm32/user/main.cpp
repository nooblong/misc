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
#include "Encoder.h"
#include "AD.h"

int key;
float angle = 0;
float speed = 0;
float voltage = 0;
int ad0 = 0;
int ad1 = 0;
int ad2 = 0;
int ad3 = 0;

int main(void)
{
	OLED_Init(); // OLED初始化
	Motor_Init(); // 电机初始化
	Key_Init();   // 按键初始化
	PWM_Init(); // PWM初始化
	IC_Init(); // 输入捕获初始化
	Encoder_Init(); // 编码器初始化
	AD_Init(); // AD初始化

	while (1)
	{
		OLED_ShowString(1, 1, "ad0:");
		OLED_ShowNum(1, 5, AD_GetValue(ADC_Channel_0), 4);
		voltage = AD_GetValue(ADC_Channel_0) * 3.3 / 4095;
		
		OLED_ShowString(2, 1, "ad1:");
		OLED_ShowNum(2, 5, AD_GetValue(ADC_Channel_1), 4);
		OLED_ShowString(3, 1, "ad2:");
		OLED_ShowNum(3, 5, AD_GetValue(ADC_Channel_2), 4);
		OLED_ShowString(4, 1, "ad3:");
		OLED_ShowNum(4, 5, AD_GetValue(ADC_Channel_3), 4);
	}
	
	// while (1)
	// {
	// 	OLED_ShowString(2, 1, "CNT:");
	// 	OLED_ShowNum(2, 5, Encoder_GetCount(), 5);
	// }
	


	// PWM_SetCompare1(5);   // 设置PWM占空比，50%
	// OLED_ShowString(2, 1, "F:");
	// OLED_ShowString(3, 1, "Duty:00%");
	// while (1)
	// {
	// 	OLED_ShowNum(2, 3, IC_GetFreq(), 7); // 显示输入捕获频率
	// 	OLED_ShowNum(3, 6, getDuty(), 2);     // 显示占空比
	
	// 	key = Key_GetNum(); // 获取按键值
	// 	if (key == 1)
	// 	{
	// 		speed += 20;
	// 		if (speed > 100)
	// 		{
	// 			speed = -100;
	// 		}
	// 	}
	// 	OLED_ShowString(4, 1, "Speed:");
    // 	OLED_ShowSignedNum(4, 8, speed, 3);
	// 	Motor_SetSpeed(speed / 10); // 设置电机速度
	// }
	

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
