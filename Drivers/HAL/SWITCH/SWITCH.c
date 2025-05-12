
 /*
 * SWITCH.c
 *
 *  Created on: May 10, 2025
 *      Author: Mohammed Yasser
 */

#include "SWITCH.h"
#include "tm4c123gh6pm.h"
#include "GPIO/GPIO.h"

void HAL_SWsInit(){
	
	DIO_voidSetPinDirection(PORTF, PIN0, INPUT); // PF0
	DIO_voidSetPinDirection(PORTF, PIN4, INPUT); // PF4

	DIO_voidSetPinValue(PORTF, PIN0, HIGH); // Enable internal pull-up
	DIO_voidSetPinValue(PORTF, PIN4, HIGH); // Enable internal pull-up
		
}
    
