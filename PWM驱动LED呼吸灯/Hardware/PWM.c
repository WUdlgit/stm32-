#include "stm32f10x.h"

void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable clock for TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable clock for GPIOA

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // Pin 0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Speed
    GPIO_Init(GPIOA, &GPIO_InitStructure); // Initialize GPIOA

    TIM_InternalClockConfig(TIM2); // Set TIM2 to internal clock

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1; // Prescaler
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // Up counting mode
    TIM_TimeBaseStructure.TIM_Period = 100 - 1; // Auto-reload value
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // Clock division
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // Initialize TIM2


    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); // Initialize structure with default values
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // PWM mode
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // Enable output
    TIM_OCInitStructure.TIM_Pulse = 0; // Compare value
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // High polarity
    TIM_OC1Init(TIM2, &TIM_OCInitStructure); // Initialize TIM2 channel 1

    TIM_Cmd(TIM2, ENABLE); // Start TIM2
}

void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare); // Set compare value for channel 1
}
