#include "clcd.h"
#include "main.h"
#include "stm32f1xx_hal.h"

// Low-level functions
static void CLCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_PORT, DATA_PINS, cmd & 0xF0);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LCD_PORT, DATA_PINS, (cmd << 4) & 0xF0);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);

    HAL_Delay(2);
}

// Public functions
void CLCD_Init(void) {
    HAL_GPIO_WritePin(LCD_PORT, DATA_PINS, GPIO_PIN_RESET);
    HAL_Delay(20);

    CLCD_SendCommand(0x02);  // Initialize in 4-bit mode
    CLCD_SendCommand(0x28);  // 2 lines, 5x8 matrix
    CLCD_SendCommand(0x0C);  // Display ON, Cursor OFF
    CLCD_SendCommand(0x06);  // Increment cursor
    CLCD_Clear();
}

void CLCD_Clear(void) {
    CLCD_SendCommand(0x01);
    HAL_Delay(2);
}

void CLCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t cmd = (row == 0 ? 0x80 : 0xC0) + col;
    CLCD_SendCommand(cmd);
}

void CLCD_WriteChar(char c) {
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_PORT, DATA_PINS, c & 0xF0);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LCD_PORT, DATA_PINS, (c << 4) & 0xF0);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);

    HAL_Delay(2);
}

void CLCD_WriteString(char *str) {
    while (*str) {
        CLCD_WriteChar(*str++);
    }
}
