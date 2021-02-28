/*
 * main.c
 *
 *  Created on: Dec 10, 2018
 *      Author: Abdulnaser
 */
#include "LIB/std_types.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "TIMER2_interface.h"
#include "I2C_interface.h"
#include "GYRO_interface.h"
#include "ACC_interface.h"
#include"LIB/util.h"
#include <avr/interrupt.h>
#include "UART_interface.h"
#include <util/delay.h>
#include "math.h"

f32 Kp = 21;
f32 Ki = 2.5;
f32 Kd = 850;


u8 counter = 0;
u8 start = 0;
u16 overflow = 0;
s16 ACC_Y;
s16 ACC_Z;
f32 ACC_angle;

s16 GYRO_data;
f64 GYRO_temp = 0;
f32 GYRO_angle = 0;

f32 angle = 0;
f32 self_balance_pid_setpoint = 0;
f32 setpoint = -0.9;

void calculate_angle(void);
s16  calculate_PID(void);
void sendInt(s32);


int main(void)
{
	s8 flag = 0;
	s16 output,last_output=0;
	DIO_VidSetPortDirection(DIO_u8PORTA,0xff);
	DIO_VidSetPortDirection(DIO_u8PORTB,0xff);
	DIO_VidSetPortDirection(DIO_u8PORTD,0xff);
	I2C_voidInit();
	GYRO_Init();
	UART_vidInit();

	TIMER2_vidInit();
	TIMER2_vidEnableOut();
	TIMER2_vidSetOUTCOMP(0);

	TIMER0_vidInit();
	TIMER0_vidEnableInterrupt();

	for(u8 i=0;i<250;i++)
	{
		GYRO_temp += (f32)GYRO_Read_XData();
		_delay_ms(4);
	}
	GYRO_temp /= 250;

	for(u8 x=0;x<5;x++)
	{
		calculate_angle();
		_delay_ms(4);
	}
	GYRO_angle = ACC_angle;

	DIO_VidSetPortValue(DIO_u8PORTA,0x01);
	overflow = 0;
	while(1)
	{


		calculate_angle();

		output = calculate_PID();
//overflow = 0;
		if((output*last_output)<0)
		{
			DIO_VidSetPortValue(DIO_u8PORTA,0x00);
			if(output>=0){DIO_VidSetPortValue(DIO_u8PORTA,0x01);}
			else{DIO_VidSetPortValue(DIO_u8PORTA,0x02);}
		}

		 if(setpoint == 0){                                                    //If the setpoint is zero degrees
		    if(output < 0)self_balance_pid_setpoint += 0.0015;                  //Increase the self_balance_pid_setpoint if the robot is still moving forewards
		    if(output > 0)self_balance_pid_setpoint -= 0.0015;                  //Decrease the self_balance_pid_setpoint if the robot is still moving backwards
		  }

		last_output = output;
		if(output<0){output*=-1;}
		TIMER2_vidSetOUTCOMP(output);

//		sendInt(ACC_angle);
//		UART_SendChar('*');
		if(overflow>195)
		{
			DIO_VidSetPinValue(DIO_u8PORTB,1,1);
		}
		else
		{
			DIO_VidSetPinValue(DIO_u8PORTB,1,0);
		}
		while(overflow<188);
		overflow = 0;
	}

	return 0;

}



void calculate_angle()
{

	ACC_Y = ACC_Read_YData();
	ACC_Z = ACC_Read_ZData();
	ACC_angle = atan2(ACC_Y,ACC_Z)*57.3;

//	if(ACC_angle<0.05 || ACC_angle>-0.05){ACC_angle=0;}

	if(start == 0 && ACC_angle<0.5 && ACC_angle>-0.5)
	{
		angle = ACC_angle;
		start = 1;
	}

	GYRO_data = (f32)GYRO_Read_XData() - GYRO_temp;
	angle= angle + (GYRO_data * 0.000031);// reblace the number by overflow variable * 21 micro* sensitivity

	angle  = angle*0.99 + ACC_angle*0.01;

}





s16  calculate_PID(void)
{
	static f32 int_mem = 0,last_Error=0;
	f32 Error,drevative,output;

	Error = setpoint - angle - self_balance_pid_setpoint;
	drevative = (Error-last_Error);

	int_mem  += Ki*Error;
	if(int_mem>255){int_mem = 255;}
	if(int_mem<-255){int_mem = -255;}

	output = Kp*Error + int_mem + Kd*drevative;
	if(output>255){output = 255;}
	if(output<-255){output = -255;}
	last_Error = Error;


	if(start == 0 || angle>45 || angle<-45)
	{
		last_Error = 0;
		last_Error = 0;
		output = 0;
		start = 0;
	}

	if(output<10 && output>-10)output=0;
	return output;
}




ISR(TIMER0_OVF_vect)
{
	overflow++;
}



ISR(USART_RXC_vect)
{
	u8 flag=0;
	flag = UDR;
	switch(flag)
	{
	case '7': Kp++; break;
	case '4': Kp--; if(Kp<0)Kp=0; break;

	case '8': Ki+=0.1; break;
	case '5': Ki-=0.1; if(Ki<0)Ki=0; break;

	case '9': Kd++; break;
	case '6': Kd--; if(Kd<0)Kd=0; break;

	case '+': setpoint +=0.15; break;
	case '-': setpoint -=0.15; break;
	counter++;
////	if(counter == 2)
////	{
//		switch(flag)
//		{
//		case 'F':setpoint+=0.5;
//				if(setpoint>1.5)setpoint=1.5;
//				break;
//
//		case 'B':setpoint-=0.5;
//				if(setpoint<0)setpoint=0;
//				break;
//
//		case 'S':setpoint = 0.5;
//				break;
//		}
//		counter = 0;
//	}
	case '0':
		TIMER2_vidDisableOut();
		UART_SendChar('P');
		sendInt(Kp);
		UART_SendChar(' ');
		UART_SendChar('I');
		sendInt(Ki);
		UART_SendChar(' ');
		UART_SendChar('D');
		sendInt(Kd);
		UART_SendChar(' ');

		break;

	}

}

void sendInt(s32 Number)
{
	u8 start=2;
	u16 Digits[10]={0};
	u16 Dnum=9,temp=0;




	if(Number<0)
	{
		UART_SendChar('-');
		Number *=-1;
	}

	if(Number>=10000){start=1;}

	do
	{
		temp=Number%10;
		Number=Number/10;
		--Dnum;
		Digits[Dnum]=temp + '0';
	}while(Number!=0);




	for(u8 counter=start;counter<=9;counter++)
	{
		if(Digits[counter]==0)
		{
			continue;
		}

		UART_SendChar(Digits[counter]);
	}


}
