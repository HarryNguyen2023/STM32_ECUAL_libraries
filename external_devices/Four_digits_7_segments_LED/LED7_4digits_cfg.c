#include "LED7_4digits.h"

const LED7_4digits LED7_4digits_param = 
{
    CC,
    {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6},
    {GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA},
    {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11},
    {GPIOA, GPIOA, GPIOA, GPIOA}
};