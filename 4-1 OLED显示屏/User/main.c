#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();
	
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"ASD");
	OLED_ShowNum(2,1,12345,5);
	OLED_ShowSignedNum(2,7,11,2);
	OLED_ShowHexNum(3,1,0XAA55,4);
	OLED_ShowBinNum(4,1,0XAA55,16);     //这里输出的二进制数在函数中要用十六进制表示，这个十六进制表示的二进制数是十六位，所以长度为16
	
	OLED_Clear();
	
	while (1)
	{
		
	}
}
