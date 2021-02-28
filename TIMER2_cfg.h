/*
 * TIMER2_cfg.h
 *
 *  Created on: Sep 16, 2018
 *      Author: Abdulnaser
 */

#ifndef TIMER2_CFG_H_
#define TIMER2_CFG_H_

/*interrupt Mode*/
/*Range:
 *  	OVERFLOW
 *  	OUTCOPM  */
#define INT_MODE  OUTCOPM


/*Wave generation mode*/
/*Range: NORMAL
	 	 PWM_PHASE
	 	 CTC
	 	 FAST_PWM  */
#define WAVE_MODE  FAST_PWM


/*Output Mode*/
/*Range: DISCONNECTED
	 	 TOGGLE
	 	 INVERTED
	 	 NON_INVERTED */
#define OUTPUT  INVERTED

/*Prescaler*/
/*Range: TIMER2_NO_PRSCL
 	 	 TIMER2_8_PRSCL
 	 	 TIMER2_32_PRSCL
		 TIMER2_64_PRSCL
		 TIMER2_128_PRSCL
	 	 TIMER2_256_PRSCL
	 	 TIMER2_1024_PRSCL  */
#define PRSCL TIMER2_64_PRSCL






#endif /* TIMER2_CFG_H_ */
