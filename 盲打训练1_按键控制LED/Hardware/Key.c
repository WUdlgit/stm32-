#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "LED.h"

/**
 * @brief 初始化按键
 *
 */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	/*
	GPIO_Speed 对输入口无效,只需要输出初始化时设置速度即可
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	*/
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
 * @brief 更新按键状态
 *
 * @return uint8_t 按键是否触发
 */
uint8_t Key_Updata(void)
{
	static uint8_t Last_State = 1; // 上一次读取（上拉输入，未按为1）
	uint8_t State = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);

	// 检测按下边沿（1 -> 0）
	if (Last_State == 1 && State == 0)
	{
		Delay_ms(20); // 消抖
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			Last_State = 0;
			return 1; // 一次触发
		}
	}

	// 检测松开，用于更新状态
	if (Last_State == 0 && State == 1)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
		{
			Last_State = 1;
		}
	}

	return 0;
}
