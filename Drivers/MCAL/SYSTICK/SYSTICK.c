
 /*
 * SYSTICK.c
 *
 *  Created on: May 10, 2025
 *      Author: Doha Mohammed
 */

#include "SYSTICK.H"
#include "tm4c123gh6pm.h"

void (*SysTick_Callback)(void) = 0;

void SysTick_Init(void) {
    NVIC_ST_CTRL_R = 0;                  // Disable SysTick
    NVIC_ST_RELOAD_R = 16000 - 1;        // 1ms at 16 MHz
    NVIC_ST_CURRENT_R = 0;               // Clear current value
    NVIC_ST_CTRL_R = 0x07;               // Enable SysTick | Core Clock | Interrupt
}

void SYSTICK_DelayMs(unsigned int delay) {
		unsigned int i;
		
    for(i = 0; i < delay; i++) {
        while((NVIC_ST_CTRL_R & 0x00010000) == 0); // Wait for COUNT flag
    }

   // NVIC_ST_CTRL_R = 0; // Turn off SysTick after delay
}
void SysTick_SetCallback(void (*callback)(void)) {
    SysTick_Callback = callback;
}

void SysTick_Handler(void) {
    if (SysTick_Callback) {
        SysTick_Callback();  // Call the user-defined function
    }
}