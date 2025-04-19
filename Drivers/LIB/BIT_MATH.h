#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BIT)          REG |=  (1 << (BIT))	//set bit
#define CLR_BIT(REG,BIT)          REG &= ~(1 << (BIT))	//clear bit
#define GET_BIT(REG,BIT)          ((REG >> BIT) & 1  )	//get bit
#define TOG_BIT(REG,BIT)          REG ^=  (1 << (BIT))  //toggle bit


#endif 
