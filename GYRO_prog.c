/*
 * GYRO_prog.c
 *
 *  Created on: Oct 23, 2018
 *      Author: Abdulnaser
 */
#include"LIB/std_types.h"
#include"LIB/util.h"
#include <util/delay.h>
#include "I2C_interface.h"
#include "GYRO_interface.h"
#include "GYRO_private.h"
#include <util/delay.h>



void GYRO_Init(void)
{
		_delay_ms(200);
		GYRO_write_data(PWM1 ,0x00);       //  CLK_SEL -> internal 8MHZ oscillator
//	    GYRO_write_data(SMPLRT_DIV,0x00);
		GYRO_write_data(GYRO_CFG,0x00);  	//+-250  & self_test disabled
		GYRO_write_data(0x1C,0x08);
		GYRO_write_data(CONFIG ,0x03);      /* input disabled &                     bandwidth     delay(ms)    Fs(kHZ)
		                                                  	  	  	  gyro->           256           0.98          8
   		                                                              acc->            260             0           1         */


//		GYRO_write_data(PWM2 ,0x00);
}

void GYRO_write_data(u8 u8_Reg_Add,u8 u8_data)
{
	 I2C_voidSendStart();
		   if(I2C_u8CheckStatus(TW_START)!=1)
			   return;

     I2C_voidSendSLA_W(slave_address);
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

s16 GYRO_Read_Data(u8 reg_add)  // number of mos reg in ARR
{
	s16 arr[2]={0};

	               I2C_voidSendStart();
				          if(I2C_u8CheckStatus(TW_START)!=1)
					                return 0;

				   I2C_voidSendSLA_W(slave_address);
				          if(I2C_u8CheckStatus(TW_MT_SLA_ACK)!=1)
				   	                return 1;

				   I2C_voidSendData(reg_add);
				          if(I2C_u8CheckStatus(TW_MT_DATA_ACK)!=1)
					                return 2;

				   I2C_voidSendStart();
				         if(I2C_u8CheckStatus(TW_REP_START)!=1)
				  		           return 3;

				   I2C_voidSendSLA_R(slave_address);
				         if(I2C_u8CheckStatus(TW_MR_SLA_ACK)!=1)
				   	               return 4;

				   arr[0]= I2C_u8ReceiveWithSendAck();
				         if(I2C_u8CheckStatus(TW_MR_DATA_ACK)!=1)
				   	   	          return 5;

				   arr[1]= I2C_u8ReceiveWithNoAck();
				         if(I2C_u8CheckStatus(TW_MR_DATA_NOT_ACK)!=1)
				         		  return 6;

				   I2C_voidSendStop();

				   s16 gyro_reading = (arr[0] << 8) | arr[1];     // sensitivity scale factor = 131

//				   gyro_reading = gyro_reading/14.375;

return gyro_reading;
}

s16 GYRO_Read_XData(void)
{
	    u8 i=GYRO_XOUT_H;    // the Twi will read from ARR[0]=X_HIGH and will save in arr[0],arr[1] respectivly;
	    s16 Xg;


		Xg = GYRO_Read_Data(i);


		return Xg;
}

s16 GYRO_Read_YData(void)
{
	u8 i=GYRO_YOUT_H; // the Twi will read from ARR[2]=Y_HIGH and will save in arr[2],arr[3] respectivly;
    s16 Yg;

		Yg= GYRO_Read_Data(i);

		return Yg;
}

s16 GYRO_Read_ZData(void)
{
	u8 i=GYRO_ZOUT_H; // the Twi will read from ARR[4]=Z_HIGH and will save in arr[4],arr[5] respectivly;
	s16 Zg;

	Zg= GYRO_Read_Data(i);

		return Zg;
}
