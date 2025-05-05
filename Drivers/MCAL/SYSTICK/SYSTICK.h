#ifndef SYSTICK_H
#define SYSTICK_H


void SYSTICK_Init(void);
void SYSTICK_DelayMs(unsigned int delay);
void SYSTICK_SetCallback(void (*callback)(void));
void SYSTICK_Handler(void);


#endif /*SYSTICK_H*/