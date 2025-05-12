

/*
 * LCD.c
 *
 *  Created on: April 30, 2025
 *      Author: Amr Khaled
 */

#include "LCD.H"

//-----------------------------------------------------------------------------
// Ports & Pins Configuration
//-----------------------------------------------------------------------------

// Contorl Pins & Port
#define LCD_CTRL_PORT PORTB // May be changed to any port
#define LCD_RS_PIN PIN0
// I am assuming that RW will be connected to GND (write mode only) //
#define LCD_E_PIN PIN1

#define LCD_DATA_PORT_1 PORTA // May be changed to any port
#define LCD_D0_PIN PIN2
#define LCD_D1_PIN PIN3
#define LCD_D2_PIN PIN4
#define LCD_D3_PIN PIN5
// Data Pins & Port
#define LCD_DATA_PORT_2 PORTD // May be changed to any port
#define LCD_D4_PIN PIN0
#define LCD_D5_PIN PIN1
#define LCD_D6_PIN PIN2
#define LCD_D7_PIN PIN3

//-----------------------------------------------------------------------------
// Private Helper Functions
//-----------------------------------------------------------------------------

/**
 * @brief Sends a pulse to the Enable pin of the LCD.
 *
 * @details This function sets the Enable pin high, waits for a short time,
 * and then sets it low again. This is used to signal the LCD to read the data
 * on the data pins.
 */
static void LCD_Pulse_Enable(void)
{

    SYSTICK_DelayMs(1);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, HIGH); // Set E high, wait, then set E low
    SYSTICK_DelayMs(1);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, LOW); // Delay for pulse width (e.g., 1ms)
    SYSTICK_DelayMs(1);
}

/**
 * @brief Sends a 4-bit nibble(half a byte) to the LCD controller.
 *
 * @param nibble The 4-bit nibble to send (D4-D7).
 */
/*
static void LCD_SendNibble(uint8_t nibble)
{
    // Set data pins to the desired nibble
    DIO_voidSetPinValue(LCD_DATA_PORT, LCD_D4_PIN, (nibble >> 0) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT, LCD_D5_PIN, (nibble >> 1) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT, LCD_D6_PIN, (nibble >> 2) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT, LCD_D7_PIN, (nibble >> 3) & 0x01);

    // Pulse the Enable pin to send the nibble
    LCD_Pulse_Enable();
}*/

/**
 * @brief sends a whole byte to the LCD controller (4-bit mode).
 */
static void LCD_SendByte(uint8_t byte, uint8_t isData)
{
    // Set RS pin for command or data
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, isData ? HIGH : LOW);
    SYSTICK_DelayMs(1); // Delay for RS setup time
                        // Send the high nibble first
    DIO_voidSetPinValue(LCD_DATA_PORT_1, LCD_D0_PIN, (byte >> 0) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT_1, LCD_D1_PIN, (byte >> 1) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT_1, LCD_D2_PIN, (byte >> 2) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT_1, LCD_D3_PIN, (byte >> 3) & 0x01);

    DIO_voidSetPinValue(LCD_DATA_PORT_2, LCD_D4_PIN, (byte >> 4) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT_2, LCD_D5_PIN, (byte >> 5) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT_2, LCD_D6_PIN, (byte >> 6) & 0x01);
    DIO_voidSetPinValue(LCD_DATA_PORT_2, LCD_D7_PIN, (byte >> 7) & 0x01);
    SYSTICK_DelayMs(1); // Delay for command execution time
    LCD_Pulse_Enable();
    SYSTICK_DelayMs(1);
}

/**
 * @brief Forces the LCD into 4-bit mode.
 *
 * @details It forces the LCD into 4-bit mode by sending a specific sequence
 * of commands using only 4 bits `D4-D7` [0x03, 0x03, 0x03, 0x02(this is the explicit command for 4 bit mode)].
 *
 * @note This function is called during initialization to ensure the LCD.
 */

/*
static void LCD_ForceInto4BitMode()
{
    // --- Special function set sequence to enter 4 bit mode ---
    LCD_SendNibble(0x03);
    SYSTICK_DelayMs(5);
    LCD_SendNibble(0x03);
    SYSTICK_DelayMs(1);
    LCD_SendNibble(0x03);
    SYSTICK_DelayMs(1);
    LCD_SendNibble(0x02); // Set to 4-bit mode entry point
    SYSTICK_DelayMs(1);
     }
*/
//-----------------------------------------------------------------------------
// API Functions
//-----------------------------------------------------------------------------

void LCD_Init(void)
{
    // 1. Enable the clock for the GPIO peripherals used
    DIO_voidInitPort(LCD_CTRL_PORT);
    DIO_voidInitPort(LCD_DATA_PORT_1); // Initialize control port
    DIO_voidInitPort(LCD_DATA_PORT_2); // Initialize data port

    // 2. Configure the GPIO pins used for LCD control (RS, E) as outputs
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_E_PIN, OUTPUT);

    // 3. Configure the GPIO pins used for LCD data (D4-D7) as outputs
    DIO_voidSetPinDirection(LCD_DATA_PORT_1, LCD_D0_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT_1, LCD_D1_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT_1, LCD_D2_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT_1, LCD_D3_PIN, OUTPUT);

    // 3. Configure the GPIO pins used for LCD data (D4-D7) as outputs
    DIO_voidSetPinDirection(LCD_DATA_PORT_2, LCD_D4_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT_2, LCD_D5_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT_2, LCD_D6_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT_2, LCD_D7_PIN, OUTPUT);

    // 4. Start LCD Initialization Sequence (HD44780 4-bit mode)

    SYSTICK_DelayMs(50);

    // Set RS and E low initially
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, LOW);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, LOW);

    // LCD_ForceInto4BitMode();

    // --- Configure LCD parameters ---
    LCD_SendCommand(0x38);                                                                       // 0x38
    LCD_SendCommand(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_OFF | LCD_CURSOR_OFF | LCD_BLINK_OFF); // 0x08
    LCD_Clear();                                                                                 // 0x01
    LCD_SendCommand(LCD_CMD_ENTRY_MODE_SET | LCD_ENTRY_INCREMENT | LCD_ENTRY_DISPLAY_SHIFT_OFF); // 0x06
    LCD_SendCommand(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF);  // 0x0C - Display ON
}

void LCD_SendCommand(uint8_t cmd)
{
    LCD_SendByte(cmd, false);

    if (cmd == LCD_CMD_CLEAR_DISPLAY || cmd == LCD_CMD_RETURN_HOME)
    {
        SYSTICK_DelayMs(2);
    }
}

void LCD_SendData(uint8_t data)
{
    LCD_SendByte(data, true);
}

void LCD_WriteChar(char c)
{
    LCD_SendData((uint8_t)c);
}

void LCD_WriteString(const char *str)
{
    while (*str != '\0')
    {
        LCD_WriteChar(*str);
        str++;
    }
}

void LCD_Clear(void)
{
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    // Note: The delay for clear command is handled in LCD_SendCommand function
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addressToWrite = 0x00;

    if (col > 15)
    {
        col = 0;
    }

    if (row == 0)
    {
        addressToWrite = LCD_LINE_0_ADDR_OFFSET + col;
    }
    else if (row == 1)
    {
        addressToWrite = LCD_LINE_1_ADDR_OFFSET + col;
    }
    else
    {
        addressToWrite = LCD_LINE_0_ADDR_OFFSET + col;
    }

    // Set the DDRAM address to the calculated value
    LCD_SendCommand(LCD_CMD_SET_DDRAM_ADDR | addressToWrite);
}