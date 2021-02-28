/*
 * I2C_prog.c
 *
 *  Created on: Oct 5, 2018
 *      Author: Abdulnaser
 */

#include "LIB/std_types.h"
#include "LIB/util.h"
#include <avr/io.h>
#include "I2C_interface.h"


void I2C_voidInit(void)
{
	TWCR=(1<<TWEN);
	TWBR=52;
	TWSR=0;
	TWAR=2;
}

void I2C_voidSendStart(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0);
}

void I2C_voidSendStop(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_voidSendSLA_W(u8 SLA)
{
	TWDR=(SLA<<1);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(GET_BIT(TWCR,7)==0);
}

void I2C_voidSendSLA_R(u8 SLA)
{
	TWDR=(SLA<<1)|0x01;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(GET_BIT(TWCR,7)==0);
}

void I2C_voidSendData(u8 Data)
{
	TWDR=Data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0);
}

u8 I2C_u8CheckStatus(u8 status)
{
	if((TWSR&0xF8)==status)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0xff;
}

u8 I2C_u8ReceiveWithNoAck(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(GET_BIT(TWCR,7)==0);
	return TWDR;
}

s8 I2C_u8ReceiveWithSendAck(void)
{
	TWCR=(1<<7)|(1<<6) |(1<<2);
		while(GET_BIT(TWCR,7)==0);
		return TWDR;
}
