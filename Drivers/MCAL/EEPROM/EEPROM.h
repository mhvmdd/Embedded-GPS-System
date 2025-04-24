#ifndef EEPROM_H
#define EEPROM_H
#include "STD.h"

//#define EEPROM_START_ADDR 	0x2000  // Start address of EEPROM emulation in flash memory
//#define EEPROM_SIZE       	1024    // EEPROM size in bytes (adjust according to your device)


extern int EEPROM_Init(void);
extern void EEPROM_write(f32 data,u32 address) ;
extern f32 EEPROM_read(u32 address);

#endif /*EEPROM_H*/
