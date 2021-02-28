/*
 * TIMER0_private.h
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/*Registers*/
#define TCCR0_REG  *((volatile u8*)0x53)
#define TCNT0_REG  *((volatile u8*)0x52)
#define OCR0_REG   *((volatile u8*)0x5C)
#define TIMSK_REG  *((volatile u8*)0x59)

#endif /* TIMER0_PRIVATE_H_ */
