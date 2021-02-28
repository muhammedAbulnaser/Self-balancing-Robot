/*
 * TIMER2_interface.h
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */

#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

/****************************************************/
/****************Public Definitions******************/
/****************************************************/
//prescalers
#define TIMER2_NO_PRSCL    1
#define TIMER2_8_PRSCL     2
#define TIMER2_32_PRSCL    3
#define TIMER2_64_PRSCL    4
#define TIMER2_128_PRSCL   5
#define TIMER2_256_PRSCL   6
#define TIMER2_1024_PRSCL  7

//interrupt mode
#define OVERFLOW   6
#define OUTCOPM    7

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
void TIMER2_vidEnableOut(void);
void TIMER2_vidDisableOut(void);
void TIMER2_vidEnableInterrupt(void);
void TIMER2_vidDisableInterrupt(void);
void TIMER2_vidInit(void);
u16  TIMER2_GetTicks(void);
u32  TIMER2_GetNum_Overflow(void);
void TIMER2_vidOVReset(void);
void TIMER2_vidSetOUTCOMP(u8 u8Val_Copy);
void TIMER2_vidSetPRSCL(u8);
void TIMER2_vidOCInt_Set(void(*Ptr_TIMER2ISR)(void));
void TIMER2_vidOVInt_Set(void(*Ptr_TIMER2ISR)(void));
#endif /* TIMER2_INTERFACE_H_ */
