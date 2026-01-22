#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"

int main(void)
{
	LED_Init();
	Key_Init();
	
	while(1)
	{
		if (Key_Updata())
		{
			if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0))
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			}
			else
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
			}
		}
	}
}
