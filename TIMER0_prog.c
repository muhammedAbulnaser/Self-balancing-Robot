/*
 * TIMER0_prog.c
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */
#include"LIB/std_types.h"
#include"LIB/util.h"
#include"TIMER0_interface.h"
#include"TIMER0_private.h"
#include"TIMER0_cfg.h"
#include<avr/interrupt.h>



typedef void(*Ptr_TIMER0ISR)(void);
Ptr_TIMER0ISR TimerIsr;
Ptr_TIMER0ISR TimerCIsr;



u32 no0_overflow=0;


void TIMER0_vidEnableInterrupt(void)
{
	sei();
	TIMSK_REG |= INT_MODE;
}


void TIMER0_vidDisableInterrupt(void)
{
	CLR_BIT(TIMSK_REG,0);
	CLR_BIT(TIMSK_REG,1);
}


void TIMER0_vidEnableOut(void)
{
	TCCR0_REG |= (OUTPUT<<4);
}


void TIMER0_vidDisableOut(void)
{
	TCCR0_REG |= (DISCONNECTED<<4);

}


void TIMER0_vidInit(void)
{
	//setting up pre-scalers
	TCCR0_REG |= PRSCL;

	//setting up waveform mode
	u8 Bit6 = GET_BIT(WAVE_MODE,1);
	u8 Bit3 = GET_BIT(WAVE_MODE,0);
	TCCR0_REG |= (Bit6<<6);
	TCCR0_REG |= (Bit3<<3);

}


//u16  TIMER0_GetTicks(void);


u32  TIMER0_GetNum_Overflow(void)
{
	return no0_overflow;
}



void TIMER0_vidOVReset(void)
{
	no0_overflow = 0;
	TCNT0_REG = 0;
}



void TIMER0_vidSetOUTCOMP(u8 u8Val_Copy)
{
	OCR0_REG = u8Val_Copy;
}


void TIMER0_vidOCInt_Set(void(*Ptr_TIMERISR)(void))
{
	TimerCIsr = Ptr_TIMERISR;
}



void TIMER0_vidOVInt_Set(void(*Ptr_TIMERISR)(void))
{
	TimerIsr = Ptr_TIMERISR;
}



//ISR (TIMER0_OVF_vect)
//{
//	no0_overflow++;
////	TimerIsr();
//}
//
//
//ISR (TIMER0_COMP_vect)
//{
//	TimerCIsr();
//}

