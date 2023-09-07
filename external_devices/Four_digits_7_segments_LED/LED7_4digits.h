#ifndef LED7_4DIGITS_H
#define LED7_4DIGITS_H

#include "stm32f1xx_hal.h"

// Define the type of LED
typedef enum
{
    CA,
    CC
}LED_Type;

// Structure for initialization for the GPIO pins to control the LED
typedef struct 
{
    LED_Type led_type;
    uint16_t leds_pin[7];
    GPIO_TypeDef* leds_port[7];
    uint16_t digits_pin[4];
    GPIO_TypeDef* digits_port[4];
}LED7_4digits;

void LED7_4Digits_Init(void);
void LED7_4Digits_Display(uint16_t number);

#endif