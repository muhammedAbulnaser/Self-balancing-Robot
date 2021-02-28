/*
 * TIMER2_prog.c
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */
#include"LIB/std_types.h"
#include"LIB/util.h"
#include"TIMER2_interface.h"
#include"TIMER2_private.h"
#include"TIMER2_cfg.h"
#include<avr/interrupt.h>



typedef void(*Ptr_TIMER2ISR)(void);
Ptr_TIMER2ISR TimerIsr;
Ptr_TIMER2ISR TimerCIsr;



u32 no_overflow=0;


void TIMER2_vidEnableInterrupt(void)
{
	SET_BIT(SREG,7);
	SET_BIT(TIMSK_REG,INT_MODE);
}


void TIMER2_vidDisableInterrupt(void)
{
	CLR_BIT(TIMSK_REG,0);
	CLR_BIT(TIMSK_REG,1);
}


void TIMER2_vidEnableOut(void)
{
	TCCR2_REG |= (OUTPUT<<4);
}


void TIMER2_vidDisableOut(void)
{
	TCCR2_REG |= (DISCONNECTED<<4);

}


void TIMER2_vidInit(void)
{
	//setting up pre-scalers
	TCCR2_REG |= PRSCL;

	//setting up waveform mode
	u8 Bit6 = GET_BIT(WAVE_MODE,1);
	u8 Bit3 = GET_BIT(WAVE_MODE,0);
	TCCR2_REG |= (Bit6<<6);
	TCCR2_REG |= (Bit3<<3);

}


//u16  TIMER2_GetTicks(void);


void TIMER2_vidSetPRSCL(u8 val)
{
	TCCR2_REG |= val;
}

u32  TIMER2_GetNum_Overflow(void)
{
	return no_overflow;
}



void TIMER2_vidOVReset(void)
{
	no_overflow = 0;
}



void TIMER2_vidSetOUTCOMP(u8 u8Val_Copy)
{
	OCR2_REG = u8Val_Copy;
}


void TIMER2_vidOCInt_Set(void(*Ptr_TIMERISR)(void))
{
	TimerCIsr = Ptr_TIMERISR;
}



void TIMER2_vidOVInt_Set(void(*Ptr_TIMERISR)(void))
{
	TimerIsr = Ptr_TIMERISR;
}



ISR (TIMER2_OVF_vect)
{
	no_overflow++;
	TimerIsr();
}


ISR (TIMER2_COMP_vect)
{
	TimerCIsr();
}

