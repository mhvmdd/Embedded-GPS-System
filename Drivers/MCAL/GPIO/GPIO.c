
 /*
 * GPIO.c
 *
 *  Created on: April 30, 2025
 *      Author: Mohammed Ashraf
 */

#include "GPIO.h" 



void DIO_voidInitPort(unsigned char port){

	SET_BIT(SYSCTL_RCGCGPIO_R, port);
	while(GET_BIT(SYSCTL_PRGPIO_R, port) == 0);

	switch (port)
    {
        case PORTA:
						GPIO_PORTA_AMSEL &=~0xFF;
						GPIO_PORTA_AFSEL &=~0xFF;
						GPIO_PORTA_PCTL &=~0xFFFFFFFF;
				    GPIO_PORTA_LOCK = GPIO_LOCK_KEY;
		    		GPIO_PORTA_CR   |= 0xFF;
						GPIO_PORTA_DEN |= 0xFF;
            break;
        case PORTB:
						GPIO_PORTB_AMSEL &=~0xFF;
						GPIO_PORTB_AFSEL &=~0xFF;
						GPIO_PORTB_PCTL &=~0xFFFFFFFF;
				    GPIO_PORTB_LOCK = GPIO_LOCK_KEY;
			    	GPIO_PORTB_CR   |= 0xFF;
						GPIO_PORTB_DEN   |= 0xFF;
            break;
        case PORTC:
						GPIO_PORTC_LOCK = GPIO_LOCK_KEY;
				    GPIO_PORTC_CR   |= 0xFF;
						GPIO_PORTC_AMSEL &=~0xFF;
						GPIO_PORTC_AFSEL &=~0xFF;
						GPIO_PORTC_PCTL &=~0xFFFFFFFF;
						GPIO_PORTC_DEN |= 0xFF;
            break;
        case PORTD:
						GPIO_PORTD_AMSEL &=~0xFF;
						GPIO_PORTD_AFSEL &=~0xFF;
						GPIO_PORTD_PCTL &=~0xFFFFFFFF;
				    GPIO_PORTD_LOCK = GPIO_LOCK_KEY;
				    GPIO_PORTD_CR   |= 0xFF;
						GPIO_PORTD_DEN |= 0xFF;
            break;
        case PORTE:
						GPIO_PORTE_AMSEL &=~0xFF;
						GPIO_PORTE_AFSEL &=~0xFF;
						GPIO_PORTE_PCTL &=~0xFFFFFFFF;
				    GPIO_PORTE_LOCK = GPIO_LOCK_KEY;
			     	GPIO_PORTE_CR   |= 0x3F;
						GPIO_PORTE_DEN |=  0xFF;
            break;
        case PORTF:
						GPIO_PORTF_AMSEL   &=~0xFF;
						GPIO_PORTF_AFSEL  &=~0xFF;
						GPIO_PORTF_PCTL  &=~0xFFFFFFFF;
						GPIO_PORTF_LOCK = GPIO_LOCK_KEY;      // Unlock GPIOCR register
						GPIO_PORTF_CR   |=0x1F;            // Allow changes to PF4-0
						GPIO_PORTF_DEN    |=0x1F;
						GPIO_PORTF_PUR    |=0x11;
            break;
        default:
            return; //  case invalid port
    }
}


void DIO_voidSetPinDirection(unsigned char port,unsigned char pin, unsigned char direction){
	switch (port) 
	{
				case PORTA:
						if(direction == OUTPUT)
								SET_BIT(GPIO_PORTA_DIR, pin);
						else
								CLR_BIT(GPIO_PORTA_DIR, pin);
						break;
				case PORTB:
						if(direction == OUTPUT)
								SET_BIT(GPIO_PORTB_DIR, pin);
						else
								CLR_BIT(GPIO_PORTB_DIR, pin);
						break;
				case PORTC:
						if(direction == OUTPUT)
								SET_BIT(GPIO_PORTC_DIR, pin);
						else
								CLR_BIT(GPIO_PORTC_DIR, pin);
						break;
				case PORTD:
						if(direction == OUTPUT)
								SET_BIT(GPIO_PORTD_DIR, pin);
						else
								CLR_BIT(GPIO_PORTD_DIR, pin);
						break;
				case PORTE:
						if(direction == OUTPUT)
								SET_BIT(GPIO_PORTE_DIR, pin);
						else
								CLR_BIT(GPIO_PORTE_DIR, pin);
						break;
				case PORTF:
						if(direction == OUTPUT)
								SET_BIT(GPIO_PORTF_DIR, pin);
						else
								CLR_BIT(GPIO_PORTF_DIR, pin);
						break;

  }
		
}
  // for leds
void DIO_voidSetPinValue(unsigned char port,unsigned char pin, unsigned char value){
	switch (port) {
        case PORTA:
            if(value == HIGH)
                SET_BIT(GPIO_PORTA_DATA, pin);
            else
                CLR_BIT(GPIO_PORTA_DATA, pin);
            break;
        case PORTB:
            if(value == HIGH)
                SET_BIT(GPIO_PORTB_DATA, pin);
            else
                CLR_BIT(GPIO_PORTB_DATA, pin);
            break;
				case PORTC:
            if(value == HIGH)
                SET_BIT(GPIO_PORTC_DATA, pin);
            else
                CLR_BIT(GPIO_PORTC_DATA, pin);
            break;
				case PORTD:
            if(value == HIGH)
                SET_BIT(GPIO_PORTD_DATA, pin);
            else
                CLR_BIT(GPIO_PORTD_DATA, pin);
            break;
				case PORTE:
            if(value == HIGH)
                SET_BIT(GPIO_PORTE_DATA, pin);
            else
                CLR_BIT(GPIO_PORTE_DATA, pin);
            break;
				case PORTF:
            if(value == HIGH)
                SET_BIT(GPIO_PORTF_DATA, pin); //led on
            else
                CLR_BIT(GPIO_PORTF_DATA, pin); // led off
            break;
        
    }
}
// sw

 char DIO_u8GetPinValue(unsigned char port,unsigned char pin){
	char value = 0;
    switch (port){
        case PORTA:
            value = GET_BIT(GPIO_PORTA_DATA, pin);
            break;
        case PORTB:
            value = GET_BIT(GPIO_PORTB_DATA, pin);
            break;
				case PORTC:
            value = GET_BIT(GPIO_PORTC_DATA, pin);
            break;
				case PORTD:
            value = GET_BIT(GPIO_PORTD_DATA, pin);
            break;
				case PORTE:
            value = GET_BIT(GPIO_PORTE_DATA, pin);
            break;
				case PORTF:
            value = GET_BIT(GPIO_PORTF_DATA, pin);  // get sw value 
            break;
        
    }
    return value;
}
 
void DIO_voidTogglePinValue(unsigned char port,unsigned char pin){

			  switch (port){
        case PORTA:
            TOG_BIT(GPIO_PORTA_DATA, pin);
            break;
        case PORTB:
            TOG_BIT(GPIO_PORTB_DATA, pin);
            break;
				case PORTC:
            TOG_BIT(GPIO_PORTC_DATA, pin);
            break;
				case PORTD:
            TOG_BIT(GPIO_PORTD_DATA, pin);
            break;
				case PORTE:
            TOG_BIT(GPIO_PORTE_DATA, pin);
            break;
				case PORTF:
            TOG_BIT(GPIO_PORTF_DATA, pin); 
            break;
        
    }

}

void DIO_voidSetPortDirection(unsigned char port,unsigned char direction){
	switch (port) {
	
				case PORTA:
								GPIO_PORTA_DIR |= direction;	
						break;
				case PORTB:
								GPIO_PORTB_DIR |= direction;
						break;
				case PORTC:
								GPIO_PORTC_DIR |= direction;
						break;
				case PORTD:
								GPIO_PORTD_DIR |= direction;
						break;
				case PORTE:
								GPIO_PORTE_DIR |= direction;
						break;
				case PORTF:
								GPIO_PORTF_DIR |= direction;
						break;
			}
}

void DIO_voidSetPortValue(unsigned char port,unsigned char value){ 
	
	switch (port) {
	case PORTA:
								GPIO_PORTA_DATA |= value;	
						break;
	case PORTB:
								GPIO_PORTB_DATA |= value;
						break;
	case PORTC:
								GPIO_PORTC_DATA|= value;
						break;
	case PORTD:
								GPIO_PORTD_DATA |= value;
						break;
	case PORTE:
								GPIO_PORTE_DATA |= value;
						break;
	case PORTF:
								GPIO_PORTF_DATA |= value;
						break;
}
	
}




