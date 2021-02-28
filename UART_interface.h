/*
 * UART_interface.h
 *
 *  Created on: Sep 28, 2018
 *      Author: Abdulnaser
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*******************************************/
/************Public definitions*************/
/*******************************************/






/*******************************************/
/************Public Functions*************/
/*******************************************/
void UART_vidInit(void);
void UART_SendChar(u8);
u8   UART_RecieveChar(void);

#endif /* UART_INTERFACE_H_ */
