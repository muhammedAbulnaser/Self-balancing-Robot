/*
 * GYRO_interface.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Abdulnaser
 */

#ifndef GYRO_INTERFACE_H_
#define GYRO_INTERFACE_H_

/* public definitions*/

#define slave_address 0x68

/* public functions*/

 void GYRO_Init(void);
 void GYRO_write_data(u8 u8_Reg_Add,u8 u8_data);
 s16 GYRO_Read_Data(u8 reg_add);
 s16 GYRO_Read_XData(void);
 s16 GYRO_Read_YData(void);
 s16 GYRO_Read_ZData(void);

#endif /* GYRO_INTERFACE_H_ */
