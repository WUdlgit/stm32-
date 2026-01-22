#include "stm32f10x.h" // Device header
#include "Delay.h"

typedef enum
{
	KEY_OFF = 0,
	KEY_ON = 1,
} Key_State;

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
	static Key_State key_state = KEY_OFF;
	uint8_t key_flag = 0;

	if (key_state == KEY_OFF)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_RESET)
		{
			Delay_ms(20);
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_RESET)
			{
				key_state = KEY_ON;
				key_flag = 1;
			}
		}
	}
	else if (key_state == KEY_ON)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_SET)
		{
			Delay_ms(20);
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_SET)
			{
				key_state = KEY_OFF;
			}
		}
	}

	return key_flag;
}
