#include "main.h"


void GPIO_Init(void)
{ 
    GPIO_InitTypeDef LED = {0};
    LED.Pin = GPIO_PIN_5;
    LED.Mode = GPIO_MODE_INPUT;
    LED.Speed = GPIO_SPEED_HIGH;
    LED.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &LED);
}