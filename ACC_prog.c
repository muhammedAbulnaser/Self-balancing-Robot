/*
 * ACC_prog.c
 *
 *  Created on: Oct 25, 2018
 *      Author: Abdulnaser
 */
#include"LIB/std_types.h"
#include"LIB/util.h"
#include <util/delay.h>
#include"ACC_interface.h"
#include"I2C_interface.h"
#include"ACC_private.h"



void ACC_Init(void)
{
	 	// self test disabled,  +-16g range

	// you must write GYRO_init before ACC_init because it is depended on it
}

void ACC_write_data(u8 u8_Reg_Add,u8 u8_data)
{
	 I2C_voidSendStart();
		   if(I2C_u8CheckStatus(TW_START)!=1)
			   return;

     I2C_voidSendSLA_W(acc_slave_address);
		   if(I2C_u8CheckStatus(TW_MT_SLA_ACK)!=1)
		   	   return;

	 I2C_voidSendData(u8_Reg_Add);
		   if(I2C_u8CheckStatus(TW_MT_DATA_ACK)!=1)
		   	   return;

	 I2C_voidSendData(u8_data);
		   if(I2C_u8CheckStatus(TW_MT_DATA_ACK)!=1)
		   	   return;

	I2C_voidSendStop();
}

s16 ACC_Read_Data(u8 reg_add)
{
	s16 arr[2]={0};

	   I2C_voidSendStart();
	          if(I2C_u8CheckStatus(TW_START)!=1)
		                return 0;

	   I2C_voidSendSLA_W(acc_slave_address);
	          if(I2C_u8CheckStatus(TW_MT_SLA_ACK)!=1)
	   	                return 1;

	   I2C_voidSendData(reg_add);
	          if(I2C_u8CheckStatus(TW_MT_DATA_ACK)!=1)
		                return 2;

	   I2C_voidSendStart();
	         if(I2C_u8CheckStatus(TW_REP_START)!=1)
	  		           return 3;

	   I2C_voidSendSLA_R(acc_slave_address);
	         if(I2C_u8CheckStatus(TW_MR_SLA_ACK)!=1)
	   	               return 4;

	   arr[0]= I2C_u8ReceiveWithSendAck();
	         if(I2C_u8CheckStatus(TW_MR_DATA_ACK)!=1)
	   	   	          return 5;

	   arr[1]= I2C_u8ReceiveWithNoAck();
	         if(I2C_u8CheckStatus(TW_MR_DATA_NOT_ACK)!=1)
	         		  return 6;

	   I2C_voidSendStop();

	 s16  acc_reading= (arr[0] << 8) | arr[1];   // sensitivity scale factor = 2.048
//	 acc_reading /= 128;

   return acc_reading;
}

s16 ACC_Read_XData(void)
{
	    u8 i=ACC_XOUT_H;
		s16 acc_X;

		acc_X= ACC_Read_Data(i);


		return acc_X;
}

s16 ACC_Read_YData(void)
{
	        u8 i=ACC_YOUT_H;
			s16 acc_Y;

			acc_Y = ACC_Read_Data(i);

			return acc_Y;
}

s16 ACC_Read_ZData(void)
{
	        u8 i=ACC_ZOUT_H;
			s16 acc_Z;

			acc_Z= ACC_Read_Data(i);

			return acc_Z;
}


