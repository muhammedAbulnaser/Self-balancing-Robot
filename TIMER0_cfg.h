/*
 * TIMER0_cfg.h
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */

#ifndef TIMER0_CFG_H_
#define TIMER0_CFG_H_

/*interrupt Mode*/
/*Range:
 *  	T0_OVERFLOW
 *  	T0_OUTCOPM  */
#define INT_MODE  T0_OVERFLOW


/*Wave generation mode*/
/*Range: NORMAL
	 	 PWM_PHASE
	 	 CTC
	 	 FAST_PWM  */
#define WAVE_MODE  NORMAL


/*Output Mode*/
/*Range: DISCONNECTED
	 	 TOGGLE
	 	 INVERTED
	 	 NON_INVERTED */
#define OUTPUT  DISCONNECTED

/*Prescaler*/
/*Range: TIMER0_NO_PRSCL
 	 	 TIMER0_8_PRSCL
		 TIMER0_64_PRSCL
	 	 TIMER0_256_PRSCL
	 	 TIMER0_1024_PRSCL  */
#define PRSCL TIMER0_NO_PRSCL






#endif /* TIMER0_CFG_H_ */
