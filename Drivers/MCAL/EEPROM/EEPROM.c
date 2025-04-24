#include "BIT_MATH.h"
#include "STD.h"
#include  "tm4c123gh6pm.h"
//#include "Systick.h"


int EEPROM_Start(void){
		SET_BIT(SYSCTL_RCGCEEPROM_R,0);//Enable EEPROM run clock 
	
		EEPROM_EESIZE_R=	0x000003FF; //only for test  EEPROM Register
		EEPROM_EEUNLOCK_R = 0x1ACCE551;//only for test  EEPROM Register
		
	
		while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); // wait  to finish  power-on 
    if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) || (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
				return 0;
		} // return an error if any of these two bits (erase retry or program retry) are set which means that theEEPROM was unable to recover its state

			// Resset EEPROM
        SYSCTL_SREEPROM_R |= SYSCTL_SREEPROM_R0; // Reset the EEPROM_0 module 
        SYSCTL_SREEPROM_R =(~ SYSCTL_SREEPROM_R0); // EEPROM module is not in a reset state.
   

        while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); //  wait (when working=0 continue)

        if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) || (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
			return 0;
		} // EEPROM unable to recover its state
		
		return 1; // initialization is completed without any errors
}


//Erase 
void eeprom_error_recovery(void) 
{
		EEPROM_EESUPP_R = EEPROM_EESUPP_START; // start erase
		while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}



int EEPROM_Init(void) // intialization EEPROM
{
			int flag=0;
			flag = EEPROM_Start();
			if(flag)
				; // no errors 
			else
				eeprom_error_recovery(); // error found

		return flag;
}



void EEPROM_write(f32 data,u32 address) 
{
		while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); 	 //	checking not busy
		EEPROM_EEBLOCK_R = address >>4;										//	 block number
		EEPROM_EEOFFSET_R = (address& 0xF);							 //offset within the block
		EEPROM_EERDWR_R = data; 												//data written 
		while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}

f32 EEPROM_read(u32 address) 
{
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	EEPROM_EEBLOCK_R = address >>4;       //Block number
	EEPROM_EEOFFSET_R = (address & 0xF); //offset within the block
	return EEPROM_EERDWR_R;
}
