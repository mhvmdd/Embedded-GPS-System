#ifndef GPIO_H_
#define	GPIO_H_

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD.h"



#define AHB	0
#define APB 1
/* choose system clock
	AHB
	APB
*/
#define clk_type	AHB

#if 	clk_type == APB
#define GPIOA_Base_Address        0x40004000            // define the boundary address of GPIO port A
#define GPIOB_Base_Address        0x40005000            // define the boundary address of GPIO port B
#define GPIOC_Base_Address        0x40006000            // define the boundary address of GPIO port C
#define GPIOD_Base_Address        0x40007000            // define the boundary address of GPIO port D
#define GPIOE_Base_Address        0x40024000            // define the boundary address of GPIO port E
#define GPIOF_Base_Address        0x40025000            // define the boundary address of GPIO port F
#elif 	clk_type == AHB
#define GPIOA_Base_Address        0x40058000            // define the boundary address of GPIO port A
#define GPIOB_Base_Address        0x40059000            // define the boundary address of GPIO port B
#define GPIOC_Base_Address        0x4005A000            // define the boundary address of GPIO port C
#define GPIOD_Base_Address        0x4005B000            // define the boundary address of GPIO port D
#define GPIOE_Base_Address        0x4005C000            // define the boundary address of GPIO port E
#define GPIOF_Base_Address        0x4005D000            // define the boundary address of GPIO port F
#endif
/*PORT A Registers*/// 8 pins  //PIN0 & PIN1 are used for UART0
#define GPIOA_DATA	    *((u32*)(GPIOA_Base_Address + 0x000))
#define GPIOA_DIR       *((u32*)(GPIOA_Base_Address + 0x400))
#define GPIOA_AFSEL	    *((u32*)(GPIOA_Base_Address + 0x420))
#define GPIOA_PUR       *((u32*)(GPIOA_Base_Address + 0x510))
#define GPIOA_PDR	    *((u32*)(GPIOA_Base_Address + 0x514))
#define GPIOA_DEN	    *((u32*)(GPIOA_Base_Address + 0x51C))
#define GPIOA_LOCK      *((u32*)(GPIOA_Base_Address + 0x520))
#define GPIOA_CR		*((u32*)(GPIOA_Base_Address + 0x524))
#define GPIOA_AMSEL		*((u32*)(GPIOA_Base_Address + 0x528))
#define GPIOA_PCTL		*((u32*)(GPIOA_Base_Address + 0x52C))

/*PORT B Registers*/// 8 pins
#define GPIOB_DATA	    *((u32*)(GPIOB_Base_Address + 0x000))
#define GPIOB_DIR       *((u32*)(GPIOB_Base_Address + 0x400))
#define GPIOB_AFSEL	    *((u32*)(GPIOB_Base_Address + 0x420))
#define GPIOB_PUR       *((u32*)(GPIOB_Base_Address + 0x510))
#define GPIOB_PDR	    *((u32*)(GPIOB_Base_Address + 0x514))
#define GPIOB_DEN	    *((u32*)(GPIOB_Base_Address + 0x51C))
#define GPIOB_LOCK      *((u32*)(GPIOB_Base_Address + 0x520))
#define GPIOB_CR		*((u32*)(GPIOB_Base_Address + 0x524))
#define GPIOB_AMSEL		*((u32*)(GPIOB_Base_Address + 0x528))
#define GPIOB_PCTL		*((u32*)(GPIOB_Base_Address + 0x52C))

/*PORT C Registers*/// 8 pins
#define GPIOC_DATA	    *((u32*)(GPIOC_Base_Address + 0x000))
#define GPIOC_DIR       *((u32*)(GPIOC_Base_Address + 0x400))
#define GPIOC_AFSEL	    *((u32*)(GPIOC_Base_Address + 0x420))
#define GPIOC_PUR       *((u32*)(GPIOC_Base_Address + 0x510))
#define GPIOC_PDR	    *((u32*)(GPIOC_Base_Address + 0x514))
#define GPIOC_DEN	    *((u32*)(GPIOC_Base_Address + 0x51C))
#define GPIOC_LOCK      *((u32*)(GPIOC_Base_Address + 0x520))
#define GPIOC_CR		*((u32*)(GPIOC_Base_Address + 0x524))
#define GPIOC_AMSEL		*((u32*)(GPIOC_Base_Address + 0x528))
#define GPIOC_PCTL		*((u32*)(GPIOC_Base_Address + 0x52C))

/*PORT D Registers*/// 8 pins
#define GPIOD_DATA	    *((u32*)(GPIOD_Base_Address + 0x000))
#define GPIOD_DIR       *((u32*)(GPIOD_Base_Address + 0x400))
#define GPIOD_AFSEL	    *((u32*)(GPIOD_Base_Address + 0x420))
#define GPIOD_PUR       *((u32*)(GPIOD_Base_Address + 0x510))
#define GPIOD_PDR	    *((u32*)(GPIOD_Base_Address + 0x514))
#define GPIOD_DEN	    *((u32*)(GPIOD_Base_Address + 0x51C))
#define GPIOD_LOCK      *((u32*)(GPIOD_Base_Address + 0x520))
#define GPIOD_CR		*((u32*)(GPIOD_Base_Address + 0x524))
#define GPIOD_AMSEL		*((u32*)(GPIOD_Base_Address + 0x528))
#define GPIOD_PCTL		*((u32*)(GPIOD_Base_Address + 0x52C))

/*PORT E Registers*/// 6 pins
#define GPIOE_DATA	    *((u32*)(GPIOE_Base_Address + 0x000))
#define GPIOE_DIR       *((u32*)(GPIOE_Base_Address + 0x400))
#define GPIOE_AFSEL	    *((u32*)(GPIOE_Base_Address + 0x420))
#define GPIOE_PUR       *((u32*)(GPIOE_Base_Address + 0x510))
#define GPIOE_PDR	    *((u32*)(GPIOE_Base_Address + 0x514))
#define GPIOE_DEN	    *((u32*)(GPIOE_Base_Address + 0x51C))
#define GPIOE_LOCK      *((u32*)(GPIOE_Base_Address + 0x520))
#define GPIOE_CR		*((u32*)(GPIOE_Base_Address + 0x524))
#define GPIOE_AMSEL		*((u32*)(GPIOE_Base_Address + 0x528))
#define GPIOE_PCTL		*((u32*)(GPIOE_Base_Address + 0x52C))

/*PORT F Registers*/// 5 pins
#define GPIOF_DATA	    *((u32*)(GPIOF_Base_Address + 0x000))
#define GPIOF_DIR       *((u32*)(GPIOF_Base_Address + 0x400))
#define GPIOF_AFSEL	    *((u32*)(GPIOF_Base_Address + 0x420))
#define GPIOF_PUR       *((u32*)(GPIOF_Base_Address + 0x510))
#define GPIOF_PDR	    *((u32*)(GPIOF_Base_Address + 0x514))
#define GPIOF_DEN	    *((u32*)(GPIOF_Base_Address + 0x51C))
#define GPIOF_LOCK      *((u32*)(GPIOF_Base_Address + 0x520))
#define GPIOF_CR		*((u32*)(GPIOF_Base_Address + 0x524))
#define GPIOF_AMSEL		*((u32*)(GPIOF_Base_Address + 0x528))
#define GPIOF_PCTL		*((u32*)(GPIOF_Base_Address + 0x52C))

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

#define OUTPUT 	1
#define INPUT	0

/*Functions*/

void DIO_voidSetPinDirection(char port,char pin, char direction);

void DIO_voidSetPinValue(char port,char pin, char value);

char DIO_u8GetPinValue(char port,char pin);

void DIO_voidSetPortDirection(char port,char direction);

void DIO_voidSetPortValue(char port,char value);

void DIO_VoidTogglePin(char port,char pin);

char DIO_u8GetPortValue(char port,char pin);




#endif
















