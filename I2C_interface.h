/*
 * I2C_interface.h
 *
 *  Created on: Oct 5, 2018
 *      Author: Abdulnaser
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#define TW_MT_ARB_LOST   0x38
#define TW_MR_ARB_LOST   0x38
#define TW_START         0x08
#define TW_REP_START     0x10
#define TW_MT_SLA_ACK    0x18
#define TW_MT_DATA_ACK   0x28
#define TW_MR_DATA_NOT_ACK  0x58
#define TW_MR_SLA_NOT_ACK   0x48
#define TW_MT_SLA_NOT_ACK   0x20
#define TW_MT_DATA_NOT_ACK  0x30
#define TW_MR_DATA_ACK   0x50
#define TW_MR_SLA_ACK    0x40


void I2C_voidInit(void);
void I2C_voidSendStart(void);
void I2C_voidSendStop(void);
void I2C_voidSendSLA_W(u8 SLA);
void I2C_voidSendSLA_R(u8 SLA);
void I2C_voidSendData(u8 Data);
u8 I2C_u8CheckStatus(u8 status);
u8 I2C_u8ReceiveWithNoAck(void);
s8 I2C_u8ReceiveWithSendAck(void);

#endif /* I2C_INTERFACE_H_ */
