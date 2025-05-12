
 /*
 * Program.c
 *
 *  Created on: May 10, 2025
 *      Author: Mohammed Yasser
 */

//----------LIB INCLUDES-----------
#include <stdio.h>
#include <stdbool.h>
//---------------------------------

//----------MCAL INCLUDES----------
#include "tm4c123gh6pm.h"
#include "GPIO/GPIO.h"
#include "SYSTICK/SYSTICK.h"
#include "UART/UART.h"
#include "ADC/ADC.h"
//---------------------------------

//----------HAL INCLUDES-----------
#include "LCD/LCD.h"
#include "GPS/GPS.h"
#include "SWITCH/SWITCH.h"
#include "LED/LED.h"
//---------------------------------

//----------APP INCLUDES-----------
#include "Program.h"
//---------------------------------


//-----------------------Program Variables--------------------------
volatile char confirm = 1; 		//confrim / back button
volatile char ON = 1; 			//on / off button
volatile char ON_flag = false;

volatile int select = 0;  		//ADC value
volatile char sel_main= 0;    //main menu select
volatile char sel_goto = 0;   //goto select
volatile char GameStart_flag = false;   //game start flag
volatile char GameWin_flag = false;   //game start flag
//----------------------------------------------------------------------

//--------------------------GPS Variables-------------------------------
extern Point_t regions_center[8];
extern int region_num;
extern Region_t regions[9];
extern Point_t curr_p;
extern Point_t regions_center[8];

double nearDis = MAX_DISTANCE;
double Dis;

GPS_DATA msg;
Point_t treasure;
//----------------------------------------------------------------------


extern int randseed;
extern int count_1m;
extern int count_5m;




//---------------Random Number Functions-----------------------------
static unsigned long seed = 1;

void srand(int s) {
    seed = s;
}
int rand(void) {
    seed = (1103515245 * seed + 12345) & 0x7FFFFFFF;
    return (int)(seed >> 16) & 0x7FFF;
}
int Random_1_to_8() {
    return (rand() % 8) + 1;
}
//------------------------------------------------------------------


//-------------------------------------------------------------------
//                      APIs
//-------------------------------------------------------------------
void Hardware_Init(void (*callback)(void)){
	
	SysTick_Init();
	
	ADC_Init();
	
	UART5_Init();
	
	DIO_voidInitPort(PORTF);
	

	
	LCD_Init();
	
	
	HAL_LEDsInit();
	
	HAL_SWsInit();
	
	__enable_irq();
	
	SysTick_SetCallback(callback);
	
	ON_flag = false;
	// Read initial state of ON button (PF0)
	
	ON = DIO_u8GetPinValue(PORTF, PIN0);  // Active LOW
	if (ON == 1) {
		// Wait until button is released to avoid accidental reset on startup
		while (DIO_u8GetPinValue(PORTF, PIN0) == 1);
		SYSTICK_DelayMs(10); // debounce
	}

	ON_flag = true;
}



void Program_Init(){
	
	srand(randseed);
	
	LCD_WriteString("HELLO,");
	LCD_SetCursor(1, 0);
	LCD_WriteString("STARTING PROGRAM....");
	SYSTICK_DelayMs(4000);
	LCD_Clear();
	LCD_SetCursor(0, 4);
	LCD_WriteString("WELCOME");
}

void Program_DeInit(){
	LCD_Clear();
	LCD_WriteString("SHUTTING DOWN.....");
	SYSTICK_DelayMs(4000);
	LCD_Clear();

}


void MainMenu(){
		
	LCD_Clear();
	LCD_SetCursor(0, 0);
	
	LCD_WriteString("Main Menu :");
	SYSTICK_DelayMs(50);
	LCD_SetCursor(1, 3);
	
	while(1){
		select = ADC_Read();
			if(select < 0x700 && select > 0x400){  // Modified region for first case
				sel_main = 1;
				LCD_SetCursor(1, 6);
				LCD_WriteString("1.GOTO       ");
				SYSTICK_DelayMs(50);
		}
		else if (select < 0x600 && select > 0x300){  // Modified region for second case
				sel_main = 2;
				LCD_SetCursor(1, 6);
				LCD_WriteString("2.GAME      ");
				SYSTICK_DelayMs(50);
		}
		else {
				sel_main = 3;
				LCD_SetCursor(1, 6);
				LCD_WriteString("3.NEARBY      ");
				SYSTICK_DelayMs(50);
		}
		        // Wait for confirm button press to finalize selection
        if (confirm == 0) {
            SYSTICK_DelayMs(10);       // debounce
            while (confirm == 0);      // wait for release
            SYSTICK_DelayMs(10);       // debounce
            break;                     // exit selection loop
        }
	}
	
	
}


void GoTo() {
    SYSTICK_DelayMs(200); // debounce delay

    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_WriteString("GOTO :");
    // Selection mode
    while (1) {
        select = ADC_Read();

        if (select > 1732) {
            sel_goto = 1;
            LCD_SetCursor(1, 3);
            LCD_WriteString("1.HALL A/B     ");
        } else if (select > 1488) {
            sel_goto = 2;
            LCD_SetCursor(1, 3);
            LCD_WriteString("2.HALL C/D     ");
        } else if (select > 1244) {
            sel_goto = 3;
            LCD_SetCursor(1, 3);
            LCD_WriteString("3.CREDIT       ");
        } else if (select > 1000) {
            sel_goto = 4;
            LCD_SetCursor(1, 3);
            LCD_WriteString("4.MOSQUE       ");
        } else if (select > 756) {
            sel_goto = 5;
            LCD_SetCursor(1, 3);
            LCD_WriteString("5.LIBRARY      ");
        } else if (select > 512) {
            sel_goto = 6;
            LCD_SetCursor(1, 3);
            LCD_WriteString("6.PITCH        ");
        } else if (select > 268) {
            sel_goto = 7;
            LCD_SetCursor(1, 3);
            LCD_WriteString("7.FOUNTAIN     ");
        } else {
            sel_goto = 8;
            LCD_SetCursor(1, 3);
            LCD_WriteString("8.LUBAN        ");
        }

        // Wait for confirm button press to finalize selection
        if (confirm == 0) {
            SYSTICK_DelayMs(10);       // debounce
            while (confirm == 0);      // wait for release
            SYSTICK_DelayMs(10);       // debounce
            break;                     // exit selection loop
        }
    }
		
		SYSTICK_DelayMs(200);
    // Now call the function based on selection

		
		    switch (sel_goto) {
        case 1: ProcessLocation("HALL A/B", regions_center[0], regions[1]); break;
        case 2: ProcessLocation("HALL C/D", regions_center[1], regions[2]); break;
        case 3: ProcessLocation("CREDIT", regions_center[2], regions[3]); break;
        case 4: ProcessLocation("MOSQUE", regions_center[3], regions[4]); break;
        case 5: ProcessLocation("LIBRARY", regions_center[4], regions[5]); break;
        case 6: ProcessLocation("PITCH", regions_center[5], regions[6]); break;
        case 7: ProcessLocation("FOUNTAIN", regions_center[6], regions[7]); break;
        case 8: ProcessLocation("LUBAN", regions_center[7], regions[8]); break;
    }
}


void Game(){
	char str[10];
	char i = 6;
	char* name = regions[i].name;
	treasure = regions_center[i-1];
	SYSTICK_DelayMs(200); //to prevent misclick
	
	LCD_Clear();
	LCD_SetCursor(0, 0);
	
	LCD_WriteString("GAME IS STARING");
	SYSTICK_DelayMs(2000);
	
	LCD_Clear();
	LCD_SetCursor(0, 0);
	LCD_WriteString("TRESURE HUNT");
	SYSTICK_DelayMs(2000);
	
	LCD_Clear();
	LCD_SetCursor(0, 0);
	LCD_WriteString("FIND THE GOLD...");
	LCD_SetCursor(1, 0);
  LCD_WriteString("Distance: ");
	GameStart_flag = true;
	count_5m = 5;
	count_1m = 59000;
	while (1){			
				HAL_GPSRecieveMsg();

				if (HAL_GPSParseMsg(&msg) == PARSING_OK) {
						
						Dis = HAL_GPSCalculateDistance(msg.latitude, msg.longitude, treasure.latitude,treasure.longitude);

						if(count_5m >=0){
												if (Point_In_Quad(curr_p, regions[i].corners) == POINT_NOT_IN_QUAD && Dis >= 10) {
													GameWin_flag = false;
													sprintf(str, "%d", (int)Dis);
													LCD_SetCursor(1, 10);
													LCD_WriteString(str);
													LCD_WriteString("m    ");
											}
										else if (Dis <= 7 || Point_In_Quad(curr_p, regions[i].corners) == POINT_IN_QUAD ) {
												GameStart_flag = false;
												GameWin_flag = true;
												LCD_Clear();
												LCD_SetCursor(0, 0);
												LCD_WriteString("Woohoo...");
												SYSTICK_DelayMs(1500);
												LCD_Clear();
												LCD_SetCursor(0, 0); // First line, first column
												LCD_WriteString("YOU FOUND THE");

												LCD_SetCursor(1, 0); // Second line, first column
												LCD_WriteString("TREASURE");
												HAL_LEDsCelebrationEffect();
												break;
										}
						}
						else{
							GameStart_flag = false;
							GameWin_flag = false;
							Game_LCDGameOver();
							break;
						}

					}
					else {
							GameStart_flag = false;
							LCD_Clear();
							LCD_SetCursor(0, 0);
							LCD_WriteString("GPS Error");
							SYSTICK_DelayMs(2000);			
							break;
					}
								if (confirm == 0) {
								SYSTICK_DelayMs(10);       
								while (confirm == 0); 
								GameStart_flag = false;									
								SYSTICK_DelayMs(10);       
								break;                     
								}
}
			 
	
}

void Game_LCDGameOver(){
		LCD_Clear();
		LCD_SetCursor(0, 0);
		LCD_WriteString("GAME OVER");
		SYSTICK_DelayMs(2000);
}

void Game_LCDRedraw(){
		char str[10];
		LCD_Clear();
		LCD_SetCursor(0, 0);
		LCD_WriteString("FIND THE GOLD...");
		LCD_SetCursor(1, 0);
		LCD_WriteString("Distance: ");
		
		Dis = HAL_GPSCalculateDistance(msg.latitude, msg.longitude, treasure.latitude,treasure.longitude);
		
		sprintf(str, "%d", (int)Dis);
		LCD_SetCursor(1, 10);
		LCD_WriteString(str);
		LCD_WriteString("m    ");
}

void NearBy(){
	char *name;
	int i ;
	char str[10];
	
	SYSTICK_DelayMs(200); //to prevent misclick
	
	LCD_Clear();
	LCD_SetCursor(0, 0);
	
	LCD_WriteString("Checking Near By");
	LCD_SetCursor(1, 0);
	LCD_WriteString("Locations...");
	SYSTICK_DelayMs(2000);
	
	while (1){
			HAL_GPSRecieveMsg();
			
    if (HAL_GPSParseMsg(&msg) == PARSING_OK) {
        // Calculate distance
				nearDis =MAX_DISTANCE;
				for (i = 0 ; i < 8 ; i++){
						Dis = HAL_GPSCalculateDistance(msg.latitude, msg.longitude, regions_center[i].latitude, regions_center[i].longitude);
						if(Dis > 1){
									if(Dis < nearDis ){
										nearDis= Dis;
										region_num = i;
									}
							}
						else {
							i--;
							continue;
						}
				}			
				if(nearDis == MAX_DISTANCE){
							LCD_Clear();
							LCD_SetCursor(0, 0);
							LCD_WriteString("ERROR");
							return;
				}
				
				name = regions[region_num + 1].name;
				LCD_SetCursor(0, 0);
				LCD_WriteString(name);
				LCD_WriteString("...           ");
				LCD_SetCursor(1, 0);
				LCD_WriteString("Distance: ");
        // Check if inside region
        if (isPointInsideRegion(curr_p, regions[region_num + 1].corners) == POINT_NOT_IN_QUAD && Dis >= 7) {
            sprintf(str, "%d", (int)nearDis);
            LCD_SetCursor(1, 10);
            LCD_WriteString(str);
						LCD_WriteString("m    ");
        } else {
            LCD_Clear();
            LCD_SetCursor(0, 0);
            LCD_WriteString("YOU HAVE ARRIVED");
            SYSTICK_DelayMs(3000);
						HAL_LEDsCelebrationEffect();
					
            break;
        }
    } else {
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_WriteString("GPS Error");
				SYSTICK_DelayMs(1000);			// Red LED
				break;
    }
		        if (confirm == 0) {
            SYSTICK_DelayMs(10);       // debounce
            while (confirm == 0);      // wait for release
            SYSTICK_DelayMs(10);       // debounce
            break;                     // exit selection loop
        }
	
		 if (confirm == 0) {
            SYSTICK_DelayMs(10);       // debounce
            while (confirm == 0);      // wait for release
            SYSTICK_DelayMs(10);       // debounce
            break;                     // exit selection loop
        }
	
	}
	
}


void ProcessLocation(const char* name, Point_t center, Region_t region) {
    char str[10];

    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_WriteString(name);
    LCD_WriteString("...           ");

    LCD_SetCursor(1, 0);
    LCD_WriteString("Distance: ");
	
	while (1){
			
		    HAL_GPSRecieveMsg();

    if (HAL_GPSParseMsg(&msg) == PARSING_OK) {
        // Calculate distance
        Dis = HAL_GPSCalculateDistance(msg.latitude, msg.longitude, center.latitude, center.longitude);

        // Check if inside region
        if (isPointInsideRegion(curr_p, region.corners) == POINT_NOT_IN_QUAD && Dis >= 7) {
						LCD_SetCursor(1, 10);
            sprintf(str, "%d", ((int)Dis));
            LCD_WriteString(str);
						LCD_WriteString("m      ");
        } else {
            LCD_Clear();
            LCD_SetCursor(0, 0);
            LCD_WriteString("YOU HAVE ARRIVED");
            SYSTICK_DelayMs(3000);
						HAL_LEDsCelebrationEffect();
            break;
        }
    } else {
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_WriteString("GPS Error");
				SYSTICK_DelayMs(1000);		
				break;
    }
		        if (confirm == 0) {
            SYSTICK_DelayMs(10);       // debounce
            while (confirm == 0);      // wait for release
            SYSTICK_DelayMs(10);       // debounce
            break;                     // exit selection loop
        }
	}
}


