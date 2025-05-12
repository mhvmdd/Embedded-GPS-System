
 /*
 * UART.h
 *
 *  Created on: April 30, 2025
 *      Author: Mohammed Mahmoud
 */

#ifndef UART_H_
#define UART_H_


//************************MACROS*********************


#define INT_BR 									104 // Integer part of 9600 baud
#define FRACT_BR 								11  // Fractional part of 9600 baud

//CLK
#define UART0_CLK_PIN 					0x00
#define UART2_CLK_PIN 					0x02
#define UART5_CLK_PIN 					0x05

// Line Control Register Config
#define LCRH_R_CFG  						0x70 // 8-bit, no parity, 1 stop bit, enable FIFO

//Control Register Config
#define CTL_R_CFG 							0x301 // Enable UART, TXE, RXE
#define CTL_R_LBMODE_EN 				0x07  //Enabling Loop back mode , only for debugging




//*************************Functions**************************


//---------------------------------------------------------
//                        UART0
//---------------------------------------------------------

void UART0_Init(void) ; 
char UART0_ReceiveChar(void) ; 
void UART0_SendChar(char c) ; 
void UART0_SendString(char *str) ; 

//---------------------------------------------------------
//                        UART2
//---------------------------------------------------------

void UART2_Init(void) ; 
char UART2_ReceiveChar(void) ;
void UART2_SendChar(char c) ; 
void UART2_SendString(char *str) ; 


//---------------------------------------------------------
//                        UART5
//---------------------------------------------------------

void UART5_Init(void) ; 
char UART5_ReceiveChar(void) ;
void UART5_SendChar(char c) ; 
void UART5_SendString(char *str) ;

#endif
