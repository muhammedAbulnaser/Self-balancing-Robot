/*
 * TIMER0_private.h
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/*Registers*/
#define TCCR2_REG  *((volatile u8*)0x45)
#define TCNT2_REG  *((volatile u8*)0x44)
#define OCR2_REG   *((volatile u8*)0x43)
#define TIMSK_REG  *((volatile u8*)0x59)

#endif /* TIMER0_PRIVATE_H_ */
