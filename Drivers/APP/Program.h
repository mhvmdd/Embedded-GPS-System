

 /*
 * Program.h
 *
 *  Created on: May 10, 2025
 *      Author: Mohammed Yasser
 */


#ifndef PROGRAM_H
#define PROGRAM_H
#include "GPS/GPS.h"

void Hardware_Init(void (*callback)(void));
void Program_Init();

void MainMenu();
void GoTo();
void NearBy();
void Game();
void ProcessLocation(const char* name, Point_t center, Region_t region);
void Game_LCDRedraw();
void Game_LCDGameOver();
void Program_DeInit();

#endif