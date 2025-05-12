
 /*
 * LED.c
 *
 *  Created on: May 10, 2025
 *      Author: Mohammed Ashraf
 */

#include "LED.h"
#include "SYSTICK/SYSTICK.h"
#include "GPIO/GPIO.h"

void HAL_LEDsInit(void){
	DIO_voidSetPinDirection(PORTF,	PIN1,OUTPUT);	// RED
	DIO_voidSetPinDirection(PORTF, 	PIN2,OUTPUT); // BLUE  
	DIO_voidSetPinDirection(PORTF, 	PIN3,OUTPUT); // GREEN	
	
	
	DIO_voidSetPinDirection(PORTA,	PIN6,OUTPUT);	// YELLOW
	DIO_voidSetPinDirection(PORTA, 	PIN7,OUTPUT); // GREEN
	DIO_voidSetPinDirection(PORTD, 	PIN7,OUTPUT); // RED

	DIO_voidSetPinValue(PORTF,	PIN1,LOW);	// RED
	DIO_voidSetPinValue(PORTF, 	PIN2,LOW); // BLUE  
	DIO_voidSetPinValue(PORTF, 	PIN3,LOW); // GREEN	

	
	DIO_voidSetPinValue(PORTA,	PIN6,LOW);	//PIN6 -> YELLOW
	DIO_voidSetPinValue(PORTA, 	PIN7,LOW); //PIN7 -> GREEN
	DIO_voidSetPinValue(PORTD, 	PIN7,LOW); //PIN7 -> RED
	
	
	//PIN2 -> YELLOW
	//PIN3 -> GREEN
	//PIN6 -> RED
	
}

void HAL_LEDsCelebrationEffect(void){
			int i;
    // Initial states: all LEDs OFF
    DIO_voidSetPinValue(PORTA, PIN6, LOW);  // YELLOW
    DIO_voidSetPinValue(PORTA, PIN7, LOW);  // GREEN
    DIO_voidSetPinValue(PORTD, PIN7, LOW);  // RED
    
    // LED Celebration Pattern
    for (i = 0; i < 3; i++) {
        // Step 1: All LEDs ON for a short duration
        DIO_voidSetPinValue(PORTA, PIN6, HIGH);  // YELLOW ON
        DIO_voidSetPinValue(PORTA, PIN7, HIGH);  // GREEN ON
        DIO_voidSetPinValue(PORTD, PIN7, HIGH);  // RED ON
        SYSTICK_DelayMs(500);  // Wait for 500ms
        
        // Step 2: All LEDs OFF
        DIO_voidSetPinValue(PORTA, PIN6, LOW);   // YELLOW OFF
        DIO_voidSetPinValue(PORTA, PIN7, LOW);   // GREEN OFF
        DIO_voidSetPinValue(PORTD, PIN7, LOW);   // RED OFF
        SYSTICK_DelayMs(500);  // Wait for 500ms
        
        // Step 3: Random LED flashing to create an effect
        DIO_voidSetPinValue(PORTA, PIN6, HIGH);  // YELLOW ON
        SYSTICK_DelayMs(100);  // 100ms on
        DIO_voidSetPinValue(PORTA, PIN6, LOW);   // YELLOW OFF
        
        DIO_voidSetPinValue(PORTA, PIN7, HIGH);  // GREEN ON
        SYSTICK_DelayMs(100);  // 100ms on
        DIO_voidSetPinValue(PORTA, PIN7, LOW);   // GREEN OFF
        
        DIO_voidSetPinValue(PORTD, PIN7, HIGH);  // RED ON
        SYSTICK_DelayMs(100);  // 100ms on
        DIO_voidSetPinValue(PORTD, PIN7, LOW);   // RED OFF
        SYSTICK_DelayMs(300);  // Wait for a longer duration between flashes
    }
	
}