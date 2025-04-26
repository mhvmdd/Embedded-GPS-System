#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "STD.h"
#include "../GPIO/GPIO.h"

//-----------------------------------------------------------------------------
// Commands and Constants for HD44780 LCD
//-----------------------------------------------------------------------------

// --- Basic Commands ---

#define LCD_CMD_CLEAR_DISPLAY 0x01
#define LCD_CMD_RETURN_HOME 0x02

// --- Entry Mode Set ---
#define LCD_CMD_ENTRY_MODE_SET 0x04
#define LCD_ENTRY_INCREMENT 0x02
#define LCD_ENTRY_DECREMENT 0x00
#define LCD_ENTRY_DISPLAY_SHIFT_ON 0x01
#define LCD_ENTRY_DISPLAY_SHIFT_OFF 0x00

// --- Display On/Off Control ---

#define LCD_CMD_DISPLAY_CONTROL 0x08
#define LCD_DISPLAY_ON 0x04
#define LCD_DISPLAY_OFF 0x00
#define LCD_CURSOR_ON 0x02
#define LCD_CURSOR_OFF 0x00
#define LCD_BLINK_ON 0x01
#define LCD_BLINK_OFF 0x00

// --- Cursor or Display Shift ---

#define LCD_CMD_CURSOR_DISPLAY_SHIFT 0x10
#define LCD_SHIFT_DISPLAY 0x08
#define LCD_SHIFT_CURSOR 0x00
#define LCD_SHIFT_RIGHT 0x04
#define LCD_SHIFT_LEFT 0x00

// --- Function Set ---

#define LCD_CMD_FUNCTION_SET 0x20
#define LCD_FUNCTION_8BIT 0x10
#define LCD_FUNCTION_4BIT 0x00
#define LCD_FUNCTION_2LINE 0x08
#define LCD_FUNCTION_1LINE 0x00
#define LCD_FUNCTION_5X10 0x04
#define LCD_FUNCTION_5X8 0x00

// --- Set DDRAM Address ---

#define LCD_CMD_SET_DDRAM_ADDR 0x80

// DDRAM Address Offsets for common displays
#define LCD_LINE_0_ADDR_OFFSET 0x00 // Start address for line 0
#define LCD_LINE_1_ADDR_OFFSET 0x40
//-----------------------------------------------------------------------------
// Functions Prototypes
//-----------------------------------------------------------------------------

/**
 * @brief Initializes the GPIO pins used for the LCD and configures the LCD
 * controller for 4-bit mode, 2 lines, 5x8 font.
 *
 * @details Must be called once before any other LCD function. Assumes the system
 * clock has already been configured. Handles the specific HD44780
 * initialization sequence and timings internally.
 */
void LCD_Init(void);

/**
 * @brief Sends a command byte to the LCD controller.
 *
 * @param cmd The command byte (use the LCD_CMD_* defines).
 * @note This is a low-level function; prefer using specific functions like
 * LCD_Clear(), LCD_SetCursor(), etc., when possible. Timing delays
 * are handled internally in the implementation.
 */
void LCD_SendCommand(uint8_t cmd);

/**
 * @brief Sends a data byte (character) to the LCD to be displayed at the
 * current cursor position.
 *
 * @param data The character byte (ASCII value) to display.
 * @note This is a low-level function; prefer using LCD_WriteChar() or
 * LCD_WriteString(). Timing delays are handled internally.
 */
void LCD_SendData(uint8_t data);

/**
 * @brief Writes a single character to the LCD at the current cursor position.
 * The cursor position then advances according to the Entry Mode setting.
 *
 * @param character The character to display.
 */
void LCD_WriteChar(char character);

/**
 * @brief Writes a null-terminated string to the LCD starting at the current
 * cursor position.
 *
 * @param str Pointer to the null-terminated string to display.
 */
void LCD_WriteString(const char *str);

/**
 * @brief Clears the entire LCD display and returns the cursor to the home
 * position (line 0, column 0).
 *
 * @note This operation takes longer than most other commands (~1.6ms).
 */
void LCD_Clear(void);

/**
 * @brief Sets the cursor position to a specific row and column.
 *
 * @param row The row number (0 for the first line, 1 for the second line on 16x02).
 * @param col The column number (0 to 15 for a 16x02 display).
 */
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif // LCD_H
