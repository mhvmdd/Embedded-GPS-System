#include "GPIO.h"
#include "UART.h" 
 



  // ********************************UART_0 --> PC *******************************//

void UART0_Init(void){
	 SET_BIT(SYSCTL_RCGCUART_R ,0);    // Enable UART0 clock
   SET_BIT(SYSCTL_RCGCGPIO_R, 0);   // Enable clock to Port A
   while(GET_BIT(SYSCTL_PRGPIO_R, 0) == 0); // Wait until Port A is ready

    CLR_BIT(UART0_CTL_R , 0x01) ;         // Disable UART0
    UART0_IBRD_R = 104;           // Integer part of 9600 baud
    UART0_FBRD_R = 11;            // Fractional part of 9600 baud
    SET(UART0_LCRH_R ,0x70 ) ;          // 8-bit, no parity, 1 stop bit, enable FIFO
    SET(UART0_CTL_R , 0x301 ) ;          // Enable UART0, TXE, RXE

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

// *************************************** UART-1 --> GPS ***********************//



void UART1_Init(void) {
    SYSCTL_RCGCUART_R |= 0x01;    // Enable UART1 clock
    SYSCTL_RCGCGPIO_R |= 0x01;    // Enable clock to Port C
    while ((SYSCTL_PRGPIO_R & 0x04) == 0) {};

    UART1_CTL_R &= ~0x01;         // Disable UART1
    UART1_IBRD_R = INT_BR ;           // Integer part (same baud as GPS: 9600)
    UART1_FBRD_R = FRACT_BR ;            // Fractional part
    UART1_LCRH_R = 0x70;          // 8-bit, no parity, 1 stop bit
    UART1_CTL_R = 0x301;          // Enable UART1, TXE, RXE

    SET_BIT(GPIO_PORTC_AFSEL_R , 0x30 ) ;   // PC4, PC5 alt func
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) | 0x00110000;
    SET_BIT(GPIO_PORTC_DEN_R,0x30 ) ;     // Digital enable
    CLR_BIT(GPIO_PORTC_AMSEL_R ,0x30);  // Disable analog
}

char UART1_ReceiveChar(void) {
    while ((UART1_FR_R & 0x10) != 0);
    return (char)(UART1_DR_R & 0xFF);
}








