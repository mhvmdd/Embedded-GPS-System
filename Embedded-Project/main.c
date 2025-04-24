#include "BIT_MATH.h"
#include "STD.h"
#include "tm4c123gh6pm.h"
#include "EEPROM.h"

int main(void) {
	
   volatile f32 read_value = 0;

    // 1. Initialize EEPROM
    if (EEPROM_Init()) {
        // 2. Write test value
        EEPROM_write(123.456f, 0x01);

        // 3. Read it back
        read_value = EEPROM_read(0x01);
		}
		else {
        // EEPROM init failed
        while(1);  // Stay here to debug
    }

    while (1) {
        // Your main loop
    }
}
