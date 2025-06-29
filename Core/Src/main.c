// #include "main.h"
#include "config.h"
#include "stm32f4xx_hal.h"

void main()
{
    GPIO_Init();
    while(1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(100);
    }
}