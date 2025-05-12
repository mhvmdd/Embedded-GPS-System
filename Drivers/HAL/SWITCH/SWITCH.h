#ifndef SWITCH_H
#define SWITCH_H

void HAL_SWsInit();
void HAL_SWsSetCallback(void (*callback)(void));
void HAL_SWsInterruptInit();

#endif