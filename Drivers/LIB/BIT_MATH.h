#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BIT)          REG |=  (1 << (BIT))	//set bit
#define CLR_BIT(REG,BIT)          REG &= ~(1 << (BIT))	//clear bit
#define GET_BIT(REG,BIT)          ((REG >> BIT) & 1  )	//get bit
#define TOG_BIT(REG,BIT)          REG ^=  (1 << (BIT))  //toggle bit
#define SET(REG,VAL)              REG|= VAL             //set more than 1 bit
#define CLR(REG,VAL)              REG&=~ VAL            //clear more than 1 bit
#define GET(REG)                  (REG&0Xff)             // get more than 1 bit
#define CHECK_REG(REG1,REG2)       (REG1&REG2)


#endif
