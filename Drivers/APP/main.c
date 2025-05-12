
 /*
 * main.c
 *
 *  Created on: May 10, 2025
 *      Author: Mohammed Yasser
 */

//----------LIB INCLUDES-----------
#include <stdio.h>
#include <stdbool.h>
//---------------------------------

//----------MCAL INCLUDES----------
#include "tm4c123gh6pm.h"
#include "GPIO/GPIO.h"
#include "SYSTICK/SYSTICK.h"
#include "UART/UART.h"
#include "ADC/ADC.h"
//---------------------------------

//----------HAL INCLUDES-----------
#include "LCD/LCD.h"
#include "GPS/GPS.h"
#include "SWITCH/SWITCH.h"
#include "LED/LED.h"
//---------------------------------

//----------APP INCLUDES-----------
#include "Program.h"
//---------------------------------

//----------For System Reset Function-----------
#define SCB_AIRCR   (*((volatile unsigned long *)0xE000ED0C))
#define VECTKEY     (0x5FA << 16)
#define SYSRESETREQ (1 << 2)
//---------------------------------------------

//-----------------------Program Variables--------------------------
extern char confirm;
extern char sel_main;
extern char GameStart_flag;
extern char ON;
extern char ON_flag;
//----------------------------------------------------------------------

//-----------------------Systick ISR Variables--------------------------
static uint8_t buttonState = 1;             // Previous stable read
static uint8_t debounceCounter = 0;         // Stability counter
uint8_t currentState ;


static uint8_t buttonState2 = 1;             // Previous stable read
static uint8_t debounceCounter2 = 0;         // Stability counter
uint8_t currentState2 ;

int counter =  0 ;
int count_1m = 0 ;
int count_5m = 5 ;
int randseed = 0 ;
//----------------------------------------------------------------------

//-----------------------Functions Prototypes--------------------------
void SysTick_ISR(void);
void NVIC_SystemReset(void);
//----------------------------------------------------------------------


int main (){
	Hardware_Init(SysTick_ISR);
	
	SYSTICK_DelayMs(200);
	Program_Init();
	
	HAL_LEDsCelebrationEffect();
	LCD_Clear();
	
	while (1){
	
			MainMenu();
			while (counter == 0);
		
			switch(sel_main){
				case 1:
					GoTo();
					break;
				case 2:  
					Game();
					break;
				case 3:
					NearBy();
					break;
				default: 
						LCD_Clear();
						LCD_SetCursor(0, 0);
						LCD_WriteString("Invalid Choice");
					break;
			}

	
	
	}
}
void NVIC_SystemReset(void){
    __asm("dsb");  // Data Synchronization Barrier
    SCB_AIRCR = VECTKEY | SYSRESETREQ;
    __asm("dsb");  // Ensure completion
    while (1);     // Wait for the reset to occur
}
void SysTick_ISR(void) {
    counter++;
    count_1m++;
    randseed++;

    if (counter >= 50) {  // Run every ~10ms (if SysTick is at 0.67ms)
        counter = 0;

        // ----------- Button 1 (Confirm) Handling ----------
        currentState = DIO_u8GetPinValue(PORTF, PIN4); // Active LOW
				currentState2 = DIO_u8GetPinValue(PORTF, PIN0); // Active LOW
        if (currentState != buttonState) {
            debounceCounter++;
            if (debounceCounter >= 10) {  // 50ms stable change
                buttonState = currentState;
                confirm = currentState;   // 0 = pressed
                debounceCounter = 0;
            }
        } else {
            debounceCounter = 0;
        }

        // ----------- Button 2 (ON/Reset) Handling ----------
       
        if (currentState2 != buttonState2) {
            debounceCounter2++;
            if (debounceCounter2 >= 10) {  // 50ms stable change
                buttonState2 = currentState2;
                ON = currentState2;        // 0 = pressed
                debounceCounter2 = 0;
            }
        } else {
            debounceCounter2 = 0;
        }
    }

    // ----------- Game Countdown (1 minute) -------------
    if (count_1m >= 60000) { // Assuming SysTick runs every 1ms
        count_1m = 0;

        if (GameStart_flag) {
            if (count_5m >= 0) {
                LCD_Clear();
                LCD_SetCursor(0, 0);
                LCD_WriteChar(count_5m + '0');  // Convert int to char
                LCD_WriteString(" Min Left");
                SYSTICK_DelayMs(2000);
                Game_LCDRedraw();
                count_5m--;
            }
        }
    }

    // ----------- Random Seed Wrapping -------------
    if (randseed >= 124356) {
        randseed = 0;
    }

    // ----------- Reset Handling -------------
    if (ON_flag == true && ON == 0) {  // Button pressed
				ON_flag = false;
        Program_DeInit();
				SYSTICK_DelayMs(100);
        NVIC_SystemReset();  
    }
}




