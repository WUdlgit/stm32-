#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"

int main(void)
{
	OLED_Init();
	
	Serial_Init();
	
	//Serial_SendByte(0x41);
	
//	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
//	Serial_SendArray(MyArray, 4);
	
//	Serial_SendString("HelloWolrd!\r\n");
	
	//Serial_SendNumber(12345,5);
	
	//printf("Num = %d\r\n",666);
	
//	char String[100];
//	sprintf(String, "Num = %d\r\n",666);
//	Serial_SendString(String);
	
	Serial_printf("ÄãºÃ,ÊÀ½ç");
	
	while (1)
	{
		
	}
}
