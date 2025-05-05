

#include "SYSTICK.H"
#include "../../LIB/tm4c123gh6pm.h"

static void (*SysTick_Callback)(void) = 0;

void SYSTICK_Init(void)
{
    NVIC_ST_CTRL_R = 0;            // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // Maximum reload value
    NVIC_ST_CURRENT_R = 0;         // Clear the current value register
    NVIC_ST_CTRL_R = 0x07;         // Enable SysTick with core clock and interrupt
}

void SYSTICK_DelayMs(unsigned int delay)
{
    unsigned int i;

    NVIC_ST_CTRL_R = 0;           // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 16000 - 1; // 1ms delay at 16 MHz
    NVIC_ST_CURRENT_R = 0;        // Clear current value
    NVIC_ST_CTRL_R = 0x5;         // Enable SysTick with core clock, no interrupt

    for (i = 0; i < delay; i++)
    {
        while ((NVIC_ST_CTRL_R & 0x00010000) == 0)
            ; // Wait for COUNT flag
    }

    NVIC_ST_CTRL_R = 0; // Turn off SysTick after delay
}
void SYSTICK_SetCallback(void (*callback)(void))
{
    SysTick_Callback = callback;
}

void SYSTICK_Handler(void)
{
    if (SysTick_Callback)
    {
        SysTick_Callback(); // Call the user-defined function
    }
}