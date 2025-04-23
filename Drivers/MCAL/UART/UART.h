#ifndef UART_H_
#define UART_H_


#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/STD.h" 

#include "../TM4C123.h"

#define INT_BR 104 
#define FRACT_BR 11 



void UART0_Init(void) ; 
char UART0_ReceiveChar(void) ; 
void UART0_SendChar(char c) ; 
void UART0_SendString(char *str) ; 
void UART1_Init(void) ; 
char UART1_ReceiveChar(void) ;


#endif
