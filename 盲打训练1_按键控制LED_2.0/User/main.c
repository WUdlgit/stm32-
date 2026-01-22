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
			LED_Turn();
		}
	}
}
