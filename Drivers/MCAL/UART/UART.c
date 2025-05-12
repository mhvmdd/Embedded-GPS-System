
 /*
 * UART.c
 *
 *  Created on: April 30, 2025
 *      Author: Mohammed Mahmoud
 */

#include "BIT_MATH.h" 
#include "tm4c123gh6pm.h"	
#include "GPIO/GPIO.h"
#include "UART.h" 



//---------------------------------------------------------
//                        UART0
//---------------------------------------------------------

void UART0_Init(void){
	 SET_BIT(SYSCTL_RCGCUART_R , UART0_CLK_PIN);    // Enable UART0 clock
   SET_BIT(SYSCTL_RCGCGPIO_R, 0);   // Enable clock to Port A
   while(GET_BIT(SYSCTL_PRGPIO_R, 0) == 0); // Wait until Port A is ready

    CLR_BIT(UART0_CTL_R , 0x01);         // Disable UART0
    UART0_IBRD_R = INT_BR;           // Integer part of 9600 baud
    UART0_FBRD_R = FRACT_BR;            // Fractional part of 9600 baud
    SET(UART0_LCRH_R , LCRH_R_CFG ) ;          
    SET(UART0_CTL_R , CTL_R_CFG ) ;          

    SET(GPIO_PORTA_AFSEL_R , 0x03 ) ;   // Enable alternate functions on PA0 and PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011; // UART
    SET (GPIO_PORTA_DEN_R , 0x03) ;     // Digital enable PA0 and PA1
    CLR (GPIO_PORTA_AMSEL_R ,0x03);  // Disable analog on PA0 and PA1

}	

void UART0_SendChar(char c){
    while ((UART0_FR_R & 0x20) != 0); // Wait if TX is full
    UART0_DR_R = c;
		
}

char UART0_ReceiveChar(void) {
    while ((UART0_FR_R & 0x10) != 0);  // Wait if RX is empty
    return (char)(UART0_DR_R & 0xFF);
}

void UART0_SendString(char *str) {
    while (*str) {
        UART0_SendChar(*str++);
			
    }
}

//---------------------------------------------------------
//                        UART2
//---------------------------------------------------------

void UART2_Init(void) {
    SET_BIT(SYSCTL_RCGCUART_R,UART2_CLK_PIN );
		while (GET_BIT(SYSCTL_PRUART_R, 2) == 0);	// UART2 clock enable
    SET_BIT(SYSCTL_RCGCGPIO_R, 3);    // GPIO Port D clock enable
    while (GET_BIT(SYSCTL_PRGPIO_R, 3) == 0) {};  // Wait for Port D ready

    CLR_BIT(UART2_CTL_R, 0);          // Disable UART2
			
    UART2_IBRD_R = INT_BR;
    UART2_FBRD_R = FRACT_BR;
    UART2_LCRH_R = LCRH_R_CFG;
    SET(UART2_CTL_R, CTL_R_CFG);      // Enable UART



    SET_BIT(GPIO_PORTD_AFSEL_R, 6);   // PD6 alt func
    SET_BIT(GPIO_PORTD_AFSEL_R, 7);   // PD7 alt func

    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) | 0x11000000;  // PD6 RX, PD7 TX

    SET_BIT(GPIO_PORTD_DEN_R, 6);     // PD6 digital enable
    SET_BIT(GPIO_PORTD_DEN_R, 7);     // PD7 digital enable

    CLR_BIT(GPIO_PORTD_AMSEL_R, 6);   // PD6 disable analog
    CLR_BIT(GPIO_PORTD_AMSEL_R, 7);   // PD7 disable analog
}



char UART2_ReceiveChar(void) {
    while ((UART2_FR_R & 0x10) != 0);  // Wait until RX not empty
    return (char)(UART2_DR_R & 0xFF);
}

void UART2_SendChar(char c) {
    while ((UART2_FR_R & 0x20) != 0);  // Wait until TX not full
    UART2_DR_R = c;
}


void UART2_SendString(char *str) {
    while (*str) {
        UART2_SendChar(*str++);
    }
}



//---------------------------------------------------------
//                        UART5
//---------------------------------------------------------

void UART5_Init(void) {
    SET_BIT(SYSCTL_RCGCUART_R, UART5_CLK_PIN );   // Enable UART5 clock
    SET_BIT(SYSCTL_RCGCGPIO_R, 4);   // Enable clock to Port E
    while (GET_BIT(SYSCTL_PRGPIO_R, 4) == 0); // Wait until Port E is ready

    CLR_BIT(UART5_CTL_R, 0);          // Disable UART5 during configuration

    UART5_IBRD_R = INT_BR ;               // Integer part for 9600 baud rate
    UART5_FBRD_R = FRACT_BR;                // Fractional part for 9600 baud rate
    UART5_LCRH_R = 0x70;              // 8-bit word length, enable FIFO, 1 stop bit, no parity

    UART5_CTL_R = 0x301;              // Enable UART5, TXE and RXE

    // ------ Configure PE4 (RX) and PE5 (TX) for UART5 ------
    SET_BIT(GPIO_PORTE_AFSEL_R, (4)); // Enable alternate function on PE4
    SET_BIT(GPIO_PORTE_AFSEL_R, (5)); // Enable alternate function on PE5

    GPIO_PORTE_PCTL_R &= ~((0xF << (4 * 4)) | (0xF << (5 * 4)));  // Clear PCTL for PE4, PE5
    GPIO_PORTE_PCTL_R |=  ((1 << (4 * 4)) | (1 << (5 * 4)));      // Configure PE4 and PE5 for UART

    SET_BIT(GPIO_PORTE_DEN_R, (4));    // Enable digital function on PE4
    SET_BIT(GPIO_PORTE_DEN_R, (5));    // Enable digital function on PE5

    CLR_BIT(GPIO_PORTE_AMSEL_R, (4));  // Disable analog on PE4
    CLR_BIT(GPIO_PORTE_AMSEL_R, (5));  // Disable analog on PE5
}
void UART5_SendChar(char c) {
    while ((UART5_FR_R & 0x20) != 0); // Wait if TX is full
    UART5_DR_R = c;
}

char UART5_ReceiveChar(void) {
    while ((UART5_FR_R & 0x10) != 0); // Wait if RX is empty
    return (char)(UART5_DR_R & 0xFF);
}

void UART5_SendString(char *str) {
    while (*str) {
        UART5_SendChar(*str++);
    }
}



