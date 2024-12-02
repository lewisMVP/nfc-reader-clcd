#ifndef __CLCD_H
#define __CLCD_H

#include "stm32f1xx_hal.h"

// LCD Pins (PB0 - PB5)
#define RS_PIN GPIO_PIN_5
#define EN_PIN GPIO_PIN_4
#define DATA_PINS (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)
#define LCD_PORT GPIOB

// Function prototypes
void CLCD_Init(void);
void CLCD_Clear(void);
void CLCD_SetCursor(uint8_t row, uint8_t col);
void CLCD_WriteChar(char c);
void CLCD_WriteString(char *str);

#endif
