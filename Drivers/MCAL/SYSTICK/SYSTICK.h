
 /*
 * SYSTICK.h
 *
 *  Created on: May 10, 2025
 *      Author: Doha Mohammed
 */
 
#ifndef SYSTICK_H
#define SYSTICK_H


void SysTick_Init(void);
void SYSTICK_DelayMs(unsigned int delay);
void SysTick_SetCallback(void (*callback)(void));
void SysTick_Handler(void);


#endif /*SYSTICK_H*/