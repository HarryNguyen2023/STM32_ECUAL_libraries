#include "LED7_4digits.h"
#include "LED7_4digits_cfg.h"

// Hexadicmal code to display the number on 7 segments LED
volatile static uint8_t hexadecimal_code[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// Variables
static uint8_t decimal_digit;
static uint8_t dozen_digit;
static uint8_t hundred_digit;
static uint8_t thousand_digit;

// Static function prototypes
static void sevenSegmentDisplay(uint8_t hexa_code);

// ---------------------------------------------- Static functions hidden from users -----------------------------------------------

// Function to display a specific number on the LED
static void sevenSegmentDisplay(uint8_t hexa_code)
{
    switch(LED7_4digits_params.led_type)
    {
        case CC:
            for(int i = 0; i < 7; ++i)
            {
                if((hexa_code >> i) & 0x01 == 1)
                    HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 1);
                else
                    HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 0);
            }
            break;
        case CA:
            for(int i = 0; i < 7; ++i)
            {
                if((hexa_code >> i) & 0x01 == 1)
                    HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 0);
                else
                    HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 1);
            }
            break;
    }
    return;
}

// -------------------------------------------------- General functions to be used by users ------------------------------------------------------

// Function to initiate the pins to control the 4-digit-7-segment LED
void LED7_4Digits_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // Initiate the pins to bright the LED
    for(uint8_t i = 0; i < 7; ++i)
    {
        if(LED7_4digits_params.led_type == CC)
            HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 0);
        else if(LED7_4digits_params.led_type == CA)
            HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 1);
        if(LED7_4digits_params.leds_port[i] == GPIOA)
            __HAL_RCC_GPIOA_CLK_ENABLE();
        else if(LED7_4digits_params.leds_port[i] == GPIOB)
            __HAL_RCC_GPIOB_CLK_ENABLE();
        else if(LED7_4digits_params.leds_port[i] == GPIOC)
            __HAL_RCC_GPIOC_CLK_ENABLE();
        else if(LED7_4digits_params.leds_port[i] == GPIOD)
            __HAL_RCC_GPIOD_CLK_ENABLE();
        else if(LED7_4digits_params.leds_port[i] == GPIOE)
            __HAL_RCC_GPIOE_CLK_ENABLE();
        GPIO_InitStruct.Pin = LED7_4digits_params.leds_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(LED7_4digits_params.leds_port[i], &GPIO_InitStruct);
    }
    // Initiate the pins to control the led digits
    for(uint8_t i = 0; i < 4; ++i)
    {
        HAL_GPIO_WritePin(LED7_4digits_params.leds_port[i], LED7_4digits_params.leds_pin[i], 0);
        if(LED7_4digits_params.digits_port[i] == GPIOA)
            __HAL_RCC_GPIOA_CLK_ENABLE();
        else if(LED7_4digits_params.digits_port[i] == GPIOB)
            __HAL_RCC_GPIOB_CLK_ENABLE();
        else if(LED7_4digits_params.digits_port[i] == GPIOC)
            __HAL_RCC_GPIOC_CLK_ENABLE();
        else if(LED7_4digits_params.digits_port[i] == GPIOD)
            __HAL_RCC_GPIOD_CLK_ENABLE();
        else if(LED7_4digits_params.digits_port[i] == GPIOE)
            __HAL_RCC_GPIOE_CLK_ENABLE();
        GPIO_InitStruct.Pin = LED7_4digits_params.digits_pin[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(LED7_4digits_params.digits_port[i], &GPIO_InitStruct);
    }
}

// Function to display specific number on the LED
void LED7_4Digits_Display(uint16_t number)
{
    // Get all the digits of the number
    decimal_digit = number % 10;
    dozen_digit = (number / 10) % 10;
    hundred_digit = (number / 100) % 10;
    thousand_digit = number / 1000;

    // Continuously switch the LEDs and display the respective digits
    for(uint8_t i = 0; i < 4; ++i)
    {
        // Turn on the LEDs to be displayed
        HAL_GPIO_WritePin(LED7_4digits_params.digits_port[i], LED7_4digits_params.digits_pin[i], 1);
        // Display the digit on the respective LED
        if(i == 0)
            sevenSegmentDisplay(hexadecimal_code[decimal_digit]);
        else if(i == 1)
            sevenSegmentDisplay(hexadecimal_code[dozen_digit]);
        else if(i == 2)
            sevenSegmentDisplay(hexadecimal_code[hundred_digit]);
        else
            sevenSegmentDisplay(hexadecimal_code[thousand_digit]);
        // Delay for a while
        HAL_Delay(10);
        // Turn off the LED 
        HAL_GPIO_WritePin(LED7_4digits_params.digits_port[i], LED7_4digits_params.digits_pin[i], 0);
    }
}

