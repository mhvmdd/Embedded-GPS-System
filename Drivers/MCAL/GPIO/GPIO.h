#ifndef GPIO_H_
#define	GPIO_H_

#include "BIT_MATH.h" 

#include "STD.h" 


#define NULL	0
/******************/
#define AHB		0
#define APB		1

#define SYSCTL_RCGCGPIO_R   *((volatile u32*)0x400FE608)//340
#define SYSCTL_PRGPIO_R   	*((volatile u32*)0x400FEA08)//406

/* choose system clock
	AHB
	APB
*/
#define clk_type	APB		

#if 	clk_type == APB
#define GPIO_PORTA_Base_Address        0x40004000            // define the boundary address of GPIO port A
#define GPIO_PORTB_Base_Address        0x40005000            // define the boundary address of GPIO port B
#define GPIO_PORTC_Base_Address        0x40006000            // define the boundary address of GPIO port C
#define GPIO_PORTD_Base_Address        0x40007000            // define the boundary address of GPIO port D
#define GPIO_PORTE_Base_Address        0x40024000            // define the boundary address of GPIO port E
#define GPIO_PORTF_Base_Address        0x40025000            // define the boundary address of GPIO port F

#elif clk_type == AHB
#define GPIO_PORTA_Base_Address        0x40058000            // define the boundary address of GPIO port A
#define GPIO_PORTB_Base_Address        0x40059000            // define the boundary address of GPIO port B
#define GPIO_PORTC_Base_Address        0x4005A000            // define the boundary address of GPIO port C
#define GPIO_PORTD_Base_Address        0x4005B000            // define the boundary address of GPIO port D
#define GPIO_PORTE_Base_Address        0x4005C000            // define the boundary address of GPIO port E
#define GPIO_PORTF_Base_Address        0x4005D000            // define the boundary address of GPIO port F

#endif
/*PORT A Registers*/// 8 pins  //PIN0 & PIN1 are used for UART0
#define GPIO_PORTA_DATA	       *((volatile u32*)(GPIO_PORTA_Base_Address + 0x3FC))
#define GPIO_PORTA_DIR         *((volatile u32*)(GPIO_PORTA_Base_Address + 0x400))
#define GPIO_PORTA_AFSEL	     *((volatile u32*)(GPIO_PORTA_Base_Address + 0x420))
#define GPIO_PORTA_PUR         *((volatile u32*)(GPIO_PORTA_Base_Address + 0x510))
#define GPIO_PORTA_PDR	       *((volatile u32*)(GPIO_PORTA_Base_Address + 0x514))
#define GPIO_PORTA_DEN	       *((volatile u32*)(GPIO_PORTA_Base_Address + 0x51C))
#define GPIO_PORTA_LOCK        *((volatile u32*)(GPIO_PORTA_Base_Address + 0x520))
#define GPIO_PORTA_CR					 *((volatile u32*)(GPIO_PORTA_Base_Address + 0x524))
#define GPIO_PORTA_AMSEL			 *((volatile u32*)(GPIO_PORTA_Base_Address + 0x528))
#define GPIO_PORTA_PCTL				 *((volatile u32*)(GPIO_PORTA_Base_Address + 0x52C))

/*PORT B Registers*/// 8 pins 
#define GPIO_PORTB_DATA	       *((volatile u32*)(GPIO_PORTB_Base_Address + 0x3FC))
#define GPIO_PORTB_DIR         *((volatile u32*)(GPIO_PORTB_Base_Address + 0x400))
#define GPIO_PORTB_AFSEL	     *((volatile u32*)(GPIO_PORTB_Base_Address + 0x420))
#define GPIO_PORTB_PUR         *((volatile u32*)(GPIO_PORTB_Base_Address + 0x510))
#define GPIO_PORTB_PDR	       *((volatile u32*)(GPIO_PORTB_Base_Address + 0x514))
#define GPIO_PORTB_DEN	       *((volatile u32*)(GPIO_PORTB_Base_Address + 0x51C))
#define GPIO_PORTB_LOCK        *((volatile u32*)(GPIO_PORTB_Base_Address + 0x520))
#define GPIO_PORTB_CR				   *((volatile u32*)(GPIO_PORTB_Base_Address + 0x524))
#define GPIO_PORTB_AMSEL			 *((volatile u32*)(GPIO_PORTB_Base_Address + 0x528))
#define GPIO_PORTB_PCTL			   *((volatile u32*)(GPIO_PORTB_Base_Address + 0x52C))

/*PORT C Registers*/// 8 pins 
#define GPIO_PORTC_DATA	        *((volatile u32*)(GPIO_PORTC_Base_Address + 0x3FC))
#define GPIO_PORTC_DIR          *((volatile u32*)(GPIO_PORTC_Base_Address + 0x400))
#define GPIO_PORTC_AFSEL	      *((volatile u32*)(GPIO_PORTC_Base_Address + 0x420))
#define GPIO_PORTC_PUR          *((volatile u32*)(GPIO_PORTC_Base_Address + 0x510))
#define GPIO_PORTC_PDR	        *((volatile u32*)(GPIO_PORTC_Base_Address + 0x514))
#define GPIO_PORTC_DEN	        *((volatile u32*)(GPIO_PORTC_Base_Address + 0x51C))
#define GPIO_PORTC_LOCK         *((volatile u32*)(GPIO_PORTC_Base_Address + 0x520))
#define GPIO_PORTC_CR					  *((volatile u32*)(GPIO_PORTC_Base_Address + 0x524))
#define GPIO_PORTC_AMSEL				*((volatile u32*)(GPIO_PORTC_Base_Address + 0x528))
#define GPIO_PORTC_PCTL				  *((volatile u32*)(GPIO_PORTC_Base_Address + 0x52C))

/*PORT D Registers*/// 8 pins 
#define GPIO_PORTD_DATA	        *((volatile u32*)(GPIO_PORTD_Base_Address + 0x3FC))
#define GPIO_PORTD_DIR          *((volatile u32*)(GPIO_PORTD_Base_Address + 0x400))
#define GPIO_PORTD_AFSEL	      *((volatile u32*)(GPIO_PORTD_Base_Address + 0x420))
#define GPIO_PORTD_PUR          *((volatile u32*)(GPIO_PORTD_Base_Address + 0x510))
#define GPIO_PORTD_PDR	        *((volatile u32*)(GPIO_PORTD_Base_Address + 0x514))
#define GPIO_PORTD_DEN	        *((volatile u32*)(GPIO_PORTD_Base_Address + 0x51C))
#define GPIO_PORTD_LOCK         *((volatile u32*)(GPIO_PORTD_Base_Address + 0x520))
#define GPIO_PORTD_CR					  *((volatile u32*)(GPIO_PORTD_Base_Address + 0x524))
#define GPIO_PORTD_AMSEL				*((volatile u32*)(GPIO_PORTD_Base_Address + 0x528))
#define GPIO_PORTD_PCTL				  *((volatile u32*)(GPIO_PORTD_Base_Address + 0x52C))

/*PORT E Registers*/// 6 pins 
#define GPIO_PORTE_DATA	        *((volatile u32*)(GPIO_PORTE_Base_Address + 0x3FC))
#define GPIO_PORTE_DIR          *((volatile u32*)(GPIO_PORTE_Base_Address + 0x400))
#define GPIO_PORTE_AFSEL	      *((volatile u32*)(GPIO_PORTE_Base_Address + 0x420))
#define GPIO_PORTE_PUR          *((volatile u32*)(GPIO_PORTE_Base_Address + 0x510))
#define GPIO_PORTE_PDR	        *((volatile u32*)(GPIO_PORTE_Base_Address + 0x514))
#define GPIO_PORTE_DEN	        *((volatile u32*)(GPIO_PORTE_Base_Address + 0x51C))
#define GPIO_PORTE_LOCK         *((volatile u32*)(GPIO_PORTE_Base_Address + 0x520))
#define GPIO_PORTE_CR					  *((volatile u32*)(GPIO_PORTE_Base_Address + 0x524))
#define GPIO_PORTE_AMSEL			  *((volatile u32*)(GPIO_PORTE_Base_Address + 0x528))
#define GPIO_PORTE_PCTL				  *((volatile u32*)(GPIO_PORTE_Base_Address + 0x52C))

/*PORT F Registers*/// 5 pins 
#define GPIO_PORTF_DATA	        *((volatile u32*)(GPIO_PORTF_Base_Address + 0x3FC))
#define GPIO_PORTF_DIR          *((volatile u32*)(GPIO_PORTF_Base_Address + 0x400))
#define GPIO_PORTF_AFSEL	      *((volatile u32*)(GPIO_PORTF_Base_Address + 0x420))
#define GPIO_PORTF_PUR          *((volatile u32*)(GPIO_PORTF_Base_Address + 0x510))
#define GPIO_PORTF_PDR	        *((volatile u32*)(GPIO_PORTF_Base_Address + 0x514))
#define GPIO_PORTF_DEN	        *((volatile u32*)(GPIO_PORTF_Base_Address + 0x51C))
#define GPIO_PORTF_LOCK         *((volatile u32*)(GPIO_PORTF_Base_Address + 0x520))
#define GPIO_PORTF_CR					  *((volatile u32*)(GPIO_PORTF_Base_Address + 0x524))
#define GPIO_PORTF_AMSEL				*((volatile u32*)(GPIO_PORTF_Base_Address + 0x528))
#define GPIO_PORTF_PCTL				  *((volatile u32*)(GPIO_PORTF_Base_Address + 0x52C))

/*Define Ports*/
#define PORTA	0
#define PORTB	1
#define PORTC	2
#define PORTD	3
#define PORTE	4
#define PORTF	5

/*Define Pins*/
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

#define HIGH	1
#define LOW		0
//for digital

#define OUTPUT 1
#define INPUT	 0

// GPIO LOCK KEY
#define GPIO_LOCK_KEY 0x4C4F434B

/*Functions*/

void DIO_voidInitPort(unsigned char port);

void DIO_voidSetPinDirection(unsigned char port,unsigned char pin, unsigned char direction);

void DIO_voidSetPinValue(unsigned char port,unsigned char pin, unsigned char value);

char DIO_u8GetPinValue(unsigned char port,unsigned char pin);

void DIO_voidSetPortDirection(unsigned char port,unsigned char direction);

void DIO_voidSetPortValue(unsigned char port,unsigned char value);


#endif
















