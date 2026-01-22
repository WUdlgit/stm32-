#include "stm32f10x.h"

void AD_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable clocks for ADC1 and GPIOA (使能ADC1和GPIOA时钟)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    // Configure PA0 (ADC Channel 0) as analog input (将PA0配置为模拟输入模式)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//AIN模式下GPIO引脚不能用于其他功能,即无效(AIN模式是ADC的专属模式)
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ADC1 configuration (配置ADC1)
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // Configure ADC channel 0 (配置ADC通道0)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    // Enable ADC1 (使能ADC1)
    ADC_Cmd(ADC1, ENABLE);

    // Calibrate ADC1 (校准ADC1)
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void)
{
    // Start ADC1 Software Conversion (启动ADC1软件转换)
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // Wait until conversion is complete (等待转换完成)
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    // Return the converted value (返回转换值)
    return ADC_GetConversionValue(ADC1);
}
