/*
 * TIMER0_interface.h
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/****************************************************/
/****************Public Definitions******************/
/****************************************************/
//prescalers
#define TIMER0_NO_PRSCL    1
#define TIMER0_8_PRSCL     2
#define TIMER0_64_PRSCL    3
#define TIMER0_256_PRSCL   4
#define TIMER0_1024_PRSCL  5

//interrupt mode
#define T0_OVERFLOW   1
#define T0_OUTCOPM    2

//wave mode
#define NORMAL    0
#define PWM_PHASE 1
#define CTC       2
#define FAST_PWM  3

//output mode
#define DISCONNECTED  0
#define TOGGLE        1
#define INVERTED      2
#define NON_INVERTED  3




/****************************************************/
/****************Public Functions********************/
/****************************************************/
void TIMER0_vidEnableOut(void);
void TIMER0_vidDisableOut(void);
void TIMER0_vidEnableInterrupt(void);
void TIMER0_vidDisableInterrupt(void);
void TIMER0_vidInit(void);
u16  TIMER0_GetTicks(void);
u32  TIMER0_GetNum_Overflow(void);
void TIMER0_vidOVReset(void);
void TIMER0_vidSetOUTCOMP(u8 u8Val_Copy);
void TIMER0_vidOCInt_Set(void(*Ptr_TIMER0ISR)(void));
void TIMER0_vidOVInt_Set(void(*Ptr_TIMER0ISR)(void));
#endif /* TIMER0_INTERFACE_H_ */
